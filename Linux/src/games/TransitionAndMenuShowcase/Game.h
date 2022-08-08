#pragma once

struct Screen1Data
{
    unsigned int VAO = 0;
    unsigned int shaderProgram = 0;
    unsigned int texture = 0;
    float colorAmount = 0.0f;
    bool fadeIn = true;
    glm::vec3 color = glm::vec3(1.0f);
};

struct Screen2Data
{
    unsigned int VAO = 0;
    unsigned int shaderProgram = 0;
    unsigned int texture = 0;
    float colorAmount = 0.0f;
    bool fadeIn = true;
    glm::vec3 color = glm::vec3(1.0f);
};

struct MenuScreenData
{
    unsigned int VAO = 0;
    unsigned int shaderProgram = 0;
    unsigned int texture = 0;
};

struct MenuScreenPrototypeData
{
    unsigned int VAO = 0;
    unsigned int shaderProgram = 0;
    unsigned int texture = 0;
    bool button1 = false;
    bool button2 = false;
};

struct Scene1Data
{
    unsigned int VAO = 0;
    unsigned int shaderProgram = 0;
    unsigned int texture = 0;
};

struct Scene2Data
{
    unsigned int VAO = 0;
    unsigned int shaderProgram = 0;
    unsigned int texture = 0;
};


struct SceneData
{
    Screen1Data screen1Data;
    Screen2Data screen2Data;
    MenuScreenData menuScreenData;
    MenuScreenPrototypeData menuScreenPrototypeData;
    Scene1Data scene1Data;
    Scene2Data scene2Data;
    TriangleSceneData triangleSceneData;
    Camera3DSceneData camera3DSceneData;
}sceneData;


enum E_DISPLAY_STATE
{
    START_SCREEN_1,
    START_SCREEN_2,
    MENU_SCREEN,
    MENU_SCREEN_PROTOTYPE,
    SCENE_1,
    SCENE_2,
    TRIANGLE_SCENE,
    CAMERA3D_SCENE
};

void display(SceneData*, E_DISPLAY_STATE*);


bool sceneSwitch = false;

//---START key input variables---//
bool enter_pressed = false;
bool button1_pressed = false;
bool button2_pressed = false;
bool m_pressed = false;
//---END key input variables---//

bool scene1_selected = false;
bool scene2_selected = false;
short int scene1Countdown = 10.0f;
short int scene2Countdown = 10.0f;

//---START Transform matrices init---//
glm::mat4 modelMat = glm::mat4(1.0f);
glm::mat4 viewMat = glm::mat4(1.0f);
glm::mat4 projectionMat = glm::mat4(1.0f);
//---END Transform matrices init---//


//TODO - these should be able to go
//---START Viewport variables---//
float ViewportWidth = 800.0f;
float ViewportHeight = 600.0f;
//---END Viewport variables---//


CameraVariables cameraVariables;

struct GameData
{
    E_DISPLAY_STATE DisplayState = START_SCREEN_1;
    unsigned int gameFrameNumber = 0;
};


void GameFrame(GLFWwindow* window, GameData* gameData)
{
    E_DISPLAY_STATE* DISPLAY_STATE = &gameData->DisplayState;
    unsigned int* frameNumber = &gameData->gameFrameNumber;

    // Do we switch display state?
    if (*DISPLAY_STATE == START_SCREEN_1 &&
            (sceneData.screen1Data.colorAmount < 0.0f ||
            (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS && !enter_pressed)))
    {
        enter_pressed = true;
        *DISPLAY_STATE = START_SCREEN_2;
        sceneSwitch = true;
    }

    if(glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_RELEASE && enter_pressed)
    {
        enter_pressed = false;
    }


    if (*DISPLAY_STATE == START_SCREEN_2 &&
            (sceneData.screen2Data.colorAmount < 0.0f || (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS && !enter_pressed)))
    {
        enter_pressed = true;
        *DISPLAY_STATE = MENU_SCREEN;
        sceneSwitch = true;
    }

    if (*DISPLAY_STATE == MENU_SCREEN)
    {
        if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS)
        {
            *DISPLAY_STATE = MENU_SCREEN_PROTOTYPE;
        }

        if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS)
        {
            *DISPLAY_STATE = TRIANGLE_SCENE;
        }

        if (glfwGetKey(window, GLFW_KEY_F3) == GLFW_PRESS)
        {
            *DISPLAY_STATE = CAMERA3D_SCENE;
        }
    }


    if (*DISPLAY_STATE == MENU_SCREEN_PROTOTYPE)
    {
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && !button1_pressed)
        {
            button1_pressed = true;
            sceneData.menuScreenPrototypeData.button1 = true;
            scene1_selected = true;
        }

        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_RELEASE && button1_pressed)
        {
            button1_pressed = false;
        }

        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS && !button2_pressed)
        {
            button2_pressed = true;
            sceneData.menuScreenPrototypeData.button2 = true;   
            scene2_selected = true;
        }

        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_RELEASE && button2_pressed)
        {
            button2_pressed = false;
        }

        if (scene1_selected)
        {
            if (scene1Countdown < 0)
            {
                *DISPLAY_STATE = SCENE_1;
                scene1_selected = false;
                sceneData.menuScreenPrototypeData.button1 = false;
                scene1Countdown = 10.0f;
            }

            scene1Countdown -= 61.0f * deltaTime;
        }

        if (scene2_selected)
        {
            if (scene2Countdown < 0)
            {
                *DISPLAY_STATE = SCENE_2;
                scene2_selected = false;
                sceneData.menuScreenPrototypeData.button2 = false;
                scene2Countdown = 10.0f;
            }


            scene2Countdown -= 61.0f * deltaTime;
        }

    }

    // Handle return to menu
    if (*DISPLAY_STATE != MENU_SCREEN
        && *DISPLAY_STATE != START_SCREEN_1
        && *DISPLAY_STATE != START_SCREEN_2)
    {

        if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS && !m_pressed)
        {
            m_pressed = true;

            if (*DISPLAY_STATE == SCENE_1
                || *DISPLAY_STATE == SCENE_2)
            {
                *DISPLAY_STATE = MENU_SCREEN_PROTOTYPE;
            }
            else
            {
                *DISPLAY_STATE = MENU_SCREEN;
            }
        }

    }

    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_RELEASE && m_pressed)
    {
        m_pressed = false;
    }

    if (*DISPLAY_STATE == CAMERA3D_SCENE)
    {
        processInputCamera(window, &cameraVariables, deltaTime);

        //Per frame transform matrix reset and reassignment
        modelMat = glm::mat4(1.f);
        modelMat = glm::rotate(modelMat, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        
        viewMat = glm::mat4(1.f);
        //viewMat = glm::translate(viewMat, glm::vec3(0.0f, 0.0f, -3.0f));
        viewMat = glm::lookAt(
                cameraVariables.cameraPos,
                cameraVariables.cameraPos + cameraVariables.cameraLookDirection,
                cameraVariables.cameraUp);

        projectionMat = glm::mat4(1.f);
        projectionMat = glm::perspective(glm::radians(45.0f), ViewportWidth/ViewportHeight, 0.1f, 100.0f); 


        sceneData.camera3DSceneData.model = cube;
        sceneData.camera3DSceneData.modelMat = modelMat;
        sceneData.camera3DSceneData.viewMat = viewMat;
        sceneData.camera3DSceneData.projectionMat = projectionMat;
    }

    if (*DISPLAY_STATE == TRIANGLE_SCENE)
    {
        sceneData.triangleSceneData.fadeAmount += 0.01f;
    }




    printf("\rDISPLAY STATE is %i ", *DISPLAY_STATE);
    fflush(stdout);
    // Draw to screen
    display(&sceneData, DISPLAY_STATE);

    ++*frameNumber;


    if (*frameNumber < 11)
        printf("Game Frame Time:  %f ms\n", deltaTime * 1000.0f);
    else
        printf("\rGame Frame Time:  %f ms", deltaTime * 1000.0f);
    fflush(stdout);
    
    // Print frame time
    if (sceneSwitch)
    {
        *frameNumber = 0;
        sceneSwitch = false;
    }

}

//--------------------------------------------------------------------------------------------

void displayPlane(unsigned int* VAO, unsigned int* shaderProgram, unsigned int* texture, float* colorAmount, bool* fadeIn, glm::vec3* color)
{
    if (!*VAO)
    {

        float vertexDataArr[18] = {0};
        float* vertexData = vertexDataArr;

        // Tri 1
        
        // Row 1 (top left)
        *vertexData++ = -1; // x
        *vertexData++ = 1; // y
        *vertexData++ = 0; // z

        // Row 2 (bottom left)
        *vertexData++ = -1; // x
        *vertexData++ = -1; // y
        *vertexData++ = 0; // z

        // Row 3 (bottom right)
        *vertexData++ = 1; // x
        *vertexData++ = -1; // y
        *vertexData++ = 0; // z
        
        // Tri 2
        
        // Row 4 (top right)
        *vertexData++ = 1; // x
        *vertexData++ = 1; // y
        *vertexData++ = 0; // z
        
        // Row 5 (top left)
        *vertexData++ = -1; // x
        *vertexData++ = 1; // y
        *vertexData++ = 0; // z
        
        // Row 6 (bottom right)
        *vertexData++ = 1; // x
        *vertexData++ = -1; // y
        *vertexData++ = 0; // z
        
        // Write shaders
        const char* vs =
            GLSL(330 core,
            layout(location = 0) in vec3 inPos;

            void main()
            {
                gl_Position = vec4(inPos, 2.0f);
            }
            );
        const char* fs =
            GLSL(330 core,
            out vec4 FragColor;

            uniform float multiplier;
            uniform float color_r;
            uniform float color_g;
            uniform float color_b;

            void main()
            {
                FragColor = vec4(multiplier * vec3(color_r, color_g, color_b) , 1.0f);
            }
            );

        // Make Shader Program
       *shaderProgram = linkShaders(compileVertexShader(vs), compileFragmentShader(fs));

        // Specify Vertices
        specifyVertices(vertexDataArr, 18, VAO); 
    } // !VAO

    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(*shaderProgram);

    if (*fadeIn)
    {
        *colorAmount += deltaTime * 0.2f;
        if (*colorAmount > 1.0f) // To delay the fade out effect (i.e stay at full color), change this (e.g to 1.5f)
            *fadeIn = false;
    }
    else
    {
        *colorAmount -= deltaTime * 0.2f;
    }

    glUniform1f(glGetUniformLocation(*shaderProgram, "multiplier"), *colorAmount); 
    glUniform1f(glGetUniformLocation(*shaderProgram, "color_r"), (*color)[0]); 
    glUniform1f(glGetUniformLocation(*shaderProgram, "color_g"), (*color)[1]); 
    glUniform1f(glGetUniformLocation(*shaderProgram, "color_b"), (*color)[2]); 
    glBindVertexArray(*VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void displayPlane_withTex(unsigned int* VAO, unsigned int* shaderProgram, unsigned int* texture, float* colorAmount, bool* fadeIn)
{
    if (!*VAO) // Create model, specify vertices and compile shaders in only once in the loop that this function will be called in
    {
        float vertexDataArr[30] = {0};
        float* vertexData = vertexDataArr;
        
        // Tri 1
        
        // Row 1 (top left)
        *vertexData++ = -1; // x
        *vertexData++ = 1; // y
        *vertexData++ = 0; // z

        // Row 2 (bottom left)
        *vertexData++ = -1; // x
        *vertexData++ = -1; // y
        *vertexData++ = 0; // z

        // Row 3 (bottom right)
        *vertexData++ = 1; // x
        *vertexData++ = -1; // y
        *vertexData++ = 0; // z
        
        // Tri 2
        
        // Row 4 (top right)
        *vertexData++ = 1; // x
        *vertexData++ = 1; // y
        *vertexData++ = 0; // z
        
        // Row 5 (top left)
        *vertexData++ = -1; // x
        *vertexData++ = 1; // y
        *vertexData++ = 0; // z
        
        // Row 6 (bottom right)
        *vertexData++ = 1; // x
        *vertexData++ = -1; // y
        *vertexData++ = 0; // z

        // Texture coords
        // Tri 1

        // (top left)
        *vertexData++ = 0; 
        *vertexData++ = 1; 

        // (bottom left)
        *vertexData++ = 0; 
        *vertexData++ = 0; 

        // (bottom right)
        *vertexData++ = 1; 
        *vertexData++ = 0; 
        
        // Tri 2
        
        // (top right)
        *vertexData++ = 1; 
        *vertexData++ = 1; 
        
        // (top left)
        *vertexData++ = 0; 
        *vertexData++ = 1; 
        
        // (bottom right)
        *vertexData++ = 1; 
        *vertexData++ = 0;
            
        // Write shaders
        const char* vs =
            GLSL(330 core,
            layout(location = 0) in vec3 inPos;
            layout(location = 1) in vec2 inTexCoord;

            out vec2 texCoord;

            void main()
            {
                mat4 modelMat;
                gl_Position = vec4(inPos, 4.0f);
                texCoord = inTexCoord;
            }
            );
        const char* fs =
            GLSL(330 core,
            in vec2 texCoord;
            out vec4 FragColor;

            uniform float multiplier;
            uniform sampler2D Texture;

            float _multiplier;  // local var as can't assign to uniform
            void main()
            {
                _multiplier = multiplier;
                if (_multiplier > 1.0f)
                    _multiplier = 1.0f;

                vec4 texColor = texture(Texture, texCoord);
                if (texColor.a < 0.1f)
                    discard;

                FragColor = _multiplier * texColor ;
            }
            );

        // Make Shader Program
        *shaderProgram = linkShaders(compileVertexShader(vs), compileFragmentShader(fs));

        // Specify Vertices
        BindVBO(CreateVBO());
        AllocateMemoryVBO(30, vertexDataArr);
        *VAO = CreateVAO();
        assert(*VAO);
        BindVAO(*VAO);
        SetAttribute(0, 3, 0, (void*)0);
        SetAttribute(1, 2, 0, (void*)(18 * sizeof(float)));

        // Load Texture
        glActiveTexture(GL_TEXTURE0);
        glGenTextures(1, texture);
        glBindTexture(GL_TEXTURE_2D, *texture);
        // set the texture wrapping/filtering options (on the currently bound texture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load and generate the texture
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load("resources/grass.png", &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_set_flip_vertically_on_load(false);
        stbi_image_free(data);

    } // !VAO

    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(*shaderProgram);

    if (*fadeIn)
    {
        *colorAmount += deltaTime * 0.2f;
        if (*colorAmount > 1.05f) // To delay the fade out effect (i.e stay at full color), change this (e.g to 1.5f)
            *fadeIn = false;
    }
    else
    {
        *colorAmount -= deltaTime * 0.2f;
    }

    glUniform1f(glGetUniformLocation(*shaderProgram, "Texture"), 0); 
    glUniform1f(glGetUniformLocation(*shaderProgram, "multiplier"), *colorAmount); 
    glBindVertexArray(*VAO);
    glBindTexture(GL_TEXTURE_2D, *texture);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void display2DMenu(unsigned int* VAO, unsigned int* shaderProgram, unsigned int* texture)
{
    if (!*VAO) // Create model, specify vertices and compile shaders in only once in the loop that this function will be called in
    {
        float vertexDataArr[30] = {0};
        float* vertexData = vertexDataArr;
        
        // Tri 1
        
        // Row 1 (top left)
        *vertexData++ = -1; // x
        *vertexData++ = 1; // y
        *vertexData++ = 0; // z

        // Row 2 (bottom left)
        *vertexData++ = -1; // x
        *vertexData++ = -1; // y
        *vertexData++ = 0; // z

        // Row 3 (bottom right)
        *vertexData++ = 1; // x
        *vertexData++ = -1; // y
        *vertexData++ = 0; // z
        
        // Tri 2
        
        // Row 4 (top right)
        *vertexData++ = 1; // x
        *vertexData++ = 1; // y
        *vertexData++ = 0; // z
        
        // Row 5 (top left)
        *vertexData++ = -1; // x
        *vertexData++ = 1; // y
        *vertexData++ = 0; // z
        
        // Row 6 (bottom right)
        *vertexData++ = 1; // x
        *vertexData++ = -1; // y
        *vertexData++ = 0; // z

        // Texture coords
        // Tri 1

        // (top left)
        *vertexData++ = 0; 
        *vertexData++ = 1; 

        // (bottom left)
        *vertexData++ = 0; 
        *vertexData++ = 0; 

        // (bottom right)
        *vertexData++ = 1; 
        *vertexData++ = 0; 
        
        // Tri 2
        
        // (top right)
        *vertexData++ = 1; 
        *vertexData++ = 1; 
        
        // (top left)
        *vertexData++ = 0; 
        *vertexData++ = 1; 
        
        // (bottom right)
        *vertexData++ = 1; 
        *vertexData++ = 0;
            
        // Write shaders
        const char* vs =
            GLSL(330 core,
            layout(location = 0) in vec3 inPos;
            layout(location = 1) in vec2 inTexCoord;

            out vec2 texCoord;

            void main()
            {
                gl_Position = vec4(inPos, 1.0f);
                texCoord = inTexCoord;
            }
            );
        const char* fs =
            GLSL(330 core,
            in vec2 texCoord;
            out vec4 FragColor;

            uniform sampler2D Texture;
            uniform bool Button1;
            uniform bool Button2;

            void main()
            {
                vec4 texColor = texture(Texture, texCoord);
                FragColor = texColor;
            }
            );

        // Make Shader Program
        *shaderProgram = linkShaders(compileVertexShader(vs), compileFragmentShader(fs));

        // Specify Vertices
        BindVBO(CreateVBO());
        AllocateMemoryVBO(30, vertexDataArr);
        *VAO = CreateVAO();
        assert(*VAO);
        BindVAO(*VAO);
        SetAttribute(0, 3, 0, (void*)0);
        SetAttribute(1, 2, 0, (void*)(18 * sizeof(float)));

        // Load Texture
        glActiveTexture(GL_TEXTURE0);
        glGenTextures(1, texture);
        glBindTexture(GL_TEXTURE_2D, *texture);
        // set the texture wrapping/filtering options (on the currently bound texture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load and generate the texture
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load("resources/2DMenu/2D_Menu.png", &width, &height, &nrChannels, 0);
        if (data)
        {
            // No A here (even though png)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_set_flip_vertically_on_load(false);
        stbi_image_free(data);
    } // !VAO

    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(*shaderProgram);

    glUniform1f(glGetUniformLocation(*shaderProgram, "Texture"), 0); 
    glBindVertexArray(*VAO);
    glBindTexture(GL_TEXTURE_2D, *texture);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void display2DMenuPrototype(unsigned int* VAO, unsigned int* shaderProgram, unsigned int* texture, bool button1, bool button2)
{
    if (!*VAO) // Create model, specify vertices and compile shaders in only once in the loop that this function will be called in
    {
        float vertexDataArr[30] = {0};
        float* vertexData = vertexDataArr;
        
        // Tri 1
        
        // Row 1 (top left)
        *vertexData++ = -1; // x
        *vertexData++ = 1; // y
        *vertexData++ = 0; // z

        // Row 2 (bottom left)
        *vertexData++ = -1; // x
        *vertexData++ = -1; // y
        *vertexData++ = 0; // z

        // Row 3 (bottom right)
        *vertexData++ = 1; // x
        *vertexData++ = -1; // y
        *vertexData++ = 0; // z
        
        // Tri 2
        
        // Row 4 (top right)
        *vertexData++ = 1; // x
        *vertexData++ = 1; // y
        *vertexData++ = 0; // z
        
        // Row 5 (top left)
        *vertexData++ = -1; // x
        *vertexData++ = 1; // y
        *vertexData++ = 0; // z
        
        // Row 6 (bottom right)
        *vertexData++ = 1; // x
        *vertexData++ = -1; // y
        *vertexData++ = 0; // z

        // Texture coords
        // Tri 1

        // (top left)
        *vertexData++ = 0; 
        *vertexData++ = 1; 

        // (bottom left)
        *vertexData++ = 0; 
        *vertexData++ = 0; 

        // (bottom right)
        *vertexData++ = 1; 
        *vertexData++ = 0; 
        
        // Tri 2
        
        // (top right)
        *vertexData++ = 1; 
        *vertexData++ = 1; 
        
        // (top left)
        *vertexData++ = 0; 
        *vertexData++ = 1; 
        
        // (bottom right)
        *vertexData++ = 1; 
        *vertexData++ = 0;
            
        // Write shaders
        const char* vs =
            GLSL(330 core,
            layout(location = 0) in vec3 inPos;
            layout(location = 1) in vec2 inTexCoord;

            out vec2 texCoord;

            void main()
            {
                gl_Position = vec4(inPos, 1.0f);
                texCoord = inTexCoord;
            }
            );
        const char* fs =
            GLSL(330 core,
            in vec2 texCoord;
            out vec4 FragColor;

            uniform sampler2D Texture;
            uniform bool Button1;
            uniform bool Button2;

            void main()
            {
                vec4 texColor = texture(Texture, texCoord);
                if (Button1)
                {
                    if (texColor.r > 0.41f && texColor.r < 0.44f)
                    {
                        FragColor = vec4(0.12f, 0.24f, 0.36f, 1.0f);
                    }
                    else
                    {
                        FragColor = texColor;
                    }
                    return;
                }

                if (Button2)
                {
                    if (texColor.r < 0.41f)
                    {
                        FragColor = vec4(0.12f, 0.24f, 0.36f, 1.0f);
                    }
                    else
                    {
                        FragColor = texColor;
                    }
                    return;
                }

                FragColor = texColor;
            }
            );

        // Make Shader Program
        *shaderProgram = linkShaders(compileVertexShader(vs), compileFragmentShader(fs));

        // Specify Vertices
        BindVBO(CreateVBO());
        AllocateMemoryVBO(30, vertexDataArr);
        *VAO = CreateVAO();
        assert(*VAO);
        BindVAO(*VAO);
        SetAttribute(0, 3, 0, (void*)0);
        SetAttribute(1, 2, 0, (void*)(18 * sizeof(float)));

        // Load Texture
        glActiveTexture(GL_TEXTURE0);
        glGenTextures(1, texture);
        glBindTexture(GL_TEXTURE_2D, *texture);
        // set the texture wrapping/filtering options (on the currently bound texture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load and generate the texture
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load("resources/2DMenu/2D_Menu_Prototype.png", &width, &height, &nrChannels, 0);
        if (data)
        {
            // No A here (even though png)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_set_flip_vertically_on_load(false);
        stbi_image_free(data);
    } // !VAO

    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(*shaderProgram);

    glUniform1f(glGetUniformLocation(*shaderProgram, "Texture"), 0); 
    glUniform1i(glGetUniformLocation(*shaderProgram, "Button1"), button1); 
    glUniform1i(glGetUniformLocation(*shaderProgram, "Button2"), button2); 
    glBindVertexArray(*VAO);
    glBindTexture(GL_TEXTURE_2D, *texture);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void displayScene1(unsigned int* VAO, unsigned int* shaderProgram, unsigned int* texture)
{
    if (!*VAO) // Create model, specify vertices and compile shaders in only once in the loop that this function will be called in
    {
        float vertexDataArr[30] = {0};
        float* vertexData = vertexDataArr;
        
        // Tri 1
        
        // Row 1 (top left)
        *vertexData++ = -1; // x
        *vertexData++ = 1; // y
        *vertexData++ = 0; // z

        // Row 2 (bottom left)
        *vertexData++ = -1; // x
        *vertexData++ = -1; // y
        *vertexData++ = 0; // z

        // Row 3 (bottom right)
        *vertexData++ = 1; // x
        *vertexData++ = -1; // y
        *vertexData++ = 0; // z
        
        // Tri 2
        
        // Row 4 (top right)
        *vertexData++ = 1; // x
        *vertexData++ = 1; // y
        *vertexData++ = 0; // z
        
        // Row 5 (top left)
        *vertexData++ = -1; // x
        *vertexData++ = 1; // y
        *vertexData++ = 0; // z
        
        // Row 6 (bottom right)
        *vertexData++ = 1; // x
        *vertexData++ = -1; // y
        *vertexData++ = 0; // z

        // Texture coords
        // Tri 1

        // (top left)
        *vertexData++ = 0; 
        *vertexData++ = 1; 

        // (bottom left)
        *vertexData++ = 0; 
        *vertexData++ = 0; 

        // (bottom right)
        *vertexData++ = 1; 
        *vertexData++ = 0; 
        
        // Tri 2
        
        // (top right)
        *vertexData++ = 1; 
        *vertexData++ = 1; 
        
        // (top left)
        *vertexData++ = 0; 
        *vertexData++ = 1; 
        
        // (bottom right)
        *vertexData++ = 1; 
        *vertexData++ = 0;
            
        // Write shaders
        const char* vs =
            GLSL(330 core,
            layout(location = 0) in vec3 inPos;
            layout(location = 1) in vec2 inTexCoord;

            out vec2 texCoord;

            void main()
            {
                gl_Position = vec4(inPos, 1.0f);
                texCoord = inTexCoord;
            }
            );
        const char* fs =
            GLSL(330 core,
            in vec2 texCoord;
            out vec4 FragColor;

            uniform sampler2D Texture;

            void main()
            {
                vec4 texColor = texture(Texture, texCoord);
                FragColor = texColor;
            }
            );

        // Make Shader Program
        *shaderProgram = linkShaders(compileVertexShader(vs), compileFragmentShader(fs));

        // Specify Vertices
        BindVBO(CreateVBO());
        AllocateMemoryVBO(30, vertexDataArr);
        *VAO = CreateVAO();
        assert(*VAO);
        BindVAO(*VAO);
        SetAttribute(0, 3, 0, (void*)0);
        SetAttribute(1, 2, 0, (void*)(18 * sizeof(float)));

        // Load Texture
        glActiveTexture(GL_TEXTURE0);
        glGenTextures(1, texture);
        glBindTexture(GL_TEXTURE_2D, *texture);
        // set the texture wrapping/filtering options (on the currently bound texture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load and generate the texture
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load("resources/scene1.png", &width, &height, &nrChannels, 0);
        if (data)
        {
            // We have text in the png, need A
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_set_flip_vertically_on_load(false);
        stbi_image_free(data);
    } // !VAO

    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(*shaderProgram);

    glUniform1f(glGetUniformLocation(*shaderProgram, "Texture"), 0); 
    glBindVertexArray(*VAO);
    glBindTexture(GL_TEXTURE_2D, *texture);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void displayScene2(unsigned int* VAO, unsigned int* shaderProgram, unsigned int* texture)
{
    if (!*VAO) // Create model, specify vertices and compile shaders in only once in the loop that this function will be called in
    {
        float vertexDataArr[30] = {0};
        float* vertexData = vertexDataArr;
        
        // Tri 1
        
        // Row 1 (top left)
        *vertexData++ = -1; // x
        *vertexData++ = 1; // y
        *vertexData++ = 0; // z

        // Row 2 (bottom left)
        *vertexData++ = -1; // x
        *vertexData++ = -1; // y
        *vertexData++ = 0; // z

        // Row 3 (bottom right)
        *vertexData++ = 1; // x
        *vertexData++ = -1; // y
        *vertexData++ = 0; // z
        
        // Tri 2
        
        // Row 4 (top right)
        *vertexData++ = 1; // x
        *vertexData++ = 1; // y
        *vertexData++ = 0; // z
        
        // Row 5 (top left)
        *vertexData++ = -1; // x
        *vertexData++ = 1; // y
        *vertexData++ = 0; // z
        
        // Row 6 (bottom right)
        *vertexData++ = 1; // x
        *vertexData++ = -1; // y
        *vertexData++ = 0; // z

        // Texture coords
        // Tri 1

        // (top left)
        *vertexData++ = 0; 
        *vertexData++ = 1; 

        // (bottom left)
        *vertexData++ = 0; 
        *vertexData++ = 0; 

        // (bottom right)
        *vertexData++ = 1; 
        *vertexData++ = 0; 
        
        // Tri 2
        
        // (top right)
        *vertexData++ = 1; 
        *vertexData++ = 1; 
        
        // (top left)
        *vertexData++ = 0; 
        *vertexData++ = 1; 
        
        // (bottom right)
        *vertexData++ = 1; 
        *vertexData++ = 0;
            
        // Write shaders
        const char* vs =
            GLSL(330 core,
            layout(location = 0) in vec3 inPos;
            layout(location = 1) in vec2 inTexCoord;

            out vec2 texCoord;

            void main()
            {
                gl_Position = vec4(inPos, 1.0f);
                texCoord = inTexCoord;
            }
            );
        const char* fs =
            GLSL(330 core,
            in vec2 texCoord;
            out vec4 FragColor;

            uniform sampler2D Texture;

            void main()
            {
                vec4 texColor = texture(Texture, texCoord);
                FragColor = texColor;
            }
            );

        // Make Shader Program
        *shaderProgram = linkShaders(compileVertexShader(vs), compileFragmentShader(fs));

        // Specify Vertices
        BindVBO(CreateVBO());
        AllocateMemoryVBO(30, vertexDataArr);
        *VAO = CreateVAO();
        assert(*VAO);
        BindVAO(*VAO);
        SetAttribute(0, 3, 0, (void*)0);
        SetAttribute(1, 2, 0, (void*)(18 * sizeof(float)));

        // Load Texture
        glActiveTexture(GL_TEXTURE0);
        glGenTextures(1, texture);
        glBindTexture(GL_TEXTURE_2D, *texture);
        // set the texture wrapping/filtering options (on the currently bound texture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load and generate the texture
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load("resources/scene2.png", &width, &height, &nrChannels, 0);
        if (data)
        {
            // We have text in the png, need A
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_set_flip_vertically_on_load(false);
        stbi_image_free(data);
    } // !VAO

    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(*shaderProgram);

    glUniform1f(glGetUniformLocation(*shaderProgram, "Texture"), 0); 
    glBindVertexArray(*VAO);
    glBindTexture(GL_TEXTURE_2D, *texture);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void display(SceneData* sceneData, E_DISPLAY_STATE* DISPLAY_STATE)
{
    switch(*DISPLAY_STATE)
    {
        case START_SCREEN_1:
            displayPlane_withTex(&sceneData->screen1Data.VAO,
                    &sceneData->screen1Data.shaderProgram,
                    &sceneData->screen1Data.texture,
                    &sceneData->screen1Data.colorAmount,
                    &sceneData->screen1Data.fadeIn);
            break;

        case START_SCREEN_2:
            displayPlane(&sceneData->screen2Data.VAO,
                    &sceneData->screen2Data.shaderProgram,
                    &sceneData->screen2Data.texture,
                    &sceneData->screen2Data.colorAmount,
                    &sceneData->screen2Data.fadeIn,
                    &sceneData->screen2Data.color);
            break;
        case MENU_SCREEN:
            display2DMenu(&sceneData->menuScreenData.VAO,
                    &sceneData->menuScreenData.shaderProgram,
                    &sceneData->menuScreenData.texture);
            break;
        case MENU_SCREEN_PROTOTYPE:
            display2DMenuPrototype(&sceneData->menuScreenPrototypeData.VAO,
                    &sceneData->menuScreenPrototypeData.shaderProgram,
                    &sceneData->menuScreenPrototypeData.texture,
                    sceneData->menuScreenPrototypeData.button1,
                    sceneData->menuScreenPrototypeData.button2);
            break;
        case SCENE_1:
            displayScene1(&sceneData->scene1Data.VAO,
                    &sceneData->scene1Data.shaderProgram,
                    &sceneData->scene1Data.texture);
            break;
        case SCENE_2:
            displayScene2(&sceneData->scene2Data.VAO,
                    &sceneData->scene2Data.shaderProgram,
                    &sceneData->scene2Data.texture);
            break;
        case TRIANGLE_SCENE:
            displayTriangle(&sceneData->triangleSceneData.VAO,
                       &sceneData->triangleSceneData.shaderProgram,
                       &sceneData->triangleSceneData.fadeAmount);
            break;
        case CAMERA3D_SCENE:
            displayCube(&sceneData->camera3DSceneData.VAO,
                    &sceneData->camera3DSceneData.shaderProgram,
                    &sceneData->camera3DSceneData.texture,
                    sceneData->camera3DSceneData.model,
                    &sceneData->camera3DSceneData.modelMat,
                    &sceneData->camera3DSceneData.viewMat,
                    &sceneData->camera3DSceneData.projectionMat);


            break;
            
        default:
            break;
    }
}
