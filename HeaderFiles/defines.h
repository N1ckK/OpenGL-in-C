#ifndef DEFINES_H
#define DEFINES_H

// Vertex struct for storing points
struct Vertex{
    float x;
    float y;
    float z;
};

// Vertexbuffer
typedef struct VertexBuffer{
    GLuint bufferID;
    GLuint vao;
} vertexbuffer;

// shader
typedef struct Shader{
    GLuint shaderID;
} shader;

#endif
