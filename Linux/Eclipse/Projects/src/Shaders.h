#pragma once

//macro to write shader programs inline
#ifndef GLSL 
#define GLSL(version,A) "#version " #version "\n" #A
#endif



//// cube data shaders
const char* vertexShaderSource_Cube =
    GLSL(330 core,
    layout(location = 0) in vec3 aPos;
    layout(location = 1) in vec2 aTexCoord;
    out vec2 TexCoord;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;

    void main()
    {
        gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
        TexCoord = aTexCoord;
    }
);



const char* fragmentShaderSource_Cube_no_mix =
    GLSL(330 core,
    out vec4 FragColor;
	in vec2 TexCoord;

	uniform sampler2D Texture;
	uniform bool visualiseDepthBuffer;

	float near = 0.1f;
	float far = 100.f;
	float LineariseDepth(float depth)
	{
		float z = depth * 2.f - 1.f;
		return (2.f * near * far)/(far + near - z * (far - near));
	}

    void main()
    {
    	if (!visualiseDepthBuffer)
    	{
    		FragColor = texture(Texture, TexCoord);
    	}
    	else
    	{
			//FragColor = vec4(vec3(gl_FragCoord.z), 1.0);
			float depth = LineariseDepth(gl_FragCoord.z)/far*3;
			FragColor = vec4(vec3(depth), 1.f);
    	}
    }
);






const char* fragmentShaderSingleColor =
    GLSL(330 core,
    in vec2 TexCoords;
    out vec4 FragColor;

    uniform sampler2D Texture;
    uniform bool visualiseDepthBuffer;

	float near = 0.1f;
	float far = 100.f;
	float LineariseDepth(float depth)
	{
		float z = depth * 2.f - 1.f;
		return (2.f * near * far)/(far + near - z * (far - near));
	}
    void main()
    {
    	if (!visualiseDepthBuffer)
    	{
			FragColor = vec4(0.04f, 0.28f, 0.26f, 1.f);
    	}
    	else
    	{
			//FragColor = vec4(vec3(gl_FragCoord.z), 1.0);
			FragColor = vec4(0.04f, 0.28f, 0.26f, 1.f);
    	}

    }
);

//// Transparency rectangle shaders
const char* vertexShaderSource_Rect_Transparency =
    GLSL(330 core,
    layout(location = 0) in vec3 aPos;
    layout(location = 1) in vec2 aTexCoord;

    out vec2 TexCoord;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;

    void main()
    {
        gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
        TexCoord = aTexCoord;
    }
);

const char* fragmentShaderSource_Rect_Transparency =
    GLSL(330 core,
	in vec2 TexCoord;
	in vec3 Color;
    out vec4 FragColor;

    uniform sampler2D Texture;


    void main()
    {
    	vec4 texColor = texture(Texture, TexCoord);
    	if (texColor.a < 0.1)
    		discard;
    	FragColor = texColor;
    }
);

// Window
// re-using VShader from rect_transp
const char* fragmentShaderSource_Rect_window =
    GLSL(330 core,
	in vec2 TexCoord;
	in vec3 Color;
    out vec4 FragColor;

    uniform sampler2D Texture;


    void main()
    {
    	FragColor = texture(Texture, TexCoord);
    }
);


//// Simple quad render shaders
const char* vertexShaderSource_SimpleQuad =
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

const char* fragmentShaderSource_SimpleQuad =
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


