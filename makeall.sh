#!/usr/bin/env bash

make clean

pushd glpng
make
sudo make install
popd

make
