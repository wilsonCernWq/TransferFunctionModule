// ======================================================================== //
// Copyright SCI Institute, University of Utah, 2018
// ======================================================================== //
#pragma once

#include <string>
#include <memory>
#include <vector>
#include <array>
#include <functional>

#include <GLFW/glfw3.h>
#ifdef _WIN32
# undef APIENTRY
# define GLFW_EXPOSE_NATIVE_WIN32
# define GLFW_EXPOSE_NATIVE_WGL
# include <GLFW/glfw3native.h>
#endif

#include "TransferFunctionModule.h"

namespace tfn {
  namespace tfn_widget {
    class TFN_MODULE_INTERFACE TransferFunctionWidget
    {
    public:
      TransferFunctionWidget(const std::function<void
                             (const std::vector<float>&,
                              const std::vector<float>&,
                              const std::array<float, 2>&)>&);	
      ~TransferFunctionWidget();
      TransferFunctionWidget(const TransferFunctionWidget &);
      TransferFunctionWidget& operator=(const TransferFunctionWidget &);
      /* Control Widget Values
       */
      void setDefaultRange(const float& a, const float& b) 
      {
	defaultRange[0] = a;
	defaultRange[1] = b;
	valueRange[0] = a;
	valueRange[1] = b;
	tfn_changed = true;
      }
      /* Draw the transfer function editor widget, returns true if the
       * transfer function changed
       */
      bool drawUI(bool* p_open = NULL);
      /* Render the transfer function to a 1D texture that can
       * be applied to volume data
       */
      void render(size_t tfn_w, size_t tfn_h = 1);
      // Load the transfer function in the file passed and set it active
      void load(const std::string &fileName);
      // Save the current transfer function out to the file
      void save(const std::string &fileName) const;
    private:
      void DrawTFNEditor(const float margin, const float height);
    private:      

      // TODO
      // This MAYBE the correct way of doing this
/*       struct TFN { */
/* 	std::vector<ColorPoint>   colors; */
/* 	std::vector<OpacityPoint_Linear> opacity; */
/* 	tfn::TransferFunction reader; */
/*       }; */

    private:
      
      // Core Handler
      std::function<void(const std::vector<float>&,
			 const std::vector<float>&,
			 const std::array<float, 2>&
			 )> tfn_sample_set;
      std::vector<tfn::TransferFunction> tfn_readers;
      std::array<float, 2> valueRange;
      std::array<float, 2> defaultRange;

      // TFNs information:
      std::vector<bool> tfn_editable;
      std::vector<std::vector<ColorPoint>>   tfn_c_list;
      std::vector<std::vector<OpacityPoint_Linear>> tfn_o_list;
      std::vector<ColorPoint>*          tfn_c;
      std::vector<OpacityPoint_Linear>* tfn_o;
      std::vector<std::string> tfn_names; // name of TFNs in the dropdown menu

      // State Variables:
      // TODO: those variables might be unnecessary
      bool tfn_edit;
      std::vector<char> tfn_text_buffer; // The filename input text buffer

      // Flags:
      // tfn_changed:   
      //     Track if the function changed and must be re-uploaded.
      //     We start by marking it changed to upload the initial palette
      bool   tfn_changed{true};

      // Meta Data
      // * Interpolated trasnfer function size
      // int tfn_w = 256;
      // int tfn_h = 1; // TODO: right now we onlu support 1D TFN

      // * The selected transfer function being shown
      int  tfn_selection;      
      // * The 2d palette texture on the GPU for displaying the color map in the UI.
      GLuint tfn_palette;
      // Local functions
      void LoadDefaultMap();
      void SetTFNSelection(int);
    };
  }//::tfn_widget
}//::tfn

