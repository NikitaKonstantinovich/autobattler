cmake_minimum_required(VERSION 3.22)
project(autobattler LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(ab_core
    src/app/rng_mersenne.cpp
 "src/app/character.cpp" "src/app/monster.cpp")
target_include_directories(ab_core PUBLIC include)
target_compile_features(ab_core PUBLIC cxx_std_20)

if(MSVC)
  target_compile_options(ab_core PRIVATE /W4 /permissive-)
else()
  target_compile_options(ab_core PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_executable(ab_cli
    src/ui/cli/main.cpp
 "src/app/character.cpp" "src/app/monster.cpp")
target_link_libraries(ab_cli PRIVATE ab_core)
