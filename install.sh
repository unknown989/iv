#!/bin/sh
echo "Downloading png++"
wget http://download.savannah.nongnu.org/releases/pngpp/png++-0.2.9.tar.gz
echo "Building png++"
mkdir /tmp/png++ && tar --directory=/tmp/png++ -xf png++-0.2.9.tar.gz
cd /tmp/png++ && make && sudo make install
echo "Done Successfly"
