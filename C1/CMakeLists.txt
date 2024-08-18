# https://github.com/sun1211/cmake_with_add_subdirectory for further references

cmake_minimum_required(VERSION 3.10)

project(C1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
  ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
  ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
  ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.0.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(main main.cpp)

enable_testing()

add_executable(C1Tests ${CMAKE_CURRENT_LIST_DIR}/tests.cpp)

target_link_libraries(
    C1Tests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(C1Tests)
