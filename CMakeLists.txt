cmake_minimum_required(VERSION 3.22)
project(autobattler LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(ABUILD_TESTS "Build tests" OFF)

add_library(ab_core
)

target_include_directories(ab_core PUBLIC include)
target_compile_features(ab_core PUBLIC cxx_std_20)

add_executable(ab_cli src/ui/cli/main.cpp)
target_link_libraries(ab_cli PRIVATE ab_core)
