#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "bmp.hpp"
#include "bmp.hpp"  // Check Guards or pragma.

#include <cstring>
#include <vector>

bool Compare(std::string path, std::string result_path) {
  std::ifstream fd;
  std::ifstream fd_res;
  fd.open(path, std::ios::out | std::ios::binary);
  fd_res.open(result_path, std::ios::out | std::ios::binary);
  if (!fd_res.is_open()) {
    fd.close();
    return false;
  }
  return std::equal(std::istreambuf_iterator<char>(fd.rdbuf()),
                    std::istreambuf_iterator<char>(),
                    std::istreambuf_iterator<char>(fd_res.rdbuf()));
}

TEST_CASE("Read and save") {
  SECTION("test_1") {
    std::string path = "../tests/img/t1_24.bmp";
    std::string result_path = "../img/result_img.bmp";

    ImageBmp image(path);
    image.Save();

    REQUIRE(Compare(path, result_path) == 1);
  }
  SECTION("test_2") {
    std::string path = "../tests/img/Shapes.bmp";
    std::string result_path = "../img/result_img.bmp";

    ImageBmp image(path);
    image.Save();

    REQUIRE(Compare(path, result_path) == 1);
  }
}

TEST_CASE("Negative") {
  SECTION("test_1") {
    std::string path = "../tests/img/tiger.bmp";
    std::string result_path = "../img/result_img.bmp";
    std::string answer = "../tests/img_ans/negative_1.bmp";

    ImageBmp image(path);
    image.Negative();
    image.Save();

    REQUIRE(Compare(answer, result_path) == 1);
  }
  SECTION("test_2") {
    std::string path = "../tests/img/Shapes.bmp";
    std::string result_path = "../img/result_img.bmp";
    std::string answer = "../tests/img_ans/negative_2.bmp";

    ImageBmp image(path);
    image.Negative();
    image.Save();

    REQUIRE(Compare(answer, result_path) == 1);
  }
}

TEST_CASE("Replace_color") {
  SECTION("test_1") {
    std::string path = "../tests/img/Shapes.bmp";
    std::string result_path = "../img/result_img.bmp";
    std::string answer = "../tests/img_ans/replace_color_1.bmp";

    ImageBmp image(path);
    std::vector<uint8_t> old_color = {246, 12, 12};
    std::vector<uint8_t> new_color = {12, 97, 246};
    image.ReplaceColor(old_color, new_color);
    image.Save();

    REQUIRE(Compare(answer, result_path) == 1);
  }
  SECTION("test_2") {
    std::string path = "../tests/img/FLAG_B24.bmp";
    std::string result_path = "../img/result_img.bmp";
    std::string answer = "../tests/img_ans/replace_color_2.bmp";

    ImageBmp image(path);
    std::vector<uint8_t> old_color = {248, 0, 0};
    std::vector<uint8_t> new_color = {255, 255, 255};
    image.ReplaceColor(old_color, new_color);
    image.Save();

    REQUIRE(Compare(answer, result_path) == 1);
  }
}

TEST_CASE("ClarityEnhancement") {
  SECTION("test_1") {
    std::string path = "../tests/img/bear.bmp";
    std::string result_path = "../img/result_img.bmp";
    std::string answer = "../tests/img_ans/clarity_enhancement_1.bmp";

    ImageBmp image(path);
    image.ClarityEnhancement();
    image.Save();

    REQUIRE(Compare(answer, result_path) == 1);
  }
  SECTION("test_2") {
    std::string path = "../tests/img/cat.bmp";
    std::string result_path = "../img/result_img.bmp";
    std::string answer = "../tests/img_ans/clarity_enhancement_2.bmp";

    ImageBmp image(path);
    image.ClarityEnhancement();
    image.Save();

    REQUIRE(Compare(answer, result_path) == 1);
  }
}

TEST_CASE("GaussianBlur") {
  SECTION("test_1") {
    std::string path = "../tests/img/tiger.bmp";
    std::string result_path = "../img/result_img.bmp";
    std::string answer = "../tests/img_ans/gaussian_blur_1.bmp";

    ImageBmp image(path);
    image.GaussianBlur();
    image.Save();

    REQUIRE(Compare(answer, result_path) == 1);
  }
  SECTION("test_2") {
    std::string path = "../tests/img/cat.bmp";
    std::string result_path = "../img/result_img.bmp";
    std::string answer = "../tests/img_ans/gaussian_blur_2.bmp";

    ImageBmp image(path);
    image.GaussianBlur();
    image.Save();

    REQUIRE(Compare(answer, result_path) == 1);
  }
}

TEST_CASE("Grey") {
  SECTION("test_1") {
    std::string path = "../tests/img/cat.bmp";
    std::string result_path = "../img/result_img.bmp";
    std::string answer = "../tests/img_ans/gray_1.bmp";

    ImageBmp image(path);
    image.Gray();
    image.Save();

    REQUIRE(Compare(answer, result_path) == 1);
  }
  SECTION("test_2") {
    std::string path = "../tests/img/sample_1920×1280.bmp";
    std::string result_path = "../img/result_img.bmp";
    std::string answer = "../tests/img_ans/gray_2.bmp";

    ImageBmp image(path);
    image.Gray();
    image.Save();

    REQUIRE(Compare(answer, result_path) == 1);
  }
}

TEST_CASE("Ridge detection") {
  SECTION("test_1") {
    std::string path = "../tests/img/cat.bmp";
    std::string result_path = "../img/result_img.bmp";
    std::string answer = "../tests/img_ans/ridge_detection.bmp";

    ImageBmp image(path);
    image.RidgeDetection();
    image.Save();

    REQUIRE(Compare(answer, result_path) == 1);
  }
}

TEST_CASE("Reduce noise") {
  SECTION("test_1") {
    std::string path = "../tests/img/Highimgnoise.bmp";
    std::string result_path = "../img/result_img.bmp";
    std::string answer = "../tests/img_ans/reduce_noise.bmp";

    ImageBmp image(path);
    image.ReduceNoise();
    image.Save();

    REQUIRE(Compare(answer, result_path) == 1);
  }
}

TEST_CASE("Vignette") {
  SECTION("test_1") {
    std::string path = "../tests/img/cat.bmp";
    std::string result_path = "../img/result_img.bmp";
    std::string answer = "../tests/img_ans/vignette.bmp";

    ImageBmp image(path);
    image.Vignette();
    image.Save();

    REQUIRE(Compare(answer, result_path) == 1);
  }
}

TEST_CASE("Cut") {
  SECTION("test_1") {
    std::string path = "../tests/img/monkey.bmp";
    std::string result_path = "../img/result_img.bmp";
    std::string answer = "../tests/img_ans/cut.bmp";

    ImageBmp image(path);
    image.Cut(650, 650, 500, 500);
    image.Save();

    REQUIRE(Compare(answer, result_path) == 1);
  }
}

TEST_CASE("Compress") {
  SECTION("test_1") {
    std::string path = "../tests/img/bear.bmp";
    std::string result_path = "../img/result_img.bmp";
    std::string answer = "../tests/img_ans/compress_1.bmp";

    ImageBmp image(path);
    image.Compress(400, 400);
    image.Save();

    REQUIRE(Compare(answer, result_path) == 1);
  }
  SECTION("test_2") {
    std::string path = "../tests/img/cat.bmp";
    std::string result_path = "../img/result_img.bmp";
    std::string answer = "../tests/img_ans/compress_2.bmp";

    ImageBmp image(path);
    image.Compress(200, 200);
    image.Save();

    REQUIRE(Compare(answer, result_path) == 1);
  }
}

TEST_CASE("Dramatic sepia") {
  SECTION("test_1") {
    std::string path = "../tests/img/cat.bmp";
    std::string result_path = "../img/result_img.bmp";
    std::string answer = "../tests/img_ans/dramatic_sepia.bmp";

    ImageBmp image(path);
    image.DramaticSepia();
    image.Save();

    REQUIRE(Compare(answer, result_path) == 1);
  }
}
