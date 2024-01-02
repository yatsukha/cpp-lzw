cmake_minimum_required(VERSION 3.11)

project(lzw)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -g -march=native")

# -DCUSTOM_CXX_LINKER="--ld-path=/usr/local/bin/ld64.sold"
# otherwise it uses the compiler to deduce it
if(DEFINED CUSTOM_CXX_LINKER)
  add_link_options(${CUSTOM_CXX_LINKER})
endif()

set(IMPLEMENTATION_FILES
  src/lzw/decode.cpp
  src/lzw/encode.cpp)

add_executable(lzw 
  src/main.cpp
  ${IMPLEMENTATION_FILES})

find_package(Threads REQUIRED)

target_link_libraries(lzw PRIVATE Threads::Threads)

target_include_directories(lzw PRIVATE 
  "include")

target_compile_options(lzw PRIVATE
  -Wall
  -Wextra
  -Wpedantic
  -Werror)

## tests

find_package(Catch2 3 REQUIRED)

add_executable(test
  test/test.cpp
  ${IMPLEMENTATION_FILES})

target_link_libraries(test PRIVATE Catch2::Catch2WithMain)
target_include_directories(test PRIVATE 
  "include")
