#!/bin/bash

for f in ./*.glsl
do
    var=$(awk -F'[/.]' '{print $3 "." $4}' <<< "$f")  
    ../../../../../engine/SPIRV_Compile/glslangValidator -G -o ../bin/$var.spv $var.glsl
done
