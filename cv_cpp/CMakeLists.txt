cmake_minimum_required(VERSION 2.8.12)

project(cv_cpp)

find_package(OpenCV QUIET)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(image image.cpp)
target_link_libraries(image ${OpenCV_LIBS} )

add_executable(video video.cpp)
target_link_libraries(video ${OpenCV_LIBS} )

add_executable(webcam webcam.cpp)
target_link_libraries(webcam ${OpenCV_LIBS} )

