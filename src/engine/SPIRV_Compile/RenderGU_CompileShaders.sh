#!/bin/bash

WorkDir=`pwd`

cd "$WorkDir"
echo ""
awk -F'[/]' '{print "You are compiling shaders located in " $(NF-3) "/" $(NF-2) "/" $(NF-1)}' <<< "$WorkDir"
#echo "You are compiling shaders located in $WorkDir"
echo ""

echo "The shaders being compiled are:"
echo ""
for f in ./*.glsl
do
    var=$(awk -F'[/.]' '{print $3 "." $4}' <<< "$f")  
    ../../../../../engine/SPIRV_Compile/glslangValidator -G -o ../bin/$var.spv $var.glsl
done
echo ""

