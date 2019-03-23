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
#include "../HeaderFiles/shader.h"

// for mandelbrot fractal
//#include "../Resources/Mandelbrot_OpenGL/mandelbrot.h"

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
#ifdef BORDERLESS_WINDOW
    printf("Launch Option: BORDERLESS_WINDOW\n");
    flags = flags | SDL_WINDOW_BORDERLESS;
#endif

// FULLSCREEN
#ifdef FULLSCREEN_WINDOW
    printf("Launch Option: FULLSCREEN_WINDOW\n");
    flags = flags | SDL_WINDOW_FULLSCREEN_DESKTOP;
#endif

    // Creating the window, title, x_window, y_window, width, height, flags
    window = SDL_CreateWindow("Title", SDL_WINDOWPOS_CENTERED,
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
        { 0.5,  0.5, 0.0,   1.0, 0.0, 0.0, 1.0}
    };
    int numVertices = 4;

    // for mandelbrot fractal
    // struct Vertex* vertices = calcVerts(800, 600);
    // int numVertices = 800 * 600;

    // create Vertex Buffer
    VERTEX_BUFFER vbuffer;
    VertexBufferCreate(&vbuffer, vertices, numVertices);
    VertexBufferUnbind();

    SHADER shader;
    char vertexShader[256] = "Source Files/shaders/basic330.vert";
    char fragmentShader[256] = "Source Files/shaders/basic330.frag";
    int size_t = 256;
    ShaderCreate(&shader, vertexShader, fragmentShader, size_t);
    ShaderBind(&shader);

    // for timing
    int perfCounterFreq = SDL_GetPerformanceFrequency();
    int startCounter = SDL_GetPerformanceCounter();
    float delta = 0.0;

    // Window loop
    bool running = true;

    while(running){
        // specifies color with with the screen should be cleared
        glClearColor(0.0, 0.0, 0.0, 1.0);
        // clears the screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Wire-frame mode
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        // bind to buffer
        VertexBufferBind(&vbuffer);
        // draw binded buffer, mode, start, count of vertices
        glDrawArrays(GL_TRIANGLE_STRIP, 0, numVertices);
        // unbind buffer
        VertexBufferUnbind();

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
        int endCounter = SDL_GetPerformanceCounter();
        int counterElapsed = endCounter - startCounter;
        delta = (float) counterElapsed / (float) perfCounterFreq;
        unsigned short fps = (short int)((float) perfCounterFreq /
                                         (float) counterElapsed);
        startCounter = endCounter;
    }
    return 0;
}
