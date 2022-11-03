#!/bin/bash

cmake -B build -S . && cd build && make && mv RenderGU ../bin/out/config/RenderGU.bin && cp -r ../../resources ../
