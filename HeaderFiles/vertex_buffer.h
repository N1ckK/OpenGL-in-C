#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <GL/glew.h>
#include "defines.h"

void VertexBufferCreate(vertexbuffer* vb, void* vertices, int numVertices){
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
                          offsetof(struct Vertex, x));
    // unbind vertex array
    glBindVertexArray(0);
}

void VertexBufferDestory(vertexbuffer* vb){
    // delete vertexbuffer vb
    glDeleteBuffers(1, &(vb -> bufferID));
}

void VertexBufferBind(vertexbuffer* vb){
    // bind array buffer to vb
    glBindVertexArray(vb -> vao);
}

void VertexBufferUnbind(){
    // unbind array buffer
    glBindVertexArray(0);
}

#endif
