#include <stdio.h>
#include <Windows.h>

#include "../HeaderFiles/opengl.h"


void* getOpenGLProcAddress(const char* name) {
	void *function = wglGetProcAddress(name);
	if (function == NULL) {
		printf("[ERROR] Could not load the following function: %s\n", name);
	}
	return function;
}

#define Win32GetOpenGLFunction(Name) Name = (w##Name *)getOpenGLProcAddress(#Name)

wglGenVertexArrays* glGenVertexArrays;
wglBindVertexArray* glBindVertexArray;
wglGenBuffers* glGenBuffers;
wglBindBuffer* glBindBuffer;
wglBufferData* glBufferData;
wglEnableVertexAttribArray* glEnableVertexAttribArray;
wglVertexAttribPointer* glVertexAttribPointer;
wglDeleteBuffers* glDeleteBuffers;
wglDeleteProgram* glDeleteProgram;
wglUseProgram* glUseProgram;
wglCreateShader* glCreateShader;
wglShaderSource* glShaderSource;
wglCompileShader* glCompileShader;
wglGetShaderiv* glGetShaderiv;
wglGetShaderInfoLog* glGetShaderInfoLog;
wglAttachShader* glAttachShader;
wglLinkProgram* glLinkProgram;
wglDetachShader* glDetachShader;
wglDeleteShader* glDeleteShader;
wglCreateProgram* glCreateProgram;

void loadOpenGLFunctions() {
	//Context must be loaded
	Win32GetOpenGLFunction(glGenVertexArrays);
	Win32GetOpenGLFunction(glBindVertexArray);
	Win32GetOpenGLFunction(glGenBuffers);
	Win32GetOpenGLFunction(glBindBuffer);
	Win32GetOpenGLFunction(glBufferData);
	Win32GetOpenGLFunction(glEnableVertexAttribArray);
	Win32GetOpenGLFunction(glVertexAttribPointer);
	Win32GetOpenGLFunction(glDeleteBuffers);
	Win32GetOpenGLFunction(glDeleteProgram);
	Win32GetOpenGLFunction(glUseProgram);
	Win32GetOpenGLFunction(glCreateShader);
	Win32GetOpenGLFunction(glShaderSource);
	Win32GetOpenGLFunction(glCompileShader);
	Win32GetOpenGLFunction(glGetShaderiv);
	Win32GetOpenGLFunction(glGetShaderInfoLog);
	Win32GetOpenGLFunction(glAttachShader);
	Win32GetOpenGLFunction(glLinkProgram);
	Win32GetOpenGLFunction(glDetachShader);
	Win32GetOpenGLFunction(glDeleteShader);
	Win32GetOpenGLFunction(glCreateProgram);
}
