cmake_minimum_required(VERSION 3.10)
project(Tutorial)

include(${CMAKE_SOURCE_DIR}/conan/conanbuildinfo.cmake)
conan_basic_setup(TARGETS KEEP_RPATHS)

set(TARGET_NAME Service)

add_executable(${TARGET_NAME}
  Product.proto
  main.cpp
)

protobuf_generate(TARGET ${TARGET_NAME})

target_link_libraries(${TARGET_NAME}
  PUBLIC CONAN_PKG::protobuf
)

target_include_directories(${TARGET_NAME}
  PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
)