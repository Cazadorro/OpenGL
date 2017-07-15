cmake_minimum_required(VERSION 3.7)
project(glproject)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp glad.c stb_image.cpp stb_image.h shader_program.cpp shader_program.h camera.cpp camera.h shader.cpp shader.h texture2d.cpp texture2d.h glutilprimitives.cpp glutilprimitives.h simplexnoise.cpp simplexnoise.h gradientnoise.cpp gradientnoise.h)
include_directories("include/")
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} -lglfw3 -lopengl32)