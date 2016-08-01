WOL over Internet
=================

A tool that sends a magic packet over the internet to wakeup a computer over LAN.

Requirements
------------
1. cmake

Install steps
-------------
1. git clone git@github.com:dpadman/wol.git 
2. cd wol
3. mkdir build
4. cd build
5. cmake .. && make
6. ./wol macaddr ipaddr port
