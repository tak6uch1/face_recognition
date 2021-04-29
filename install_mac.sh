#!/bin/sh

which brew > /dev/null
if [ $? -ne 0 ]; then
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
fi
brew install wget
brew install boost
brew install boost-python3
brew install opencv
brew install cmake
brew install xquartz
ln -s /opt/X11/include/X11 /usr/local/include/X11

sudo pip3 install imutils

# Dlib
#   Note: Check the latest version of dlib on http://dlib.net/
wget http://dlib.net/files/dlib-19.21.tar.bz2
tar zxf dlib-19.21.tar.bz2
cd dlib-19.21
sudo python setup.py install

cd ..
wget http://dlib.net/files/shape_predictor_68_face_landmarks.dat.bz2
bunzip2 shape_predictor_68_face_landmarks.dat.bz2
