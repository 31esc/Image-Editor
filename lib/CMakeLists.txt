cmake_minimum_required(VERSION 3.20)

project(ImageEditorLib)

add_library(ImageEditorLib SHARED bmp.cpp)

target_include_directories(
    ImageEditorLib
    PUBLIC
    ${CMAKE_SOURCE_DIR}
)

target_include_directories(
    ImageEditorLib
    PUBLIC
    ${CMAKE_SOURCE_DIR}/tests
)