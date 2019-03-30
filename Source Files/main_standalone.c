#include <stdio.h>
#include <stdbool.h>

#include <GL/gl.h>
//#include <GL/glu.h>
//#include <GL/glext.h>
#include <Windows.h>
#include <sys/time.h>

#include "../HeaderFiles/opengl.h"
#include "../HeaderFiles/defines.h"
#include "../HeaderFiles/vertex_buffer.h"
#include "../HeaderFiles/index_buffer.h"
#include "../HeaderFiles/shader.h"


LRESULT CALLBACK MessageHandler(HWND hwnd, UINT uMsg, WPARAM wParam,
                                                      LPARAM lParam){
    switch (uMsg) {
    case WM_CLOSE:
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        break;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int main(int argc, char* argv[]){

    HINSTANCE hInstance = GetModuleHandle(0);
    HWND hwnd;
    WNDCLASS wc;
    MSG msg;

    wc = (WNDCLASS) {};
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = MessageHandler;
    wc.hInstance = hInstance;
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszClassName = "WINAPI Test";

    if (! RegisterClass(&wc)){
        printf("[ERROR] Could not register the window.\n");
    }

    hwnd = CreateWindow("WINAPI Test", "OpenGL", WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT, CW_USEDEFAULT, WIDTH_WINDOW, HEIGHT_WINDOW,
                0, 0, hInstance, 0);

#if BORDERLESS_WINDOW
    printf("[INFO] Launch Option: BORDERLESS_WINDOW 1\n");
    SetWindowLong(hwnd, GWL_STYLE, 0);
#endif

#if FULLSCREEN_WINDOW
    printf("[INFO] Launch Option: FULLSCREEN_WINDOW 1\n");
    RECT rect;
    if(!GetWindowRect(GetDesktopWindow(), &rect)){
        printf("[Error] Could not get Screen dimensions\n");
        printf("%ld\n", GetLastError());
    }

    SetWindowPos(hwnd, HWND_BOTTOM, rect.left, rect.top, rect.right - rect.left,
                                    rect.bottom - rect.top, SWP_NOZORDER);
#endif

    ShowWindow(hwnd, SW_SHOW);

    printf("[INFO] Window successfully created.\n");

    HDC hdc = GetDC(hwnd);

    PIXELFORMATDESCRIPTOR pixelFormat = {};
    pixelFormat.nSize = sizeof(pixelFormat);
    pixelFormat.nVersion = 1;
    pixelFormat.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
    pixelFormat.cColorBits = 24;
    pixelFormat.cRedBits = 8;
    pixelFormat.cGreenBits = 8;
    pixelFormat.cBlueBits = 8;
    pixelFormat.cAlphaBits = 8;

    int index = ChoosePixelFormat(hdc, &pixelFormat);
    PIXELFORMATDESCRIPTOR supportedPixelFormat;
    DescribePixelFormat(hdc, index, sizeof(PIXELFORMATDESCRIPTOR), &supportedPixelFormat);
    SetPixelFormat(hdc, index, &supportedPixelFormat);

    HGLRC context = wglCreateContext(hdc);
    if (!wglMakeCurrent(hdc, context)){
        printf("[ERROR] Could not create OpenGL context\n");
        return 0;
    }

    // loading GL functions from opengl.h
    loadOpenGLFunctions();

    //printing GL-Version
    printf("[INFO] OpenGL Version: %s\n", glGetString(GL_VERSION));

    // triangle
    struct Vertex vertices[] = {
        // x     y    z      r    g    b    a
        {-0.5, -0.5, 0.0,   1.0, 0.0, 0.0, 1.0},
        {-0.5,  0.5, 0.0,   0.0, 1.0, 0.0, 1.0},
        { 0.5, -0.5, 0.0,   0.0, 0.0, 1.0, 1.0},
        { 0.5,  0.5, 0.0,   1.0, 0.5, 0.5, 1.0}
    };
    unsigned int numVertices = 4;

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
    VertexBufferCreate(&vbuffer, vertices, numVertices);
    VertexBufferUnbind();


    // creating shader;
    SHADER shader;
    char vertexShader[256];
    char fragmentShader[256];

#if SHADER_VERSION == 330
    printf("[INFO] Launch Option: SHADER_VERSION 330\n");
    strcpy(vertexShader, "Source Files/shaders/basic330.vert");
    strcpy(fragmentShader, "Source Files/shaders/basic330.frag");
#elif SHADER_VERSION == 120
    printf("[INFO] Launch Option: SHADER_VERSION 120\n");
    strcpy(vertexShader, "Source Files/shaders/basic120.vert");
    strcpy(fragmentShader, "Source Files/shaders/basic120.frag");
#endif

    ShaderCreate(&shader, vertexShader, fragmentShader, sizeof(vertexShader));
    ShaderBind(&shader);

    // Window loop
    bool running = true;

    clock_t start, stop, delta = 0;
    unsigned short frames = 0;

    while(running){

        start = clock();

        while(PeekMessage(&msg, 0, 0, 0, PM_REMOVE)){
            if (msg.message == WM_QUIT) running = false;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // specifies color with with the screen should be cleared
        glClearColor(0.1, 0.1, 0.1, 1.0);
        // clears the screen
        glClear(GL_COLOR_BUFFER_BIT);

        // bind to buffer
        VertexBufferBind(vbuffer);
        IndexBufferBind(ibuffer);
        // draw binded buffer, mode, start, count of vertices

        //glDrawArrays(GL_TRIANGLE_STRIP, 0, numVertices);
        glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);

        // unbind buffer
        VertexBufferUnbind();
        IndexBufferUnbind(ibuffer);

        // switch buffers (doublebuffering)
        SwapBuffers(hdc);

        stop = clock();
        delta += stop - start;
        frames ++;
        if ((delta / (double) CLOCKS_PER_SEC) > 1){
            printf("[INFO] FPS: %d\n", frames);
            frames = delta = 0;
        }

    }
    return 0;
}
