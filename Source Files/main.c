#include <stdio.h>
#include <stdbool.h>

#include <GL/glew.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include <GL/gl.h>
//#include <GL/glu.h>
//#include <GL/glext.h>

//#pragma comment(lib, "SDL2.lib")
//#pragma comment(lib, "glew32.lib")
//#pragma comment(lib, "opengl32.lib")

//#include "../HeaderFiles/defines.h"
#include "../HeaderFiles/vertex_buffer.h"
#include "../HeaderFiles/index_buffer.h"
#include "../HeaderFiles/shader.h"


int main(int argc, char* argv[]){

    // Declaring the window
    SDL_Window* window;

    // Initing SDL
    SDL_Init(SDL_INIT_EVERYTHING);

    // red color channel size 8 bit -> 0 - 255
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    // green color channel size 8 bit -> 0 - 255
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    // blue color channel size 8 bit -> 0 - 255
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    // alpha channel size 8 bit -> 0 - 255
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    // size of pixel 4*8 = 32 minimum
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    // activate doublebuffering
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    // flags
    int flags = SDL_WINDOW_OPENGL;

// borderless window
#if BORDERLESS_WINDOW
    printf("[INFO] Launch Option: BORDERLESS_WINDOW 1\n");
    flags = flags | SDL_WINDOW_BORDERLESS;
#endif

// FULLSCREEN
#if FULLSCREEN_WINDOW
    printf("[INFO] Launch Option: FULLSCREEN_WINDOW 1\n");
    flags = flags | SDL_WINDOW_FULLSCREEN_DESKTOP;
#endif

    // Creating the window, title, x_window, y_window, width, height, flags
    window = SDL_CreateWindow("C OpenGL", SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                              WIDTH_WINDOW, HEIGHT_WINDOW, flags);

    // Creating context for window
    SDL_GLContext glContext = SDL_GL_CreateContext(window);

    // init glew
    GLenum error = glewInit();
    if (error != GLEW_OK){
        printf("[ERROR] Could not Init Glew: %s\n", glewGetErrorString(error));
        scanf("%s", NULL);
        return -1;
    }

    // printing GL-Version
    printf("[INFO] OpenGL Version: %s\n", glGetString(GL_VERSION));

    // triangle
    struct Vertex vertices[] = {
        // x     y    z      r    g    b    a
        {-0.5, -0.5, 0.0,   1.0, 0.0, 0.0, 1.0},
        {-0.5,  0.5, 0.0,   0.0, 1.0, 0.0, 1.0},
        { 0.5, -0.5, 0.0,   0.0, 0.0, 1.0, 1.0},
        { 0.5,  0.5, 0.0,   1.0, 0.5, 0.5, 1.0}
    };
    int numVertices = 4;

    // indices
    unsigned int indices[] = {
        0, 1, 2,
        1, 2, 3
    };
    unsigned int numIndices = 6;

    
    // declare INDEX_BUFFER
    INDEX_BUFFER ibuffer;
    // create index buffer
    IndexBufferCreate(&ibuffer, indices, numIndices);
    // unbind index buffer
    IndexBufferUnbind();

    // create Vertex Buffer
    VERTEX_BUFFER vbuffer;
    // create Vetexbuffer
    VertexBufferCreate(&vbuffer, vertices, numVertices);
    // vertexbuffer bind
    VertexBufferUnbind();


    // declare shader
    SHADER shader;
    char vertexShader[256];
    char fragmentShader[256];

// shader version
#if SHADER_VERSION == 330
    printf("[INFO] Launch Option: SHADER_VERSION 330\n");
    strcpy(vertexShader, "Source Files/shaders/basic330.vert");
    strcpy(fragmentShader, "Source Files/shaders/basic330.frag");
#elif SHADER_VERSION == 120
    printf("[INFO] Launch Option: SHADER_VERSION 120\n");
    strcpy(vertexShader, "Source Files/shaders/basic120.vert");
    strcpy(fragmentShader, "Source Files/shaders/basic120.frag");
#endif

    // create shader
    ShaderCreate(&shader, vertexShader, fragmentShader, sizeof(vertexShader));
    ShaderBind(&shader);

    // for timing
    int perfCounterFreq = SDL_GetPerformanceFrequency();
    int startCounter = SDL_GetPerformanceCounter();
    int endCounter, counterElapsed;
    unsigned short fps;
    float delta = 0.0;

    // Window loop
    bool running = true;

    while(running){
        // specifies color with with the screen should be cleared
        glClearColor(0.1, 0.1, 0.1, 1.0);
        // clears the screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Wire-frame mode
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        // bind to buffer
        VertexBufferBind(vbuffer);
        IndexBufferBind (ibuffer);

        // draw binded buffer, mode, start, count of vertices (without indexbuffer)
        //glDrawArrays(GL_TRIANGLE_STRIP, 0, numVertices);
        // draw (with indexbuffer): mode, amount, buffer (already bound)
        glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);

        // unbind buffer
        VertexBufferUnbind();
        IndexBufferUnbind();

        // switch buffers (doublebuffering)
        SDL_GL_SwapWindow(window);

        // SDL event declaration
        SDL_Event event;

        // message handler
        while(SDL_PollEvent(&event)){

            // quit event
            if(event.type == SDL_QUIT){
                running = false;
            }
        }

        // time calculations
        endCounter = SDL_GetPerformanceCounter();
        counterElapsed = endCounter - startCounter;
        delta = (float) counterElapsed / (float) perfCounterFreq;
        fps = (short int)((float) perfCounterFreq / (float) counterElapsed);
        startCounter = endCounter;
    }
    return 0;
}
