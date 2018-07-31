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
        
        class TFN_MODULE_INTERFACE TransferFunctionWidget {
            
        private: // local type definitions
            
            using setter = std::function<void(const list1f&,const list1f&,const range1f&)>;
            
        private: // local variables
            
            // Variables Controlled by Users
            setter tfn_sample_set;
            range1f valueRange;
            range1f defaultRange;
            // Flags
            // tfn_changed: Track if the function changed and must be re-uploaded.
            //              We start by marking it changed to upload the initial
            //              palette
            bool   tfn_changed{true};
            // OpenGL Variables
            // tfn_palette: The 2d palette texture on the GPU for displaying the
            //              color map preview in the UI.
            GLuint tfn_palette;
            
        public: // global functions
            
            ~TransferFunctionWidget();
            TransferFunctionWidget(const setter&);
            TransferFunctionWidget(const TransferFunctionWidget &);
            TransferFunctionWidget& operator=(const TransferFunctionWidget &);
            /* Setup the default data value range for the transfer function
             */
            void setDefaultRange(const float& a, const float& b);
            /* Draw the transfer function editor widget, returns true if the
             * transfer function changed
             */
            bool drawUI(bool* p_open = NULL);
            /* Render the transfer function to a 1D texture that can
             * be applied to volume data
             */
            void render(size_t tfn_w = 256, size_t tfn_h = 1);
            // Load the transfer function in the file passed and set it active
            void load(const std::string &fileName);
            // Save the current transfer function out to the file
            void save(const std::string &fileName) const;
            
        private: // local functions
            
            /** Namely, make a selected transfer function table current
             */
            void setTfn(int);
            /** Load all the pre-defined transfer function maps
             */
            void setDefaultTfns();
            /** Draw the Tfn Editor in a window
             */
            void drawTfnEditor(const float margin, const float height);
            tfn::vec4f drawTfnEditor_ColorControlPoints(void* _draw_list,
                                                        const tfn::vec3f&,
                                                        const tfn::vec2f&,
                                                        const tfn::vec4f&,
                                                        const float&);
            tfn::vec4f drawTfnEditor_OpacityControlPoints(void* _draw_list,
                                                          const tfn::vec2f&,
                                                          const tfn::vec2f&,
                                                          const float&);
            tfn::vec4f drawTfnEditor_InteractionBlocks(void* _draw_list,
                                                       const tfn::vec3f&,
                                                       const tfn::vec2f&,
                                                       const tfn::vec4f&,
                                                       const float&,
                                                       const float&);
            
        private: // TODO: to be cleaned
            
            TransferFunctionData test;
            
            // TODO
            // This MAYBE the correct way of doing this
            /*       struct TFN { */
            /* 	std::vector<ColorPoint>   colors; */
            /* 	std::vector<OpacityPoint_Linear> opacity; */
            /* 	tfn::TransferFunction reader; */
            /*       }; */
            
            
            std::vector<tfn::TransferFunction> tfn_readers;
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
            
            
            // Meta Data
            // * Interpolated trasnfer function size
            // int tfn_w = 256;
            // int tfn_h = 1; // TODO: right now we onlu support 1D TFN
            
            // * The selected transfer function being shown
            int  tfn_selection;
        };
        
    } // ::tfn::tfn_widget
} // ::tfn
