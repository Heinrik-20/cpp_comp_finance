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

add_subdirectory(DefInt)
add_subdirectory(BinModel)
add_subdirectory(Options)

target_link_libraries(main PRIVATE DefInt Options BinModel)

enable_testing()

add_executable(CPPNumerical ${CMAKE_CURRENT_LIST_DIR}/c2Tests.cpp)

add_subdirectory(Oracle)

target_link_libraries(CPPNumerical DefInt Oracle BinModel Options)
target_link_libraries(CPPNumerical GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(CPPNumerical)