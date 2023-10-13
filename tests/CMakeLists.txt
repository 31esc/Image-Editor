cmake_minimum_required(VERSION 3.20)

project(ImageEditorTests)

find_package(GTest REQUIRED CONFIG)

add_executable(Tests test_project.cpp)
add_dependencies(Tests ImageEditorLib)

target_include_directories(
    Tests
    PUBLIC
    ${CMAKE_SOURCE_DIR}/lib
)

target_link_libraries(
    Tests
    PUBLIC
    ImageEditorLib
    GTest::gtest GTest::gtest_main
)

target_include_directories(Tests PRIVATE tests)
