cmake_minimum_required(VERSION 2.8.12)

project(dlib_cpp)
add_subdirectory(../dlib-19.21/dlib dlib_build)

find_package(OpenCV QUIET)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(image_dlib image_dlib.cpp)
target_link_libraries(image_dlib dlib::dlib ${OpenCV_LIBS} )

add_executable(video_dlib video_dlib.cpp)
target_link_libraries(video_dlib dlib::dlib ${OpenCV_LIBS} )

add_executable(webcam_dlib webcam_dlib.cpp)
target_link_libraries(webcam_dlib dlib::dlib ${OpenCV_LIBS} )

