// ======================================================================== //
// Copyright 2009-2017 Intel Corporation                                    //
//                                                                          //
// Licensed under the Apache License, Version 2.0 (the "License");          //
// you may not use this file except in compliance with the License.         //
// You may obtain a copy of the License at                                  //
//                                                                          //
//     http://www.apache.org/licenses/LICENSE-2.0                           //
//                                                                          //
// Unless required by applicable law or agreed to in writing, software      //
// distributed under the License is distributed on an "AS IS" BASIS,        //
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. //
// See the License for the specific language governing permissions and      //
// limitations under the License.                                           //
// ======================================================================== //

#pragma once

#ifdef _WIN32
  #ifdef tfn_module_EXPORTS
    #define TFN_MODULE_INTERFACE __declspec(dllexport)
  #else
    #define TFN_MODULE_INTERFACE __declspec(dllimport)
  #endif
#else
  #define TFN_MODULE_INTERFACE
#endif

#include <cassert>
#include <cmath>
#include <string>
#include <array>
#include <vector>
#include <map>
#include <initializer_list>

#define TFN_MODULE_VERSION "0.02 WIP"
namespace tfn
{
  inline TFN_MODULE_INTERFACE const char* GetVersion() 
  {
    return TFN_MODULE_VERSION; 
  };
};

#ifdef TFN_MODULE_EXTERNAL_VECTOR_TYPES
/*! we assume the app already defines osp::vec types. Note those
  HAVE to be compatible with the data layouts used below.
  Note: this feature allows the application to use its own vector
  type library in the following way
  a) include your own vector library (say, ospcommon::vec3f etc, when using 
     the ospcommon library)
  b) make sure the proper vec3f etc are defined in a osp:: namespace, e.g.,
     using
     namespace tfn {
       typedef ospcommon::vec3f vec3f;
     }
  c) defines OSPRAY_EXTERNAL_VECTOR_TYPES
  d) include vec.h
  ! */
#else
namespace tfn {
  struct vec2f    { float x, y; };
  struct vec2i    { int x, y; };
  struct vec3f    { float x, y, z; };
  struct vec3fa   { float x, y, z; union { int a; unsigned u; float w; }; };
  struct vec3i    { int x, y, z; };
  struct vec4f    { float x, y, z, w; };
  struct vec4i    { int x, y, z, w; };
  struct box2i    { vec2i lower, upper; };
  struct box2f    { vec2f lower, upper; };
  struct box3i    { vec3i lower, upper; };
  struct box3f    { vec3f lower, upper; };
  struct linear3f { vec3f vx, vy, vz; };
  struct affine3f { linear3f l; vec3f p; };
  using  range1f = std::array<float,2>;
  using  range2f = std::array<vec2f,2>;
  using  range3f = std::array<vec3f,2>;
  using  list1f  = std::vector<float>;
  using  list2f  = std::vector<vec2f>;
  using  list3f  = std::vector<vec3f>;
  template<class T> const T &clamp(const T &v, const T &lo, const T &hi) 
  {
    return (v < lo) ? lo : (hi < v ? hi : v);
  }
  template<typename T> T lerp(const T &vl, const T &vr, 
                              const T &pl, const T &pr, 
                              const T &p) 
  {
    const T dl = std::abs(pr - pl) > 0.f ? (p - pl) / (pr - pl) : 0.f;
    const T dr = 1.f - dl;
    return vl * dr + vr * dl;
  }
};
#endif

/* The transfer function file format used by the OSPRay sample apps is a
 * little endian binary format with the following layout:
 *
 * VERSION 1:
 *
 * uint32: magic number identifying the file
 * uint64: version number
 * uint64: length of the name of the transfer function (not including \0)
 * [char...]: name of the transfer function (without \0)
 * uint64: number of vec3f color values
 * uint64: numer of vec2f data value, opacity value pairs
 * float64: data value min
 * float64: data value max
 * float32: opacity scaling value, opacity values should be scaled
 *          by this factor
 * [vec3f...]: RGB values
 * [vec2f...]: data value, opacity value pairs
 *
 */

namespace tfn {

//// Basic Types //////////////////////////////////////////////////////////////////////

  // basic color type
  struct TFN_MODULE_INTERFACE color_t {
  public:
    float r = 0.f, g = 0.f, b = 0.f;
  public:
    virtual ~color_t() = default;
             color_t() = default;
    explicit color_t(const float& r, const float& g, const float& b) 
      : r(r), g(g), b(b) {}
    color_t& operator+=(const color_t& rhs) 
    {
      r += rhs.r; g += rhs.g; b += rhs.b; return *this;
    }
    // friends defined inside class body are inline and are hidden from non-ADL lookup,
    // passing lhs by value helps optimize chained a+b+c, otherwise, both parameters 
    // may be const references
    friend color_t operator+(color_t lhs, const color_t& rhs) 
    {
      lhs += rhs; // reuse compound assignment
      return lhs; // return the result by value (uses move constructor)
    }
    uint32_t hex() const;
  };

  // basic opacity type
  struct TFN_MODULE_INTERFACE opacity_t {
  public:
    float a = 0.f;
  public:
    virtual ~opacity_t() = default;
             opacity_t() = default;
    explicit opacity_t(const float& a) : a(a) {}
    opacity_t& operator+=(const opacity_t& rhs) 
    {
      a += rhs.a; return *this;
    }
    friend opacity_t operator+(opacity_t lhs, const opacity_t& rhs) 
    {
      lhs += rhs; return lhs;
    }
  };

  // internal use 
  using _c_t = color_t;
  using _o_t = opacity_t;

  // abstract control point type
  template<typename value_t> 
  struct TFN_MODULE_INTERFACE control_t { 
  protected:
    value_t v;
  public:
    virtual ~control_t() = default;
    const value_t& val() const { return v; }
          value_t& val()       { return v; }
    virtual value_t splat(float x, float w) const = 0;
  };

  // abstract control point list type
  //   the enable_if statement ensures that cp_t can only be a derivated type 
  //   ofcontrol_t
  //   (see reference https://eli.thegreenplace.net/2014/sfinae-and-enable_if)
  template<typename cp_t,
           typename std::enable_if<std::is_base_of<control_t<_c_t>, cp_t>::value ||
                                   std::is_base_of<control_t<_o_t>, cp_t>::value,
                                   cp_t>::type* = nullptr>
  struct TFN_MODULE_INTERFACE control_list_t {
  public:
    using list_t = std::multimap<float, cp_t*>;
    using pair_t = std::pair<float, cp_t*>;
  protected:
    list_t list;
  public:
    virtual ~control_list_t() = default;
    // we dont have a default constructor here becayse we require the list to have
    // at least two points
    template<std::size_t N>
    control_list_t(const pair_t(&list)[N])
    {
      static_assert(N > 1, "Two or more elements are required.");
    }
    explicit control_list_t(const list_t& l) : list(l) {}

/*     const float& pos() const { return p; } */
/*           float& pos()       { return p; } */


    void resize(size_t n) { list.resize(n); }
    void size() const { return list.size(); }
  
/*     void add(const point_t& point)  */
/*     { */
/*       list.insert(std::make_pair(point.pos(), point)); */
/*     } */
/*     void remove(const point_t& point)  */
/*     { */
/*       list.remove(point.pos()); */
/*     } */

    // TODO this might be wrong
    /*   std::vector<T> interpolate0(size_t n) const 
    {
      const float step = 1.f / static_cast<float>(n);
      std::vector<T> output(n);
      
      auto& curr = list.begin();
      auto& next = it;
      for (size_t i = 0; i < n; ++i) {
        const float p = static_cast<float>(i) * step;
        if (p > )

          output[i] += it->splat(p, w);
      }
      return output;
    }
*/
/*     std::vector<T> rasterize(size_t n) const  */
/*     { */
/*       const float w = 1.f / static_cast<float>(n); */
/*       std::vector<T> output(n); */
/*       for (size_t i = 0; i < n; ++i) { */
/*         const float p = static_cast<float>(i) * w; */
/*         for (auto& it : list) { */
/*           output[i] += it->splat(p, w); */
/*         } */
/*       } */
/*       return output; */
/*     } */
  };

//// End of Basic Types ////

//// Control Points ///////////////////////////////////////////////////////////////////

  struct TFN_MODULE_INTERFACE simple_color_control_t 
    : public control_t<color_t>
  {
  public:
    color_t splat(float x, float w) const override
    {
      assert(w >= 0);
      return v;//std::abs(x - p) >= w ? color_t() : v;
    }
  };

  struct TFN_MODULE_INTERFACE simple_opacity_control_t 
    : public control_t<opacity_t>
  {
  public:
    opacity_t splat(float x, float w) const override
    {
      assert(w >= 0);
      return v;//std::abs(x - p) >= w ? opacity_t() : v;
    }
  };

  struct TFN_MODULE_INTERFACE gaussian_opacity_control_t 
    : public control_t<opacity_t>
  {
  protected:
    using value_t = control_t<opacity_t>;
    float sw, sy; // width / height of the gaussian function
    float bx, by;
  public:
    explicit gaussian_opacity_control_t(const value_t& point,
                                        const float& sw, 
                                        const float& sy,
                                        const float& bx, 
                                        const float& by)
      : value_t(point), sw(sw), sy(sy), bx(bx), by(by) {}
    // opacity_t splat(float x, float w) const override 
    // {
    //   return opacity_t();
    // }
  };

  using simple_color_list_t   = 
    control_list_t<simple_color_control_t>;
  using simple_opacity_list_t = 
    control_list_t<simple_opacity_control_t>;

//// End of Control Points ////

//// Old Definitions //////////////////////////////////////////////////////////////////

  struct TFN_MODULE_INTERFACE ColorPoint {
    float p; // location of the control point [0, 1]
    float r, g, b;
    ColorPoint() = default;
    ColorPoint(const float cp, const float cr, 
               const float cg, const float cb);
    ColorPoint(const ColorPoint& c);
    ColorPoint& operator=(const ColorPoint &c);
    unsigned long GetHex();
  };

  struct TFN_MODULE_INTERFACE OpacityPoint_Linear {
    float p; // location of the control point [0, 1]
    float a;
    OpacityPoint_Linear() = default;
    OpacityPoint_Linear(const float cp, const float ca);
    OpacityPoint_Linear(const OpacityPoint_Linear& c);
    OpacityPoint_Linear& operator=(const OpacityPoint_Linear &c);
  };

  struct TFN_MODULE_INTERFACE OpacityPoint_Gaussian {
    float p; // location of the control point [0, 1]
    float a;
    float sw, sy; // width/height of the gaussian function
    float bx, by;
    OpacityPoint_Gaussian() = default;
    OpacityPoint_Gaussian(const float cp,  const float ca,
                          const float csw, const float csy,
                          const float cbx, const float cby);
    OpacityPoint_Gaussian(const OpacityPoint_Gaussian& c);
    OpacityPoint_Gaussian& operator=(const OpacityPoint_Gaussian &c);
  };

//// End of Old Definitions ////

//// Transfer Function ////////////////////////////////////////////////////////////////

  struct TFN_MODULE_INTERFACE TransferFunction {
    std::string name;
    std::vector<tfn::vec3f> rgbValues;
    std::vector<tfn::vec2f> opacityValues;
    double dataValueMin;
    double dataValueMax;
    float opacityScaling;
    // Load the transfer function data in the file
    TransferFunction(const std::string &fileName);
    // Construct a transfer function from some existing one
    TransferFunction(const std::string &name,
		     const std::vector<tfn::vec3f> &rgbValues,
		     const std::vector<tfn::vec2f> &opacityValues,
		     const double dataValueMin,
		     const double dataValueMax,
		     const float opacityScaling);
    // Load the transfer function data from a file
    void load(const std::string &fileName);
    // Save the transfer function data to the file
    void save(const std::string &fileName) const;
  };

  struct TFN_MODULE_INTERFACE TransferFunctionData {
  public:
    //using color_ptr_t   = std::unique_ptr<control_point_t<color_t>>;
    //using opacity_ptr_t = std::unique_ptr<control_point_t<opacity_t>>;
  public:
    bool editable;
    //std::vector<color_ptr_t>   colors;
    //std::vector<opacity_ptr_t> opacities;
    std::unique_ptr<TransferFunction> data;
  };

//// End of Transfer Function ////

};
