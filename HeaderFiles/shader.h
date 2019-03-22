#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string.h>
#include "defines.h"

GLuint ShaderCompile(char* shaderSource, GLenum type);

void ShaderParse(char* filename, char* contents, int size_t);

void ShaderCreate(shader* sh, char* vertexShaderFilename,
                              char* fragmentShaderFilename, int size_t);

void ShaderDestroy(shader* sh);

void ShaderBind(shader* sh);

void ShaderUnbind();

#endif
