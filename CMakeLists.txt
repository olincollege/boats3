# Require the CMake version matching what is included in the latest LTS version
# of Ubuntu, which at the time of writing is 22.04.
cmake_minimum_required(VERSION 3.22)

project(desktop_pet
  VERSION 1.0
  LANGUAGES C
)

set(CMAKE_C_STANDARD 17)

# set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic -Wshadow -Wconversion -Wunreachable-code")
# set(CMAKE_C_FLAGS "-Wall -pedantic -Wunreachable-code")
set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic")

set(CMAKE_C_CLANG_TIDY
  clang-tidy;
  -header-filter=.;
  -checks=*,-llvmlibc-restrict-system-libc-headers,-llvm-header-guard,-altera*;
)

add_subdirectory(scripts)

include(CTest)
find_library(CRITERION criterion REQUIRED)
set(CRITERION_FLAGS --verbose -j1)

add_subdirectory(test)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
