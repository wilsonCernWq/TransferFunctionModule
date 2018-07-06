// ======================================================================== //
// Copyright SCI Institute, University of Utah, 2018
// ======================================================================== //
#pragma once

#include "TransferFunctionWidget.h"
#include <string>
#include <vector>
#include <map>

using namespace tfn;
using namespace tfn_widget;

static const std::map<std::string, std::vector<float>> _predef_color_table_ = {
  {/* Hot */
    "bluehot", { 
      0.f,   0.f, 0.f, 1.f,
      0.25f, 0.f, 1.f, 1.f, 
      0.5f,  0.f, 1.f, 0.f, 
      0.75f, 1.f, 1.f, 0.f, 
      1.f,   1.f, 0.f, 0.f
    }
  },
  {/* Caleblack */
    "caleblack", { 
      0.f,   0.f, 0.f, 0.f,
      0.17f, 0.f, 0.f, 1.f, 
      0.34f, 0.f, 1.f, 1.f, 
      0.50f, 0.f, 1.f, 0.f, 
      0.67f, 1.f, 1.f, 0.f, 
      0.84f, 1.f, 0.f, 0.f, 
      1.f,   1.f, 0.f, 1.f, 
    }
  },
  {/* Calewhite */
    "calewhite", {
      0.f,   1.f, 1.f, 1.f, 
      0.17f, 0.f, 0.f, 1.f, 
      0.34f, 0.f, 1.f, 1.f, 
      0.50f, 0.f, 1.f, 0.f, 
      0.67f, 1.f, 1.f, 0.f, 
      0.84f, 1.f, 0.f, 0.f, 
      1.f,   1.f, 0.f, 1.f,
    }
  },
  {/* Gray */
    "gray", {0.f, 0.f, 0.f, 0.f, 1.f, 1.f, 1.f, 1.f}
  },
  {/* Xray */
    "xray", {0.f, 1.f, 1.f, 1.f, 1.f, 0.f, 0.f, 0.f}
  },
  {/* Rainbow */
    "rainbow", {
      0.f,  1.f, 0.f, 1.f, 
      0.2f, 0.f, 0.f, 1.f, 
      0.4f, 0.f, 1.f, 1.f, 
      0.6f, 0.f, 1.f, 0.f, 
      0.8f, 1.f, 1.f, 0.f, 
      1.0f, 1.f, 0.f, 0.f, 
    }
  },    
  {/* Contoured */
    "contoured", {
      0.f,    0.f, 0.f, 1.f, 
      0.333f, 0.f, 1.f, 0.f, 
      0.666f, 1.f, 1.f, 0.f, 
      1.0f,   1.f, 0.f, 0.f, 
    }
  },
  {/* Levels discrete color table. */
    "levels", {
      0.000f, 1.00f, 0.00f, 0.00f,
      0.034f, 0.00f, 1.00f, 0.00f,
      0.069f, 0.00f, 0.00f, 1.00f,
      0.103f, 0.00f, 1.00f, 1.00f,
      0.138f, 1.00f, 0.00f, 1.00f,
      0.172f, 1.00f, 1.00f, 0.00f,
      0.207f, 1.00f, 0.53f, 0.00f,
      0.241f, 1.00f, 0.00f, 0.53f,
      0.276f, 0.66f, 0.66f, 0.66f,
      0.310f, 1.00f, 0.27f, 0.27f,
      0.345f, 0.39f, 1.00f, 0.39f,
      0.379f, 0.39f, 0.39f, 1.00f,
      0.414f, 0.16f, 0.65f, 0.65f,
      0.448f, 1.00f, 0.39f, 1.00f,
      0.483f, 1.00f, 1.00f, 0.39f,
      0.517f, 1.00f, 0.67f, 0.39f,
      0.552f, 0.67f, 0.31f, 1.00f,
      0.586f, 0.59f, 0.00f, 0.00f,
      0.621f, 0.00f, 0.59f, 0.00f,
      0.655f, 0.00f, 0.00f, 0.59f,
      0.690f, 0.00f, 0.43f, 0.43f,
      0.724f, 0.59f, 0.00f, 0.59f,
      0.759f, 0.59f, 0.59f, 0.00f,
      0.793f, 0.59f, 0.33f, 0.00f,
      0.828f, 0.63f, 0.00f, 0.31f,
      0.862f, 1.00f, 0.41f, 0.11f,
      0.897f, 0.00f, 0.67f, 0.32f,
      0.931f, 0.27f, 1.00f, 0.49f,
      0.966f, 0.00f, 0.51f, 1.00f,
      1.000f, 0.51f, 0.00f, 1.00f,
    }
  },
  {/* Bluehot */
    "bluehot", {
      0.f,    0.f, 0.f,  0.f, 
      0.333f, 0.f, 0.f,  0.5f, 
      0.666f, 0.f, 0.5f, 1.f, 
      1.0f,   1.f, 1.f,  1.f, 
    }
  },
  {/* Orangehot */
    "orangehot", {
      0.f,    0.f,  0.f,  0.f, 
      0.333f, 0.5f, 0.f,  0.f, 
      0.666f, 1.f,  0.5f, 0.f, 
      1.0f,   1.f,  1.f,  1.f, 
    }
  },
  {/* Hot-and-cold */
    "hot_and_cold", {
      0.f,    0.f, 1.f, 1.f, 
      0.45f,  0.f, 0.f, 1.f, 
      0.5f,   0.f, 0.f, 0.5f, 
      0.55f,  1.f, 0.f, 0.f, 
      1.0f,   1.f, 1.f, 0.f, 
    }
  },
  {/* Hot desaturated */
    "hot_desaturated", {
      0.0f,   0.28f, 0.28f, 0.86f, 
      0.143f, 0.f,   0.f,   0.36f, 
      0.285f, 0.f,   1.f,   1.f, 
      0.429f, 0.f,   0.5f,  0.f, 
      0.571f, 1.f,   1.f,   0.f, 
      0.714f, 1.f,   0.38f, 0.f, 
      0.857f, 0.42f, 0.f,   0.f, 
      1.0f,   0.88f, 0.3f,  0.3f, 
    }
  },
  {/* Difference */
    "difference", {
      0.f,    0.f,  0.f,  1.f, 
      0.5f,   1.f,  1.f,  1.f, 
      1.0f,   1.f,  0.f,  0.f, 
    }
  },
  {/* CPK Molecular Colors used by Jmol */
    "jmol_colors", {
      0.000f, 0.125f, 0.125f, 0.125f,
      0.009f, 1.000f, 1.000f, 1.000f,
      0.018f, 0.851f, 1.000f, 1.000f,
      0.028f, 0.800f, 0.502f, 1.000f,
      0.037f, 0.761f, 1.000f, 0.000f,
      0.046f, 1.000f, 0.710f, 0.710f,
      0.055f, 0.565f, 0.565f, 0.565f,
      0.064f, 0.188f, 0.314f, 0.973f,
      0.073f, 1.000f, 0.051f, 0.051f,
      0.083f, 0.565f, 0.878f, 0.314f,
      0.092f, 0.702f, 0.890f, 0.961f,
      0.101f, 0.671f, 0.361f, 0.949f,
      0.110f, 0.541f, 1.000f, 0.000f,
      0.119f, 0.749f, 0.651f, 0.651f,
      0.128f, 0.941f, 0.784f, 0.627f,
      0.138f, 1.000f, 0.502f, 0.000f,
      0.147f, 1.000f, 1.000f, 0.188f,
      0.156f, 0.122f, 0.941f, 0.122f,
      0.165f, 0.502f, 0.820f, 0.890f,
      0.174f, 0.561f, 0.251f, 0.831f,
      0.183f, 0.239f, 1.000f, 0.000f,
      0.193f, 0.902f, 0.902f, 0.902f,
      0.202f, 0.749f, 0.761f, 0.780f,
      0.211f, 0.651f, 0.651f, 0.671f,
      0.220f, 0.541f, 0.600f, 0.780f,
      0.229f, 0.612f, 0.478f, 0.780f,
      0.239f, 0.878f, 0.400f, 0.200f,
      0.248f, 0.941f, 0.565f, 0.627f,
      0.257f, 0.314f, 0.816f, 0.314f,
      0.266f, 0.784f, 0.502f, 0.200f,
      0.275f, 0.490f, 0.502f, 0.690f,
      0.284f, 0.761f, 0.561f, 0.561f,
      0.294f, 0.400f, 0.561f, 0.561f,
      0.303f, 0.741f, 0.502f, 0.890f,
      0.312f, 1.000f, 0.631f, 0.000f,
      0.321f, 0.651f, 0.161f, 0.161f,
      0.330f, 0.361f, 0.722f, 0.820f,
      0.339f, 0.439f, 0.180f, 0.690f,
      0.349f, 0.000f, 1.000f, 0.000f,
      0.358f, 0.580f, 1.000f, 1.000f,
      0.367f, 0.580f, 0.878f, 0.878f,
      0.376f, 0.451f, 0.761f, 0.788f,
      0.385f, 0.329f, 0.710f, 0.710f,
      0.394f, 0.231f, 0.620f, 0.620f,
      0.404f, 0.141f, 0.561f, 0.561f,
      0.413f, 0.039f, 0.490f, 0.549f,
      0.422f, 0.000f, 0.412f, 0.522f,
      0.431f, 0.753f, 0.753f, 0.753f,
      0.440f, 1.000f, 0.851f, 0.561f,
      0.450f, 0.651f, 0.459f, 0.451f,
      0.459f, 0.400f, 0.502f, 0.502f,
      0.468f, 0.620f, 0.388f, 0.710f,
      0.477f, 0.831f, 0.478f, 0.000f,
      0.486f, 0.580f, 0.000f, 0.580f,
      0.495f, 0.259f, 0.620f, 0.690f,
      0.505f, 0.341f, 0.090f, 0.561f,
      0.514f, 0.000f, 0.788f, 0.000f,
      0.523f, 0.439f, 0.831f, 1.000f,
      0.532f, 1.000f, 1.000f, 0.780f,
      0.541f, 0.851f, 1.000f, 0.780f,
      0.550f, 0.780f, 1.000f, 0.780f,
      0.560f, 0.639f, 1.000f, 0.780f,
      0.569f, 0.561f, 1.000f, 0.780f,
      0.578f, 0.380f, 1.000f, 0.780f,
      0.587f, 0.271f, 1.000f, 0.780f,
      0.596f, 0.188f, 1.000f, 0.780f,
      0.606f, 0.122f, 1.000f, 0.780f,
      0.615f, 0.000f, 1.000f, 0.612f,
      0.624f, 0.000f, 0.902f, 0.459f,
      0.633f, 0.000f, 0.831f, 0.322f,
      0.642f, 0.000f, 0.749f, 0.220f,
      0.651f, 0.000f, 0.671f, 0.141f,
      0.661f, 0.302f, 0.761f, 1.000f,
      0.670f, 0.302f, 0.651f, 1.000f,
      0.679f, 0.129f, 0.580f, 0.839f,
      0.688f, 0.149f, 0.490f, 0.671f,
      0.697f, 0.149f, 0.400f, 0.588f,
      0.706f, 0.090f, 0.329f, 0.529f,
      0.716f, 0.816f, 0.816f, 0.878f,
      0.725f, 1.000f, 0.820f, 0.137f,
      0.734f, 0.722f, 0.722f, 0.816f,
      0.743f, 0.651f, 0.329f, 0.302f,
      0.752f, 0.341f, 0.349f, 0.380f,
      0.761f, 0.620f, 0.310f, 0.710f,
      0.771f, 0.671f, 0.361f, 0.000f,
      0.780f, 0.459f, 0.310f, 0.271f,
      0.789f, 0.259f, 0.510f, 0.588f,
      0.798f, 0.259f, 0.000f, 0.400f,
      0.807f, 0.000f, 0.490f, 0.000f,
      0.817f, 0.439f, 0.671f, 0.980f,
      0.826f, 0.000f, 0.729f, 1.000f,
      0.835f, 0.000f, 0.631f, 1.000f,
      0.844f, 0.000f, 0.561f, 1.000f,
      0.853f, 0.000f, 0.502f, 1.000f,
      0.862f, 0.000f, 0.420f, 1.000f,
      0.872f, 0.329f, 0.361f, 0.949f,
      0.881f, 0.471f, 0.361f, 0.890f,
      0.890f, 0.541f, 0.310f, 0.890f,
      0.899f, 0.631f, 0.212f, 0.831f,
      0.908f, 0.702f, 0.122f, 0.831f,
      0.917f, 0.702f, 0.122f, 0.729f,
      0.927f, 0.702f, 0.051f, 0.651f,
      0.936f, 0.741f, 0.051f, 0.529f,
      0.945f, 0.780f, 0.000f, 0.400f,
      0.954f, 0.800f, 0.000f, 0.349f,
      0.963f, 0.820f, 0.000f, 0.310f,
      0.972f, 0.851f, 0.000f, 0.271f,
      0.982f, 0.878f, 0.000f, 0.220f,
      0.991f, 0.902f, 0.000f, 0.180f,
      1.000f, 0.922f, 0.000f, 0.149f,
    }
  },
  {/* CPK Molecular Colors used by Rasmol */
    "rasmol_colors", {
      0.000f, 0.125f, 0.125f, 0.125f,
      0.009f, 1.000f, 1.000f, 1.000f,
      0.018f, 1.000f, 0.753f, 0.796f,
      0.028f, 0.698f, 0.133f, 0.133f,
      0.037f, 1.000f, 0.078f, 0.576f,
      0.046f, 0.000f, 1.000f, 0.000f,
      0.055f, 0.784f, 0.784f, 0.784f,
      0.064f, 0.561f, 0.561f, 1.000f,
      0.073f, 0.941f, 0.000f, 0.000f,
      0.083f, 0.855f, 0.647f, 0.125f,
      0.092f, 1.000f, 0.078f, 0.576f,
      0.101f, 0.000f, 0.000f, 1.000f,
      0.110f, 0.133f, 0.545f, 0.133f,
      0.119f, 0.502f, 0.502f, 0.565f,
      0.128f, 0.855f, 0.647f, 0.125f,
      0.138f, 1.000f, 0.647f, 0.000f,
      0.147f, 1.000f, 0.784f, 0.196f,
      0.156f, 0.000f, 1.000f, 0.000f,
      0.165f, 1.000f, 0.078f, 0.576f,
      0.174f, 1.000f, 0.078f, 0.576f,
      0.183f, 0.502f, 0.502f, 0.565f,
      0.193f, 1.000f, 0.078f, 0.576f,
      0.202f, 0.502f, 0.502f, 0.565f,
      0.211f, 1.000f, 0.078f, 0.576f,
      0.220f, 0.502f, 0.502f, 0.565f,
      0.229f, 0.502f, 0.502f, 0.565f,
      0.239f, 1.000f, 0.647f, 0.000f,
      0.248f, 1.000f, 0.078f, 0.576f,
      0.257f, 0.647f, 0.165f, 0.165f,
      0.266f, 0.647f, 0.165f, 0.165f,
      0.275f, 0.647f, 0.165f, 0.165f,
      0.284f, 1.000f, 0.078f, 0.576f,
      0.294f, 1.000f, 0.078f, 0.576f,
      0.303f, 1.000f, 0.078f, 0.576f,
      0.312f, 1.000f, 0.078f, 0.576f,
      0.321f, 0.647f, 0.165f, 0.165f,
      0.330f, 1.000f, 0.078f, 0.576f,
      0.339f, 1.000f, 0.078f, 0.576f,
      0.349f, 1.000f, 0.078f, 0.576f,
      0.358f, 1.000f, 0.078f, 0.576f,
      0.367f, 1.000f, 0.078f, 0.576f,
      0.376f, 1.000f, 0.078f, 0.576f,
      0.385f, 1.000f, 0.078f, 0.576f,
      0.394f, 1.000f, 0.078f, 0.576f,
      0.404f, 1.000f, 0.078f, 0.576f,
      0.413f, 1.000f, 0.078f, 0.576f,
      0.422f, 1.000f, 0.078f, 0.576f,
      0.431f, 0.502f, 0.502f, 0.565f,
      0.440f, 1.000f, 0.078f, 0.576f,
      0.450f, 1.000f, 0.078f, 0.576f,
      0.459f, 1.000f, 0.078f, 0.576f,
      0.468f, 1.000f, 0.078f, 0.576f,
      0.477f, 1.000f, 0.078f, 0.576f,
      0.486f, 0.627f, 0.125f, 0.941f,
      0.495f, 1.000f, 0.078f, 0.576f,
      0.505f, 1.000f, 0.078f, 0.576f,
      0.514f, 1.000f, 0.647f, 0.000f,
      0.523f, 1.000f, 0.078f, 0.576f,
      0.532f, 1.000f, 0.078f, 0.576f,
      0.541f, 1.000f, 0.078f, 0.576f,
      0.550f, 1.000f, 0.078f, 0.576f,
      0.560f, 1.000f, 0.078f, 0.576f,
      0.569f, 1.000f, 0.078f, 0.576f,
      0.578f, 1.000f, 0.078f, 0.576f,
      0.587f, 1.000f, 0.078f, 0.576f,
      0.596f, 1.000f, 0.078f, 0.576f,
      0.606f, 1.000f, 0.078f, 0.576f,
      0.615f, 1.000f, 0.078f, 0.576f,
      0.624f, 1.000f, 0.078f, 0.576f,
      0.633f, 1.000f, 0.078f, 0.576f,
      0.642f, 1.000f, 0.078f, 0.576f,
      0.651f, 1.000f, 0.078f, 0.576f,
      0.661f, 1.000f, 0.078f, 0.576f,
      0.670f, 1.000f, 0.078f, 0.576f,
      0.679f, 1.000f, 0.078f, 0.576f,
      0.688f, 1.000f, 0.078f, 0.576f,
      0.697f, 1.000f, 0.078f, 0.576f,
      0.706f, 1.000f, 0.078f, 0.576f,
      0.716f, 1.000f, 0.078f, 0.576f,
      0.725f, 0.855f, 0.647f, 0.125f,
      0.734f, 1.000f, 0.078f, 0.576f,
      0.743f, 1.000f, 0.078f, 0.576f,
      0.752f, 1.000f, 0.078f, 0.576f,
      0.761f, 1.000f, 0.078f, 0.576f,
      0.771f, 1.000f, 0.078f, 0.576f,
      0.780f, 1.000f, 0.078f, 0.576f,
      0.789f, 1.000f, 0.078f, 0.576f,
      0.798f, 1.000f, 0.078f, 0.576f,
      0.807f, 1.000f, 0.078f, 0.576f,
      0.817f, 1.000f, 0.078f, 0.576f,
      0.826f, 1.000f, 0.078f, 0.576f,
      0.835f, 1.000f, 0.078f, 0.576f,
      0.844f, 1.000f, 0.078f, 0.576f,
      0.853f, 1.000f, 0.078f, 0.576f,
      0.862f, 1.000f, 0.078f, 0.576f,
      0.872f, 1.000f, 0.078f, 0.576f,
      0.881f, 1.000f, 0.078f, 0.576f,
      0.890f, 1.000f, 0.078f, 0.576f,
      0.899f, 1.000f, 0.078f, 0.576f,
      0.908f, 1.000f, 0.078f, 0.576f,
      0.917f, 1.000f, 0.078f, 0.576f,
      0.927f, 1.000f, 0.078f, 0.576f,
      0.936f, 1.000f, 0.078f, 0.576f,
      0.945f, 1.000f, 0.078f, 0.576f,
      0.954f, 1.000f, 0.078f, 0.576f,
      0.963f, 1.000f, 0.078f, 0.576f,
      0.972f, 1.000f, 0.078f, 0.576f,
      0.982f, 1.000f, 0.078f, 0.576f,
      0.991f, 1.000f, 0.078f, 0.576f,
      1.000f, 1.000f, 0.078f, 0.576f,
    }
  },
  {/* Jet */
    "jet", {
      0.0f, 0.f, 0.f, 1.f,
      0.3f, 0.f, 1.f, 1.f,
      0.6f, 1.f, 1.f, 0.f,
      1.0f, 1.f, 0.f, 0.f     
    }
  },
};

void TransferFunctionWidget::LoadDefaultMap() {
  for (auto& ct : _predef_color_table_) {
    tfn_c_list.emplace_back(ct.second.size()/4);
    for (size_t i = 0; i < ct.second.size()/4; ++i) {
      tfn_c_list.back()[i] = ColorPoint(ct.second[i*4], 
                                        ct.second[i*4+1], 
                                        ct.second[i*4+2], 
                                        ct.second[i*4+3]);
    }
    tfn_o_list.emplace_back(5);
    tfn_o_list.back()[0] = OpacityPoint_Linear(0.00f, 0.00f);
    tfn_o_list.back()[1] = OpacityPoint_Linear(0.25f, 0.25f);
    tfn_o_list.back()[2] = OpacityPoint_Linear(0.50f, 0.50f);
    tfn_o_list.back()[3] = OpacityPoint_Linear(0.75f, 0.75f);
    tfn_o_list.back()[4] = OpacityPoint_Linear(1.00f, 1.00f);
    tfn_editable.push_back(ct.second.size() < 40);
    tfn_names.push_back(ct.first);
  }
};
