cmake_minimum_required(VERSION 3.16)
project(opencv)

set(CMAKE_CXX_STANDARD 14)
# 可以将下面的路径单独添加到环境变量OpenCV_DIR
set(OpenCV_DIR "E:\\sourcecode\\opencv\\Clion-openCV\\mingw-build\\install")
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs)

add_executable(opencv main.cpp)

target_link_libraries(opencv ${OpenCV_LIBS})