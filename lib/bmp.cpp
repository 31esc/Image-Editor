#include "bmp.hpp"
#include <cstddef>

ImageBmp::ImageBmp(const std::string path) {
  std::ifstream fd;
  fd.open(path, std::ios::out | std::ios::binary);

  if (!fd.is_open()) {
    throw std::runtime_error("File could not be opened");
  }

  fd.read(reinterpret_cast<char*>(&header_.type), sizeof(header_.type));
  fd.read(reinterpret_cast<char*>(&header_.size), sizeof(header_.size));
  fd.read(reinterpret_cast<char*>(&header_.reserved), sizeof(header_.reserved));
  fd.read(reinterpret_cast<char*>(&header_.offset), sizeof(header_.offset));

  if (header_.type != bmp_type_) {
    throw std::runtime_error("File if not bmp");
  }

  fd.read(reinterpret_cast<char*>(&information_header_.size),
          sizeof(information_header_.size));

  if (information_header_.size >= 12) {
    fd.read(reinterpret_cast<char*>(&information_header_.width),
            sizeof(information_header_.width));
    fd.read(reinterpret_cast<char*>(&information_header_.height),
            sizeof(information_header_.height));
    fd.read(reinterpret_cast<char*>(&information_header_.planes),
            sizeof(information_header_.planes));
    fd.read(reinterpret_cast<char*>(&information_header_.bit_count),
            sizeof(information_header_.bit_count));
  }

  if (information_header_.size >= 40) {
    fd.read(reinterpret_cast<char*>(&information_header_.compression),
            sizeof(information_header_.compression));
    fd.read(reinterpret_cast<char*>(&information_header_.image_size),
            sizeof(information_header_.image_size));
    fd.read(reinterpret_cast<char*>(&information_header_.x_pixels_per_meter),
            sizeof(information_header_.x_pixels_per_meter));
    fd.read(reinterpret_cast<char*>(&information_header_.y_pixels_per_meter),
            sizeof(information_header_.y_pixels_per_meter));
    fd.read(reinterpret_cast<char*>(&information_header_.color_used),
            sizeof(information_header_.color_used));
    fd.read(reinterpret_cast<char*>(&information_header_.color_important),
            sizeof(information_header_.color_important));
  }

  if (information_header_.size >= 52) {
    fd.read(reinterpret_cast<char*>(&additional_information_.red_mask),
            sizeof(additional_information_.red_mask));
    fd.read(reinterpret_cast<char*>(&additional_information_.green_mask),
            sizeof(additional_information_.green_mask));
    fd.read(reinterpret_cast<char*>(&additional_information_.blue_mask),
            sizeof(additional_information_.blue_mask));
  }
  if (information_header_.size >= 56) {
    fd.read(reinterpret_cast<char*>(&additional_information_.alpha_mask),
            sizeof(additional_information_.alpha_mask));
  }

  if (information_header_.size >= 108) {
    fd.read(reinterpret_cast<char*>(&additional_information_.cs_type),
            sizeof(additional_information_.cs_type));
    fd.read(reinterpret_cast<char*>(&additional_information_.endpoints),
            sizeof(additional_information_.endpoints));
    fd.read(reinterpret_cast<char*>(&additional_information_.gamma_red),
            sizeof(additional_information_.gamma_red));
    fd.read(reinterpret_cast<char*>(&additional_information_.gamma_blue),
            sizeof(additional_information_.gamma_blue));
    fd.read(reinterpret_cast<char*>(&additional_information_.gamma_green),
            sizeof(additional_information_.gamma_green));
  }

  if (information_header_.size >= 124) {
    fd.read(reinterpret_cast<char*>(&additional_information_.intent),
            sizeof(additional_information_.intent));
    fd.read(reinterpret_cast<char*>(&additional_information_.profile_data),
            sizeof(additional_information_.profile_data));
    fd.read(reinterpret_cast<char*>(&additional_information_.profile_size),
            sizeof(additional_information_.profile_size));
    fd.read(reinterpret_cast<char*>(&additional_information_.reserved),
            sizeof(additional_information_.reserved));
  }

  if (information_header_.size != 12 && information_header_.size != 40 &&
      information_header_.size != 52 && information_header_.size != 56 &&
      information_header_.size != 108 && information_header_.size != 124) {
    throw std::runtime_error("Error: Unsupported BMP format");
  }

  if (information_header_.bit_count != 16 &&
      information_header_.bit_count != 24 &&
      information_header_.bit_count != 32) {
    throw std::runtime_error("Error: Unsupported BMP bit count");
  }

  fd.seekg(header_.offset, std::ios::beg);

  padding_ =
      (4 - (information_header_.width * information_header_.bit_count) % 4) % 4;
  colors_in_pixel_ = information_header_.bit_count / 8;

  pixel_color_.resize(information_header_.height);

  for (uint32_t y = 0; y < information_header_.height; ++y) {
    pixel_color_[y].resize(information_header_.width);
    for (uint32_t x = 0; x < information_header_.width; ++x) {
      pixel_color_[y][x].resize(4);
      for (uint16_t color = 0; color < colors_in_pixel_; ++color) {
        fd.read(reinterpret_cast<char*>(&pixel_color_[y][x][color]), 1);
      }
    }
    fd.ignore(padding_);
  }
  fd.close();
}

void ImageBmp::Save() {
  std::filesystem::path cppFilePath =
      std::filesystem::canonical(std::filesystem::path(__FILE__)).parent_path();
  std::filesystem::path resultImagePath = cppFilePath / "../img/result_img.bmp";
  std::ofstream fd(resultImagePath.c_str(), std::ofstream::binary);

  if (!fd.is_open()) {
    throw std::runtime_error("Failed to open file for writing");
  }

  fd.write(reinterpret_cast<char*>(&header_.type), sizeof(header_.type));
  fd.write(reinterpret_cast<char*>(&header_.size), sizeof(header_.size));
  fd.write(reinterpret_cast<char*>(&header_.reserved),
           sizeof(header_.reserved));
  fd.write(reinterpret_cast<char*>(&header_.offset), sizeof(header_.offset));

  fd.write(reinterpret_cast<char*>(&information_header_.size),
           sizeof(information_header_.size));

  if (information_header_.size >= 12) {
    fd.write(reinterpret_cast<char*>(&information_header_.width),
             sizeof(information_header_.width));
    fd.write(reinterpret_cast<char*>(&information_header_.height),
             sizeof(information_header_.height));
    fd.write(reinterpret_cast<char*>(&information_header_.planes),
             sizeof(information_header_.planes));
    fd.write(reinterpret_cast<char*>(&information_header_.bit_count),
             sizeof(information_header_.bit_count));
  }

  if (information_header_.size >= 40) {
    fd.write(reinterpret_cast<char*>(&information_header_.compression),
             sizeof(information_header_.compression));
    fd.write(reinterpret_cast<char*>(&information_header_.image_size),
             sizeof(information_header_.image_size));
    fd.write(reinterpret_cast<char*>(&information_header_.x_pixels_per_meter),
             sizeof(information_header_.x_pixels_per_meter));
    fd.write(reinterpret_cast<char*>(&information_header_.y_pixels_per_meter),
             sizeof(information_header_.y_pixels_per_meter));
    fd.write(reinterpret_cast<char*>(&information_header_.color_used),
             sizeof(information_header_.color_used));
    fd.write(reinterpret_cast<char*>(&information_header_.color_important),
             sizeof(information_header_.color_important));
  }

  if (information_header_.size >= 52) {
    fd.write(reinterpret_cast<char*>(&additional_information_.red_mask),
             sizeof(additional_information_.red_mask));
    fd.write(reinterpret_cast<char*>(&additional_information_.green_mask),
             sizeof(additional_information_.green_mask));
    fd.write(reinterpret_cast<char*>(&additional_information_.blue_mask),
             sizeof(additional_information_.blue_mask));
  }
  if (information_header_.size >= 56) {
    fd.write(reinterpret_cast<char*>(&additional_information_.alpha_mask),
             sizeof(additional_information_.alpha_mask));
  }

  if (information_header_.size >= 108) {
    fd.write(reinterpret_cast<char*>(&additional_information_.cs_type),
             sizeof(additional_information_.cs_type));
    fd.write(reinterpret_cast<char*>(&additional_information_.endpoints),
             sizeof(additional_information_.endpoints));
    fd.write(reinterpret_cast<char*>(&additional_information_.gamma_red),
             sizeof(additional_information_.gamma_red));
    fd.write(reinterpret_cast<char*>(&additional_information_.gamma_blue),
             sizeof(additional_information_.gamma_blue));
    fd.write(reinterpret_cast<char*>(&additional_information_.gamma_green),
             sizeof(additional_information_.gamma_green));
  }

  if (information_header_.size >= 124) {
    fd.write(reinterpret_cast<char*>(&additional_information_.intent),
             sizeof(additional_information_.intent));
    fd.write(reinterpret_cast<char*>(&additional_information_.profile_data),
             sizeof(additional_information_.profile_data));
    fd.write(reinterpret_cast<char*>(&additional_information_.profile_size),
             sizeof(additional_information_.profile_size));
    fd.write(reinterpret_cast<char*>(&additional_information_.reserved),
             sizeof(additional_information_.reserved));
  }

  fd.seekp(header_.offset, std::ios::beg);

  char padding_symbols[3] = {0, 0, 0};

  for (uint32_t y = 0; y < information_header_.height; ++y) {
    for (uint32_t x = 0; x < information_header_.width; ++x) {
      for (uint16_t color = 0; color < colors_in_pixel_; ++color) {
        fd.write(reinterpret_cast<char*>(&pixel_color_[y][x][color]),
                 sizeof(pixel_color_[y][x][color]));
      }
    }
    fd.write(padding_symbols, padding_);
  }
  fd.close();
}

ImageBmp& ImageBmp::operator=(ImageBmp&& other) {
  if (this != &other) {
    std::swap(header_, other.header_);
    std::swap(information_header_, other.information_header_);
    std::swap(additional_information_, other.additional_information_);
    std::swap(colors_in_pixel_, other.colors_in_pixel_);
    std::swap(padding_, other.padding_);
    std::swap(pixel_color_, other.pixel_color_);
  }
  return *this;
}

ImageBmp& ImageBmp::operator=(const ImageBmp& other) {
  if (this != &other) {
    header_ = other.header_;
    information_header_ = other.information_header_;
    additional_information_ = other.additional_information_;
    colors_in_pixel_ = other.colors_in_pixel_;
    padding_ = other.padding_;
    pixel_color_ = other.pixel_color_;
  }
  return *this;
}

void ImageBmp::Negative() {
  for (uint32_t y = 0; y < information_header_.height; ++y) {
    for (uint32_t x = 0; x < information_header_.width; ++x) {
      for (uint16_t color = 0; color < 3; ++color) {
        pixel_color_[y][x][color] = ~pixel_color_[y][x][color];
      }
    }
  }
}

void ImageBmp::ReplaceColor(const std::vector<uint8_t>& old_color,
                            const std::vector<uint8_t>& new_color) {
  for (uint32_t y = 0; y < information_header_.height; ++y) {
    for (uint32_t x = 0; x < information_header_.width; ++x) {
      if (pixel_color_[y][x][Color::kRed] == old_color[0] &&
          pixel_color_[y][x][Color::kGreen] == old_color[1] &&
          pixel_color_[y][x][Color::kBlue] == old_color[2]) {
        pixel_color_[y][x][Color::kRed] = new_color[0];
        pixel_color_[y][x][Color::kGreen] = new_color[1];
        pixel_color_[y][x][Color::kBlue] = new_color[2];
      }
    }
  }
}

uint8_t ImageBmp::GetPixel(int y, int x, uint8_t color) {
  y = y < 0 ? 0 : y;
  y = y < information_header_.height
          ? y
          : static_cast<int>(information_header_.height) - 1;
  x = x < 0 ? 0 : x;
  x = x < information_header_.width
          ? x
          : static_cast<int>(information_header_.width) - 1;
  return pixel_color_[y][x][color];
}

void ImageBmp::MatrixMultiplication(std::vector<std::vector<double>>& kernel,
                                    size_t div) {
  std::vector<std::vector<std::vector<uint8_t>>> new_arr = pixel_color_;
  int size = static_cast<int>(kernel.size() / 2);
  for (int y = 0; y < information_header_.height; ++y) {
    for (int x = 0; x < information_header_.width; ++x) {
      for (int color = 0; color < colors_in_pixel_; ++color) {
        double sum = 0;
        for (int i = y - size; i <= y + size; ++i) {
          for (int j = x - size; j <= x + size; ++j) {
            sum += GetPixel(i, j, color) * kernel[i - y + size][j - x + size];
          }
        }
        sum /= static_cast<double>(div);
        sum = std::min(255.0, sum);
        sum = std::max(0.0, sum);
        new_arr[y][x][color] = static_cast<uint8_t>(sum);
      }
    }
  }
  pixel_color_ = std::move(new_arr);
}

void ImageBmp::ClarityEnhancement() {
  std::vector<std::vector<double>> kernel = {
      {-1, -1, -1}, {-1, 9, -1}, {-1, -1, -1}};
  MatrixMultiplication(kernel, 1);
}

void ImageBmp::GaussianBlur() {
  std::vector<std::vector<double>> kernel = {{1, 4, 6, 4, 1},
                                             {4, 16, 24, 16, 4},
                                             {6, 24, 36, 24, 6},
                                             {4, 16, 24, 16, 4},
                                             {1, 4, 6, 4, 1}};
  MatrixMultiplication(kernel, 256);
}

void ImageBmp::RidgeDetection() {
  std::vector<std::vector<double>> kernel = {
      {-1, -1, -1}, {-1, 8, -1}, {-1, -1, -1}};
  MatrixMultiplication(kernel, 1);
}

void ImageBmp::Vignette() {
  double cx = 0.5 * information_header_.width;
  double cy = 0.5 * information_header_.height;
  double max_dist = 1.0 / sqrt(cx * cx + cy * cy);
  for (uint32_t y = 0; y < information_header_.height; ++y) {
    for (uint32_t x = 0; x < information_header_.width; ++x) {
      double dist = sqrt((x - cx) * (x - cx) + (y - cy) * (y - cy));
      double lumen = 0.75 / (1.0 + exp((dist * max_dist - 0.73) * 20.0)) + 0.25;
      for (uint16_t color = 0; color < 3; ++color) {
        pixel_color_[y][x][color] =
            static_cast<uint8_t>(lumen * pixel_color_[y][x][color]);
      }
    }
  }
}

void ImageBmp::ReduceNoise() {
  std::vector<std::vector<std::vector<uint8_t>>> new_arr = pixel_color_;
  for (int y = 0; y < information_header_.height; ++y) {
    for (int x = 0; x < information_header_.width; ++x) {
      for (int color = 0; color < colors_in_pixel_; ++color) {
        std::vector<uint8_t> tmp_arr;
        tmp_arr.reserve(9);
        for (int i = y - 2; i <= y + 2; ++i) {
          for (int j = x - 2; j <= x + 2; ++j) {
            tmp_arr.push_back(GetPixel(i, j, color));
          }
        }
        std::sort(tmp_arr.begin(), tmp_arr.end());
        new_arr[y][x][color] = tmp_arr[tmp_arr.size() / 2];
      }
    }
  }
  pixel_color_ = std::move(new_arr);
}

void ImageBmp::Docs() {
  std::cout << "ImageBmp Documentation:" << std::endl;
  std::cout << "--negative: Apply negative filter to the image." << std::endl;
  std::cout
      << "--replace_color: Replace one color with another color in the image."
      << std::endl;
  std::cout << "   Usage: --replace_color <old_color_R> <old_color_G> "
               "<old_color_B> <new_color_R> <new_color_G> <new_color_B>"
            << std::endl;
  std::cout << "--clarity_enhancement: Enhance the clarity of the image."
            << std::endl;
  std::cout << "--gaussian_blur: Apply Gaussian blur to the image."
            << std::endl;
  std::cout << "--gray: Convert the image to grayscale." << std::endl;
  std::cout << "--ridge_detection: Perform ridge detection on the image."
            << std::endl;
  std::cout << "--reduce_noise: Reduce noise in the image." << std::endl;
  std::cout << "--vignette: Apply a vignette effect to the image." << std::endl;
  std::cout << "--cut: Crop a rectangular region from the image." << std::endl;
  std::cout << "   Usage: --cut <x_position> <y_position> <width> <height>"
            << std::endl;
  std::cout << "--compress: Compress the image to the specified dimensions."
            << std::endl;
  std::cout << "   Usage: --compress <new_width> <new_height>" << std::endl;
  std::cout << "--dramatic_sepia: Apply a dramatic sepia effect to the image."
            << std::endl;
  std::cout << "--help: Display this documentation." << std::endl;
}

void ImageBmp::Cut(size_t first, size_t second, size_t width, size_t height) {
  std::vector<std::vector<std::vector<uint8_t>>> new_pixel_color;
  new_pixel_color.resize(height);
  for (uint32_t y = 0; y < height; ++y) {
    new_pixel_color[y].resize(width);
    for (uint32_t x = 0; x < width; ++x) {
      new_pixel_color[y][x].resize(colors_in_pixel_);
      for (uint32_t color = 0; color < colors_in_pixel_; ++color) {
        new_pixel_color[y][x][color] =
            pixel_color_[y + second][x + first][color];
      }
    }
  }
  pixel_color_ = std::move(new_pixel_color);
  uint32_t new_size = height * width * colors_in_pixel_;
  uint32_t tmp = header_.size - information_header_.image_size + new_size;
  information_header_.height = height;
  information_header_.width = width;
  information_header_.image_size = new_size;
  header_.size -= tmp;
}

void ImageBmp::Gray() {
  for (uint32_t y = 0; y < information_header_.height; ++y) {
    for (uint32_t x = 0; x < information_header_.width; ++x) {
      double gray = pixel_color_[y][x][Color::kRed] * 0.299 +
                    pixel_color_[y][x][Color::kGreen] * 0.587 +
                    pixel_color_[y][x][Color::kBlue] * 0.144;
      gray = std::min(gray, 255.0);
      for (uint16_t color = 0; color < 3; ++color) {
        pixel_color_[y][x][color] = static_cast<uint8_t>(gray);
      }
    }
  }
}

void ImageBmp::DramaticSepia() {
  for (uint32_t y = 0; y < information_header_.height; ++y) {
    for (uint32_t x = 0; x < information_header_.width; ++x) {
      double sepia[3];
      sepia[Color::kRed] = pixel_color_[y][x][Color::kRed] * 0.393 +
                           pixel_color_[y][x][Color::kGreen] * 0.769 +
                           pixel_color_[y][x][Color::kBlue] * 0.189;
      sepia[Color::kGreen] = pixel_color_[y][x][Color::kRed] * 0.349 +
                             pixel_color_[y][x][Color::kGreen] * 0.686 +
                             pixel_color_[y][x][Color::kBlue] * 0.168;
      sepia[Color::kBlue] = pixel_color_[y][x][Color::kRed] * 0.272 +
                            pixel_color_[y][x][Color::kGreen] * 0.534 +
                            pixel_color_[y][x][Color::kBlue] * 0.131;
      for (uint16_t color = 0; color < 3; ++color) {
        sepia[color] = std::min(sepia[color], 255.0);
        pixel_color_[y][x][color] = static_cast<uint8_t>(sepia[color]);
      }
    }
  }
}

void ImageBmp::Compress(size_t width, size_t height) {
  std::vector<std::vector<std::vector<uint8_t>>> new_pixel_color;
  double y_coefficient = 1.0 * static_cast<double>(information_header_.height) /
                         static_cast<double>(height);
  double x_coefficient = 1.0 * static_cast<double>(information_header_.width) /
                         static_cast<double>(width);
  new_pixel_color.resize(height);
  for (uint32_t y = 0; y < height; ++y) {
    new_pixel_color[y].resize(width);
    for (uint32_t x = 0; x < width; ++x) {
      new_pixel_color[y][x] =
          pixel_color_[static_cast<size_t>(y * y_coefficient)]
                      [static_cast<size_t>(x * x_coefficient)];
    }
  }
  pixel_color_ = std::move(new_pixel_color);
  uint32_t new_size = height * width * colors_in_pixel_;
  uint32_t tmp = header_.size - information_header_.image_size + new_size;
  information_header_.height = height;
  information_header_.width = width;
  information_header_.image_size = new_size;
  header_.size -= tmp;
}
