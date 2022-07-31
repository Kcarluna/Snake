#!/bin/sh

set -xe

g++ -std=c++17 `pkg-config sdl2 --cflags --libs` main.cpp Snake.cpp -o Snake && ./Snake
