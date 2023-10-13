#include <cstring>
#include <iostream>
#include "bmp.hpp"

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cout << "File not found\n";
    return 0;
  }

  ImageBmp image = ImageBmp(argv[1]);
  
  for (int i = 2; i < argc; ++i) {
    if (strcmp(argv[i], "--negative") == 0) {
      image.Negative();
    } else if (strcmp(argv[i], "--replace_color") == 0 ||
               strcmp(argv[i], "-rc") == 0) {
      if (i + 6 >= argc) {
        throw std::runtime_error("Too few arguments");
      }
      std::vector<uint8_t> old_color;
      std::vector<uint8_t> new_color;
      for (uint32_t j = 1; j <= 3; ++j) {
        old_color.push_back(static_cast<uint8_t>(atoi(argv[i + j])));
      }
      for (uint32_t j = 4; j <= 6; ++j) {
        new_color.push_back(static_cast<uint8_t>(atoi(argv[i + j])));
      }
      i += 6;
      image.ReplaceColor(old_color, new_color);
    } else if (strcmp(argv[i], "--clarity_enhancement") == 0) {
      image.ClarityEnhancement();
    } else if (strcmp(argv[i], "--gaussian_blur") == 0) {
      image.GaussianBlur();
    } else if (strcmp(argv[i], "--gray") == 0) {
      image.Gray();
    } else if (strcmp(argv[i], "--ridge_detection") == 0) {
      image.RidgeDetection();
    } else if (strcmp(argv[i], "--reduce_noise") == 0) {
      image.ReduceNoise();
    } else if (strcmp(argv[i], "--vignette") == 0) {
      image.Vignette();
    } else if (strcmp(argv[i], "--cut") == 0) {
      if (i + 4 >= argc) {
        throw std::runtime_error("Too few arguments");
      }
      uint32_t x = atoi(argv[i + 1]);
      uint32_t y = atoi(argv[i + 2]);
      uint32_t width = atoi(argv[i + 3]);
      uint32_t height = atoi(argv[i + 4]);
      i += 4;
      image.Cut(x, y, width, height);
    } else if (strcmp(argv[i], "--compress") == 0) {
      if (i + 2 >= argc) {
        throw std::runtime_error("Too few arguments");
      }
      uint32_t width = atoi(argv[i + 1]);
      uint32_t height = atoi(argv[i + 2]);
      i += 2;
      image.Compress(width, height);
    } else if (strcmp(argv[i], "--dramatic_sepia") == 0 ||
               strcmp(argv[i], "-ds") == 0) {
      image.DramaticSepia();
    } else if (strcmp(argv[i], "--help") == 0) {
      image.Docs();
    }
  }
  image.Save();
}
