cmake_minimum_required(VERSION 3.7)
project(glproject)

set(CMAKE_CXX_STANDARD 14)
SET( CMAKE_CXX_FLAGS "-pg -O3")
set(SOURCE_FILES main.cpp glad.c stb_image.cpp stb_image.h shader_program.cpp shader_program.h camera.cpp camera.h shader.cpp shader.h texture2d.cpp texture2d.h glutilprimitives.cpp glutilprimitives.h simplexnoise.cpp simplexnoise.h OctaveNoise.cpp OctaveNoise.h murmurhash3.cpp murmurhash3.h Hasher.h interpolation_functions.cpp interpolation_functions.h ease_functions.cpp ease_functions.h GradientNoiseContributor.cpp GradientNoiseContributor.h ValueNoiseContributor.cpp ValueNoiseContributor.h)
include_directories("include/")
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} -lglfw3 -lopengl32)