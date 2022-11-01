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
    var2=$(awk -F'[/.]' '{print $4}' <<< "$f")  	
	
	echo "VAR2 is $var2"
    glslc.exe -fshader-stage=$var2 $var.glsl -o ../bin/$var.spv 
done
echo ""

