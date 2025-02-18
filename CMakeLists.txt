cmake_minimum_required(VERSION 3.10)

project(FireParticle)

set(CMAKE_CXX_STANDARD 11)

# Add SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(FireParticle main.cpp)

include(FetchContent)
FetchContent_Declare(
  SDL2
  GIT_REPOSITORY http://github.com/libsdl-org/SDL
  GIT_TAG release-2.30.12
)
FetchContent_MakeAvailable(SDL2)

target_link_libraries(FireParticle ${SDL2_LIBRARIES} SDL2main)