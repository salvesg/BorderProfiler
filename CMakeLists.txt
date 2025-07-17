# CMakeLists for PhotonicExercise

cmake_minimum_required(VERSION 3.7) # Required for openCV
project(PhotonicExercise)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

# Recomended by documentation
set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)

find_package(OpenCV REQUIRED core imgcodecs highgui)

add_executable(PoliteCat src/main.cc)

target_link_libraries(PoliteCat PRIVATE ${OpenCV_LIBS})

target_include_directories(PoliteCat PRIVATE ${OpenCV_INCLUDE_DIRS})
