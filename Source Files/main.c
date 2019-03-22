#include <stdio.h>
#include <stdbool.h>

//#define GLEW_STATIC
#include <GL/glew.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

//#pragma comment(lib, "SDL2.lib")
//#pragma comment(lib, "glew32.lib")
//#pragma comment(lib, "opengl32.lib")

#include "../HeaderFiles/vertex_buffer.h"
#include "../HeaderFiles/defines.h"
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

    // Creating the window, title, x_window, y_window, width, height, flags
    window = SDL_CreateWindow("Title", SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                              800, 600, SDL_WINDOW_OPENGL);

    // Creating context for window
    SDL_GLContext glContext = SDL_GL_CreateContext(window);

    // init glew
    GLenum error = glewInit();
    if (error != GLEW_OK){
        printf("Error: %s\n", glewGetErrorString(error));
        scanf("%s", NULL);
        return -1;
    }

    // printing GL-Version
    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));

    // triangle
    struct Vertex vertices[] = {
        {-0.5, -0.5, 0.0},
        { 0.0,  0.5, 0.0},
        { 0.5, -0.5, 0.0}
    };
    int numVertices = 3;

    // create Vertex Buffer
    vertexbuffer vbuffer;
    VertexBufferCreate(&vbuffer, vertices, numVertices);
    VertexBufferUnbind();


    shader shader;
    char vertexShader[1024] = "Source Files/shaders/basic.vert";
    char fragmentShader[1024] = "Source Files/shaders/basic.frag";
    int size_t = 1024;
    ShaderCreate(&shader, vertexShader, fragmentShader, size_t);
    ShaderBind(&shader);


    // Window loop
    bool running = true;

    while(running){
        // specifies color with with the screen should be cleared
        glClearColor(0.0, 0.0, 0.0, 1.0);
        // clears the screen
        glClear(GL_COLOR_BUFFER_BIT);

        // bind to buffer
        VertexBufferBind(&vbuffer);
        // draw binded buffer, mode, start, count of vertices
        glDrawArrays(GL_TRIANGLES, 0, numVertices);
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
    }
    return 0;
}
