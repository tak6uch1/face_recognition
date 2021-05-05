#!/bin/sh

sudo apt-get -y update
sudo apt-get -y upgrade

sudo pip3 install --upgrade pip
sudo pip3 install imutils

sudo apt-get -yV install git
sudo apt-get -yV install build-essential
sudo apt-get -yV install cmake
sudo apt-get -yV install libeigen3-dev
sudo apt-get -yV install libgtk-3-dev
sudo apt-get -yV install qt5-default
sudo apt-get -yV install libvtk7-qt-dev
sudo apt-get -yV install freeglut3-dev
sudo apt-get -yV install libtbb-dev
sudo apt-get -yV install libjpeg-dev
sudo apt-get -yV install libopenjp2-7-dev
sudo apt-get -yV install libpng++-dev
sudo apt-get -yV install libtiff-dev
sudo apt-get -yV install libopenexr-dev
sudo apt-get -yV install libwebp-dev
sudo apt-get -yV install libavresample-dev
sudo apt-get -yV install libhdf5-dev
sudo apt-get -yV install libboost-all-dev
sudo apt-get -yV install libpython3-dev
sudo apt-get -yV install python3-numpy
sudo apt-get -yV install python3-imaging
sudo apt-get -yV install python3-pandas
sudo apt-get -yV install python3-matplotlib
sudo apt-get -yV install python3-gi-cairo
