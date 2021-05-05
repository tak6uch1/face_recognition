#!/bin/sh

# OpenCV
cd /usr/local
sudo mkdir opencv4
cd /usr/local/opencv4
sudo git clone https://github.com/opencv/opencv.git
sudo git clone https://github.com/opencv/opencv_contrib.git

cd opencv
sudo mkdir build
cd build

sudo cmake \
-D CMAKE_BUILD_TYPE=Release \
-D CMAKE_INSTALL_PREFIX=/usr/local \
-D OPENCV_EXTRA_MODULES_PATH=/usr/local/opencv4/opencv_contrib/modules \
PYTHON3_EXECUTABLE=/usr/lib/python3.7 \
PYTHON_INCLUDE_DIR=/usr/include/python3.7 \
PYTHON_INCLUDE_DIR2=/usr/include/arm-linux-gnueabihf/python3.7m \
PYTHON_LIBRARY=/usr/lib/arm-linux-gnueabihf/libpython3.7m.so \
PYTHON3_NUMPY_INCLUDE_DIRS=/usr/lib/python3/dist-packages/numpy/core/include \
-S /usr/local/opencv4/opencv

sudo make -j7
sudo make install
