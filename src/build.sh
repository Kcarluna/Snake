#!/bin/sh

set -xe

g++ -std=c++17 main.cpp Snake.cpp -o Snake.o `pkg-config sdl2 --cflags --libs` && ./Snake.o
