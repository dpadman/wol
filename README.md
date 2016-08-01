WOL over Internet
=================

A tool that sends a magic packet over the internet to wakeup a computer.

Requirements
------------
1. cmake

Install steps
-------------
git clone 
cd wol
mkdir build
cd build
cmake .. && make
./wol <macaddr> <ipaddr> <port>
