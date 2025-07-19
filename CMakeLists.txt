# CMakeLists for PhotonicExercise

cmake_minimum_required(VERSION 3.7) # Required for openCV
project(PhotonicExercise)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

find_package(OpenCV REQUIRED 
  COMPONENTS core imgcodecs highgui)


add_library( ImageBorders STATIC
  lib/ImageBorders.cc
)

target_include_directories( ImageBorders
  PUBLIC ${CMAKE_SOURCE_DIR}/include ${OpenCV_INCLUDE_DIRS} 
)

target_link_libraries( ImageBorders
  PUBLIC ${OpenCV_LIBS}
)

find_package(OpenMP)

if(OpenMP_CXX_FOUND)
  target_link_libraries( ImageBorders
    PUBLIC OpenMP::OpenMP_CXX
  )
else()
  message(WARNING "OpenMP for C++ not found. Configuring build w/o parallel support")
endif()

add_executable(CreateBorders ${CMAKE_SOURCE_DIR}/src/ApplySobelFilter.cc)
target_link_libraries(CreateBorders PRIVATE ImageBorders)

