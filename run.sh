#!/bin/sh
g++ main.cpp -O2 allegro_interface.cpp display.cpp app_controller.cpp particles.cpp common.cpp $(pkg-config --libs allegro-5 allegro_font-5  allegro_primitives-5 allegro_image-5 allegro_ttf-5 allegro_dialog-5 --cflags) -lm -o build/out
./build/out