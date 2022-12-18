cmake_minimum_required(VERSION 3.24)
project(aoc2022)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)
set(ABSL_BUILD_TESTING OFF)
FetchContent_Declare(
        absl
        GIT_REPOSITORY "https://github.com/abseil/abseil-cpp.git"
        GIT_TAG "20220623.1"
        GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(absl)

add_executable(aoc2022 main.cpp)
target_link_libraries(aoc2022 absl::strings)
