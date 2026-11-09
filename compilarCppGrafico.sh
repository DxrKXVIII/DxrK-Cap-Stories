#!/bin/bash
g++ src/main.cpp src/motor_lore.cpp src/motor_graficos.cpp -o DxrKCapStories -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
