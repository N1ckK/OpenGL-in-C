#ifndef DEFINES_H
#define DEFINES_H

#include "../HeaderFiles/launch_options.h"


// Vertex struct for storing points
struct Vertex{
    float x, y, z;
    float r, g, b, a;
};


// Vertexbuffer
typedef struct VertexBuffer{
    GLuint bufferID;
    GLuint vao;
} VERTEX_BUFFER;


// shader
typedef struct Shader{
    GLuint shaderID;
} SHADER;

#endif
