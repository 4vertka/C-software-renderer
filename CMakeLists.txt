cmake_minimum_required(VERSION 3.16)
project(ZoraidaRenderer)

#set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_C_FLAGS_DEBUG "-O0 -g -Wall -Wextra -Wmissing-braces")
set(CMAKE_C_FLAGS_RELEASE "-O2 -Wall")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(external/minifb)
add_subdirectory(external/SDL)

add_executable(${PROJECT_NAME}
  ./main/main.c
  ./core/renderer.c
  ./core/math/vector.c
  ./core/math/matrix.c
  ./core/line.c
  ./core/mesh.c
  ./core/system/system.c
)


target_include_directories(${PROJECT_NAME} PRIVATE
  ${CMAKE_SOURCE_DIR}/core
)

target_link_libraries(${PROJECT_NAME} PRIVATE minifb::minifb SDL3::SDL3)
