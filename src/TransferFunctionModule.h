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

#include <vector>
#include <string>

#ifdef TFNMODULE_EXTERNAL_VECTOR_TYPES
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
    struct box2i    { vec2i lower, upper; };
    struct box3i    { vec3i lower, upper; };
    struct box3f    { vec3f lower, upper; };
    struct linear3f { vec3f vx, vy, vz; };
    struct affine3f { linear3f l; vec3f p; };
};
#endif

#ifdef _WIN32
  #ifdef tfn_module_EXPORTS
    #define TFN_MODULE_INTERFACE __declspec(dllexport)
  #else
    #define TFN_MODULE_INTERFACE __declspec(dllimport)
  #endif
#else
  #define TFN_MODULE_INTERFACE
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

  struct TFN_MODULE_INTERFACE ColorPoint {
    float p; // location of the control point [0, 1]
    float r, g, b;
    ColorPoint() = default;
    ColorPoint(const float cp, const float cr, const float cg, const float cb);
    ColorPoint(const ColorPoint& c);
    ColorPoint& operator=(const ColorPoint &c);
    unsigned long GetHex();
  };

  struct OpacityPoint_Linear {
    float p; // location of the control point [0, 1]
    float a;
    OpacityPoint_Linear() = default;
    OpacityPoint_Linear(const float cp, const float ca);
    OpacityPoint_Linear(const OpacityPoint_Linear& c);
    OpacityPoint_Linear& operator=(const OpacityPoint_Linear &c);
  };

  struct OpacityPoint_Gaussian {
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
}

