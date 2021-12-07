#pragma once

// Will get clash with C floor() at call site if you call it floor!
float floor_model[] =
{
    // positions		// Tex coord
    // Tri 1
    //x     y      z
    1.0f, -0.5f,  1.0f, 1.f, 0.f,    //"bottom" right
    -1.0f, -0.5f,  1.0f, 0.f, 0.f,	  //"bottom" left
    -1.0f, -0.5f, -1.0f, 0.f, 1.f,    // "top" left

    // Tri 2
    //x     y      z
    1.0f, -0.5f,  1.0f, 1.f, 0.f,    // "bottom" right"
    -1.0f, -0.5f, -1.0f, 0.f, 1.f,    // "top" left"
    1.0f, -0.5f, -1.0f, 1.f, 1.f,    // "top" right
};
