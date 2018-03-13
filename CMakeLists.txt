cmake_minimum_required(VERSION 3.9)
project(OpenCV)

set(CMAKE_CXX_STANDARD 11)
add_executable(OpenCV main.cpp)
set(OpenCV_LIBS opencv_core330 opencv_imgproc330 opencv_highgui330 opencv_imgcodecs330 opencv_objdetect330 opencv_video330 opencv_videoio330)
target_link_libraries(OpenCV ${OpenCV_LIBS})