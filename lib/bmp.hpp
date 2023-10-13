#pragma once

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

class ImageBmp {
 private:
  struct FileHeader {
    uint16_t type;
    uint32_t size;
    uint32_t reserved;
    uint32_t offset;
  };

  struct InformationHeader {
    uint32_t size;
    uint32_t width;
    uint32_t height;
    uint16_t planes;
    uint16_t bit_count;

    uint32_t compression;
    uint32_t image_size;
    uint32_t x_pixels_per_meter;
    uint32_t y_pixels_per_meter;
    uint32_t color_used;
    uint32_t color_important;
  };

  struct AdditionalInformation {
    uint32_t red_mask;
    uint32_t green_mask;
    uint32_t blue_mask;
    uint32_t alpha_mask;

    uint32_t cs_type;
    uint32_t endpoints[9];
    uint32_t gamma_red;
    uint32_t gamma_green;
    uint32_t gamma_blue;

    uint32_t intent;
    uint32_t profile_data;
    uint32_t profile_size;
    uint32_t reserved;
  };

  enum Color { kBlue, kGreen, kRed, kReserved };

  FileHeader header_;
  InformationHeader information_header_;
  AdditionalInformation additional_information_;

  const uint16_t bmp_type_ = 0x4d42;
  uint16_t colors_in_pixel_;
  uint16_t padding_;

  std::vector<std::vector<std::vector<uint8_t>>> pixel_color_;

 public:
  ImageBmp() = default;

  explicit ImageBmp(const std::string path);

  ~ImageBmp() = default;

  ImageBmp& operator=(const ImageBmp& other);

  ImageBmp& operator=(ImageBmp&& other);

  uint8_t GetPixel(int, int, uint8_t);

  void MatrixMultiplication(std::vector<std::vector<double>>&, size_t);

  void Save();

  void Negative();

  void ReplaceColor(const std::vector<uint8_t>&, const std::vector<uint8_t>&);

  void ClarityEnhancement();

  void GaussianBlur();

  void Gray();

  void RidgeDetection();

  void ReduceNoise();

  void Vignette();

  void Cut(size_t, size_t, size_t, size_t);

  void Compress(size_t width, size_t height);

  void Docs();

  void DramaticSepia();
};
