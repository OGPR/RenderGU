#pragma once

//macro to write shader programs inline
#ifndef GLSL
#define GLSL(version,A) "#version " #version "\n" #A
#endif

//// Simple quad render shaders
const char* vertexShaderSimpleQuad =
    GLSL(330 core,
    layout(location = 0) in vec3 aPos;
    layout(location = 1) in vec2 aTexCoord;

    out vec2 TexCoord;

    uniform mat4 model;


    void main()
    {
    	gl_Position =  model * vec4(aPos , 1.0);
        TexCoord = aTexCoord;
    }
);

const char* fragmentShaderSimpleQuad =
    GLSL(330 core,
	in vec2 TexCoord;
    out vec4 FragColor;

    uniform sampler2D Texture;
    uniform float scrollDistance;

    // For kernel effects
    const float offset = 1.f/300.f;

    void main()
    {
    	// Original
		FragColor = vec4(texture(Texture, vec2(1.0f - TexCoord.s, TexCoord.t)));
		return;

		//// kernel effects
		vec2 offsets[9] = vec2[]
		(
		    vec2(-offset, offset), vec2(0.0f, offset), vec2(offset,  offset),
		    vec2(-offset,   0.0f), vec2(0.0f, 0.0f),   vec2(offset,    0.0f),
		    vec2(-offset, -offset),vec2(0.0f, -offset),  vec2(offset, -offset)
		);

		vec3 texSample[9];
		for(int i = 0; i < 9; ++i)
			texSample[i] = vec3(texture(Texture, TexCoord + offsets[i]));

		/*
		float sharpenKernel[9] = float[]
		(
            -1, -1, -1,
            -1,  9, -1,
            -1, -1, -1
        );
        */

		/*
		// Divide by 16 when setting color vec below
		float blurKernel[9] = float[]
		(
            1, 2, 1,
            2,  4, 2,
            1, 2, 1
        );
        */

		float edgeDetKernel[9] = float[]
		(
            1, 1, 1,
            1,  -8, 1,
            1, 1, 1
        );

		vec3 color = vec3(0.0f);
		for (int i = 0; i < 9; ++i)
			//color += texSample[i] * sharpenKernel[i];
			//color += texSample[i] * blurKernel[i]/16.f;
			color += texSample[i] * edgeDetKernel[i];

		FragColor = vec4(color + scrollDistance, 1.0f);



		//// Scrolling Effect
    	/*
		if (TexCoord.t >= 0 && TexCoord.t > 1 - scrollDistance)
			FragColor = vec4(1.0f, 0.f, 0.f, 1.f);

		else
			FragColor = vec4(texture(Texture, TexCoord));
		*/

    	//Inversion
    	//FragColor = vec4(vec3(1.0f - texture(Texture, TexCoord)),1.0f);

    	//Greyscale
    	/*
    	float R_coeff = 0.2126f;
    	float G_coeff = 0.7152f;
    	float B_coeff = 0.0722f;
    	float Y = (R_coeff * FragColor.r + G_coeff * FragColor.g + B_coeff * FragColor.b);
    	FragColor = vec4(vec3(Y),1.0f);
    	*/
    }
);