#!/bin/sh

# Dlib
#   Note: Check the latest version of dlib on http://dlib.net/
wget http://dlib.net/files/dlib-19.21.tar.bz2
bunzip2 dlib-19.21.tar.bz2
tar xf dlib-19.21.tar
cd dlib-19.21
sudo python3 setup.py install

cd ..
wget http://dlib.net/files/shape_predictor_68_face_landmarks.dat.bz2
bunzip2 shape_predictor_68_face_landmarks.dat.bz2
