#!/bin/bash

cmake -B build -S . && cd build && make && mv RenderGU ../bin/RenderGU.bin && cp -r ../resources ../bin
