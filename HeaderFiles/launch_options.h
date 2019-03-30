/*
    If STANDALONE is 1, the project will compile without SDL and GLEW.
    Instead it will use the WINAPI and manually include OpenGL.
    Else if STANDALONE is 0 the Project will use GLEW and SDL to Compile the
    Project
*/
#define STANDALONE 1

// ============================================================================

/*
    Determines the Width of the window.
*/
#define WIDTH_WINDOW 800

/*
    Determines the height of the window.
*/
#define HEIGHT_WINDOW 600

// ============================================================================

/*
    Determines wheather the window should appear in fullscreen.
*/
#define FULLSCREEN_WINDOW 0

/*
    Determines wheather the window should appear borderless.
*/
#define BORDERLESS_WINDOW 0

// ============================================================================

/*
    Specifies the shader Version to be used. Supported Versions are:
    120 and 330. 330 is recommended.
*/
#define SHADER_VERSION 330

// ============================================================================
