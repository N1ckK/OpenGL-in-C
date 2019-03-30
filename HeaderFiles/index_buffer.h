#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include "../HeaderFiles/launch_options.h"

#if STANDALONE
#include "../HeaderFiles/opengl.h"
#else
#include <GL/glew.h>
#endif

#include "defines.h"

void IndexBufferCreate(INDEX_BUFFER* ib, void* indices,  unsigned int numIndices){
    // create index buffer
    glGenBuffers(1, ib);
    // bind index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ib);
    // specify buffer data
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(indices),
                 indices, GL_STATIC_DRAW);
}


void IndexBufferDestroy(INDEX_BUFFER* ib){
    glDeleteBuffers(1, ib);
}


void IndexBufferBind(INDEX_BUFFER ib){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
}


void IndexBufferUnbind(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

#endif
