cmake_minimum_required(VERSION  3.22)
# set(CMAKE_MINOR_VERSION 3.1)

project(vrml)

include_directories(/usr/local/include/opencv4/)
link_directories(/usr/local/lib)

add_executable(vrml main.cc ./parser/ele.cpp ./parser/wrl.cpp )


target_link_libraries(vrml opencv_core opencv_highgui opencv_imgproc opencv_imgcodecs)