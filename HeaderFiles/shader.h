#ifndef SHADER_H
#define SHADER_H

#include "../HeaderFiles/launch_options.h"

#if STANDALONE
#include "../HeaderFiles/opengl.h"
#else
#include <GL/glew.h>
#endif

#include "defines.h"
#include <string.h>


GLuint ShaderCompile(char* shaderSource, GLenum type);

void ShaderParse(char* filename, char* contents, int size_t);

void ShaderCreate(SHADER* sh, char* vertexShaderFilename,
                              char* fragmentShaderFilename, int size_t);

void ShaderDestroy(SHADER* sh);

void ShaderBind(SHADER* sh);

void ShaderUnbind();

#endif
