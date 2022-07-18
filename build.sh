#!/bin/sh

set -xe

clang++ -std=c++17 main.cpp Snake.cpp -o Snake `pkg-config sdl2_ttf --cflags --libs` && ./Snake
