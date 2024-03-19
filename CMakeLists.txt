cmake_minimum_required(VERSION 3.12)
project(Cson C)

set(CMAKE_C_STANDARD 23)

include_directories(src)

set(LIBCSON_SRC src/libcson.c)
add_library(libcson_static STATIC ${LIBCSON_SRC})

set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_executable(ll_test tests/ll_test.c)
