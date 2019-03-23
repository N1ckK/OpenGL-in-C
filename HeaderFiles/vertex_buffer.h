#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include "../HeaderFiles/launch_options.h"

#if STANDALONE
#include "../HeaderFiles/opengl.h"
#else
#include <GL/glew.h>
#endif

#include "defines.h"


void VertexBufferCreate(VERTEX_BUFFER* vb, void* vertices, int numVertices){
    // Create Vertex Array
    glGenVertexArrays(1, &(vb -> vao));
    // Bind Vertex Array
    glBindVertexArray(vb -> vao);

    // GPU Buffer for storing Vertex on GPU
    glGenBuffers(1, &(vb -> bufferID));
    // Bind buffer vertexBuffer (use buffer)
    glBindBuffer(GL_ARRAY_BUFFER, vb -> bufferID);
    // write into Buffer
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(struct Vertex),
                 vertices, GL_STATIC_DRAW);
    // activate first attribute (position)
    glEnableVertexAttribArray(0);
    // specify attribute: which attribute, number of elements, type of
    // elements, normalize, bytes to next element(Vertex), offset
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(struct Vertex),
                          (void*) offsetof(struct Vertex, x));

    // activate second attribute (color)
    glEnableVertexAttribArray(1);
    // specify attribute: which attribute, number of elements, type of
    // elements, normalize, bytes to next element(Vertex), offset
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(struct Vertex),
                        (void*) offsetof(struct Vertex, r));

    // unbind vertex array
    glBindVertexArray(0);
}

void VertexBufferDestory(VERTEX_BUFFER* vb){
    // delete vertexbuffer vb
    glDeleteBuffers(1, &(vb -> bufferID));
}

void VertexBufferBind(VERTEX_BUFFER* vb){
    // bind array buffer to vb
    glBindVertexArray(vb -> vao);
}

void VertexBufferUnbind(){
    // unbind array buffer
    glBindVertexArray(0);
}

#endif
