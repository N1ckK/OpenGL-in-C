#ifndef DEFINES_H
#define DEFINES_H

#include "../HeaderFiles/launch_options.h"

// Vertex struct for storing points and color
struct Vertex{
    float x, y, z;
    float r, g, b, a;
};


// Vertexbuffer
typedef struct VertexBuffer{
    GLuint bufferID;
    GLuint vao;
} VERTEX_BUFFER;


// index buffer
typedef GLuint INDEX_BUFFER;


// shader
typedef struct Shader{
    GLuint shaderID;
} SHADER;

#endif
