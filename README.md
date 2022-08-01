# RenderGU
Rendering ground up (GU) using modern OpenGL

## Current Engine Features
### Display state scene switching

#### Scene Data Examples
```
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

```
#### SceneData Interface
```
struct SceneData
{
    MenuScreenPrototypeData menuScreenPrototypeData;
    Scene1Data scene1Data;
}sceneData;

```
#### Display State
```
enum E_DISPLAY_STATE
{
    MENU_SCREEN_PROTOTYPE,
    SCENE_1,
    //... etc,
}DISPLAY_STATE;

```
#### Main Display Function
```
void display(SceneData* sceneData)
{
    switch(DISPLAY_STATE)
    {
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
 
		// etc...
        default:
            break;
    }
}

```

#### Call Site (Render Loop)
```
if (DISPLAY_STATE == MENU_SCREEN_PROTOTYPE)
{
	// Example - this will later set shader uniform when rendering
	// to attachments of currently bound framebuffer.
	sceneData.menuScreenPrototypeData.button2 = true; 
}

// Render to attachments of currently bound framebuffer
display(&sceneData)
```
### One-time Intra-Frame Scene Set Up

If there is no VAO do the following for each scene display, once only, inside a frame:

- Create model vertex data -i.e the model
- Write your shaders
- Make the shader program
- Specify the vertices


### Shader Compilation and Linking Utility Functions
#### Function Interfaces
```
unsigned int compileVertexShader(const char* vertexShaderSource);

unsigned int compileFragmentShader(const char* fragmentShaderSource);

unsigned int compileComputeShader(const char* computeShaderSource);

unsigned int linkShaders(
        unsigned int vertexShader,
        unsigned int fragmentShader);

unsigned int linkShaders(unsigned int computeShader);

```
#### Function Call Site
```
*shaderProgram = linkShaders(compileVertexShader(vs), compileFragmentShader(fs));
```

## Real-time Console Performance Data
![Console performance data](Images/EngineFeatures/ConsolePerfMetrics.png)


## Resources
- [LearnOpenGL](https://learnopengl.com/)
- Fundamentals Of Computer Graphics 4th Edition (Marschner, S. and Shirley, P., 2018. Fundamentals of computer graphics. CRC Press.)
- Real Time Rendering 4th Edition (Akenine-Moller, T., Haines, E. and Hoffman,  N., 2019. Real-time rendering. AK Peters/crc Press.)
- [Computer Graphcis with Modern OpenGL](https://www.udemy.com/course/graphics- with-modern-opengl/)


