#pragma once

//macro to write shader programs inline
#ifndef GLSL 
#define GLSL(version,A) "#version " #version "\n" #A
#endif

const char* vertexShaderSource =
    GLSL(330 core,
    uniform float R_ChannelValue;
    uniform float G_ChannelValue;
    uniform float B_ChannelValue;
    layout(location = 0) in vec3 aPos;
    out vec3 vColor;

    void main()
    {
        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
        vColor = vec3(0.f + R_ChannelValue, 0.f + G_ChannelValue, 0.f + B_ChannelValue);
    }
);

const char* fragmentShaderSource =
    GLSL(330 core,
    out vec4 FragColor;
    in vec3 vColor;

    void main()
    {
        FragColor = vec4(vColor, 1.0f);
    }
);

//// Triangle data shaders
const char* vertexShaderSource_Tri =
    GLSL(330 core,
    layout(location = 0) in vec3 aPos;
    layout(location = 1) in vec3 aColour;
    layout(location = 2) in vec2 aTexCoord;
    out vec3 Colour;
    out vec2 TexCoord;

    void main()
    {
        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
        Colour = aColour;
        TexCoord = aTexCoord;
    }
);

const char* fragmentShaderSource_Tri =
    GLSL(330 core,
    out vec4 FragColor;
	in vec3 Colour;
	in vec2 TexCoord;

	uniform sampler2D Texture;

    void main()
    {
        //FragColor = vec4(Colour, 1.0f);
        FragColor = texture(Texture, TexCoord);
    }
);

//// Rectangle data shaders
const char* vertexShaderSource_Rect =
    GLSL(330 core,
    layout(location = 0) in vec3 aPos;
    layout(location = 1) in vec3 aColour;
    layout(location = 2) in vec2 aTexCoord;
    out vec3 Colour;
    out vec2 TexCoord;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;

    void main()
    {
        gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
        Colour = aColour;
        TexCoord = aTexCoord;
    }
);

const char* fragmentShaderSource_Rect =
    GLSL(330 core,
    out vec4 FragColor;
	in vec3 Colour;
	in vec2 TexCoord;

	uniform sampler2D Texture1;
	uniform sampler2D Texture2;
	uniform bool vertFlip = false;
	uniform float texture2Amount = 0.2f;

    void main()
    {
        //FragColor = vec4(Colour, 1.0f);
    	if (vertFlip)
			FragColor = mix(texture(Texture1, TexCoord), texture(Texture2, vec2(1.0 - TexCoord.x, TexCoord.y)), texture2Amount);
    	else
			FragColor = mix(texture(Texture1, TexCoord), texture(Texture2, TexCoord), texture2Amount);
    }
);

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

const char* fragmentShaderSource_Cube =
    GLSL(330 core,
    out vec4 FragColor;
	in vec2 TexCoord;

	uniform sampler2D Texture1;
	uniform sampler2D Texture2;
	uniform bool vertFlip = false;
	uniform float texture2Amount = 0.2f;

    void main()
    {
        //FragColor = vec4(Colour, 1.0f);
    	if (vertFlip)
			FragColor = mix(texture(Texture1, TexCoord), texture(Texture2, vec2(1.0 - TexCoord.x, TexCoord.y)), texture2Amount);
    	else
			FragColor = mix(texture(Texture1, TexCoord), texture(Texture2, TexCoord), texture2Amount);
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
const char* vertexShaderSource_Cube_Raw_Target =
    GLSL(330 core,
    layout(location = 0) in vec3 aPos;
	layout(location = 1) in vec3 aNormal;
	layout(location = 2) in vec2 aTexCoords;

	out vec3 Normal;
	out vec3 FragPos;
	out vec2 TexCoords;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;

    vec4 vertexWS;

    void main()
    {
        gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
        vertexWS = model * vec4(aPos, 1.0f);
        FragPos = vec3(vertexWS);
        Normal = aNormal;
        TexCoords = aTexCoords;
    }
);

const char* fragmentShaderSource_Cube_Raw_Target =
    GLSL(330 core,
    in vec3 FragPos;
    in vec3 Normal;
    in vec2 TexCoords;
    out vec4 FragColor;

    uniform struct Material
	{
    	sampler2D ambientMap;
    	sampler2D diffuseMap;
    	sampler2D specularMap;
    	unsigned int shine;
	} material;


	uniform struct DirectionalLight
	{
		vec3 direction;
		vec3 source;
		vec3 ambient;
		vec3 diffuse;
		vec3 specular;
	} directionalLight;

	uniform struct PointLight
	{
		vec3 pos;
		vec3 source;
		vec3 ambient;
		vec3 diffuse;
		vec3 specular;

		// Attenuation factors for
		// F_att = 1/(K_c + K_l*d + K_q*d*d), where
		// F_att is the attenuation value, K_c are constants, and
		// d is the distance from the fragment to the light source

		float K_c;
		float K_l;
		float K_q;
	} pointLight;

	uniform struct SpotLight
	{
		vec3 pos;

		vec3 direction;
		vec3 source;
		vec3 ambient;
		vec3 diffuse;
		vec3 specular;

	} spotLight;


	uniform vec3 viewPos;
	uniform unsigned int PhongExp;
	uniform bool ambientLight;
	uniform bool diffuseLight;
	uniform bool specularLight;
	uniform bool isLightDirectional;
	uniform bool isLightPoint;
	uniform bool isLightSpot;
	uniform bool attenuation;



    void main()
    {
		// Ambient
		float ambientStrength = ambientLight ?  1.f : 0.f;
		vec3 ambientColor;
		if (isLightDirectional)
			ambientColor = directionalLight.source * directionalLight.ambient * ambientStrength * vec3(texture(material.ambientMap, TexCoords));
		else if (isLightPoint)
			ambientColor = pointLight.source * pointLight.ambient * ambientStrength * vec3(texture(material.ambientMap, TexCoords));
		else if (isLightSpot)
			ambientColor = spotLight.source * spotLight.ambient * ambientStrength * vec3(texture(material.ambientMap, TexCoords));

		// Diffuse
		vec3 lightDir;
		if (isLightDirectional)
			lightDir = normalize(-directionalLight.direction);
		else if (isLightPoint)
			lightDir = normalize(pointLight.pos - FragPos);
		else if (isLightSpot)
			lightDir = normalize(spotLight.pos - FragPos);

		float diffuseReflectionFactor;
		vec3 diffuseColor;
		float cutoff = 3.14f * 12.5f/180.f;
		if (isLightSpot && (acos(dot(spotLight.direction, -lightDir)) > cutoff))
		{
			diffuseReflectionFactor = 0.f;
			diffuseColor = vec3(0.f);
			ambientColor = vec3(0.f);
		}
		else
		{
			diffuseReflectionFactor= diffuseLight? max(dot(Normal, lightDir), 0.0f) : 0.f;
			if (isLightDirectional)
				diffuseColor = directionalLight.source * directionalLight.diffuse * diffuseReflectionFactor * vec3(texture(material.diffuseMap, TexCoords));
			else if (isLightPoint)
				diffuseColor = pointLight.source * pointLight.diffuse * diffuseReflectionFactor * vec3(texture(material.diffuseMap, TexCoords));
			else if (isLightSpot)
				diffuseColor = spotLight.source * spotLight.diffuse * diffuseReflectionFactor * vec3(texture(material.diffuseMap, TexCoords));
		}


		// Specular
		float specularReflectionFactor;
		vec3 specularColor;
		if (isLightSpot && (acos(dot(spotLight.direction, -lightDir)) > cutoff))
		{
			specularReflectionFactor = 0.f;
			specularColor = vec3(0.f);
		}
		else
		{
			float specularStrength = 0.5f;
			vec3 viewDir = normalize(viewPos - FragPos);
			vec3 reflectDir = reflect(-lightDir, Normal);
			specularReflectionFactor = specularLight ? pow(max(dot(reflectDir, viewDir), 0.0f), material.shine) : 0.f;
			if (isLightDirectional)
				specularColor = directionalLight.source * directionalLight.specular * specularReflectionFactor * vec3(texture(material.specularMap, TexCoords));
			else if (isLightPoint)
				specularColor = pointLight.source * pointLight.specular * specularReflectionFactor * vec3(texture(material.specularMap, TexCoords));
			else if (isLightSpot)
				specularColor = spotLight.source * spotLight.specular * specularReflectionFactor * vec3(texture(material.specularMap, TexCoords));
		}

		// Attenuation
		// Apply to all components for now, so we don't get stacking with more than 1 light source
		if (attenuation && isLightPoint)
		{
			float d = length(pointLight.pos - FragPos);
			float F_att = 1.f/(pointLight.K_c + pointLight.K_l * d + pointLight.K_q * d * d);
			ambientColor *= F_att;
			diffuseColor *= F_att;
			specularColor *= F_att;
		}


		//Final Color
		vec3 finalColor =  ambientColor + diffuseColor + specularColor;
    	FragColor = vec4(finalColor, 1.f);
    }
);

const char* vertexShaderSource_Cube_Raw_LightSource =
    GLSL(330 core,
    layout(location = 0) in vec3 aPos;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;

    void main()
    {
        gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    }
);

const char* fragmentShaderSource_Cube_Raw_LightSource =
    GLSL(330 core,
    out vec4 FragColor;

	uniform vec3 lightSource;

    void main()
    {
    	FragColor = vec4(lightSource, 1.0f);
    }
);

const char* vertexShaderFloor =
    GLSL(330 core,
    layout(location = 0) in vec3 aPos;
	layout(location = 1) in vec2 aTexCoords;

	out vec2 TexCoords;

	uniform mat4 model;
	uniform mat4 view;
	uniform mat4 projection;

    void main()
    {
        gl_Position = projection * view * model * vec4(aPos, 1.0);
        TexCoords = aTexCoords;
    }
);

const char* fragmentShaderFloor =
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
			FragColor = texture(Texture, TexCoords);
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

    // NDC assumed, no need for matrices

    void main()
    {
    	gl_Position = vec4(aPos , 1.0);
        TexCoord = aTexCoord;
    }
);

const char* fragmentShaderSource_SimpleQuad =
    GLSL(330 core,
	in vec2 TexCoord;
    out vec4 FragColor;

    uniform sampler2D Texture;
    uniform float scrollDistance;


    void main()
    {
    	//// Scrolling Effect

		if (TexCoord.t >= 0 && TexCoord.t > 1 - scrollDistance)
			FragColor = vec4(1.0f, 0.f, 0.f, 1.f);

		else
			FragColor = vec4(texture(Texture, TexCoord));

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


