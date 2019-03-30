#include "../HeaderFiles/shader.h"
#include <stdlib.h>
#include <stdio.h>

GLuint ShaderCompile(char* shaderSource, GLenum type){
    // create id of the shader
    GLuint id = glCreateShader(type);
    //create double pointer to source code
    const char* src = &shaderSource[0];
    // pass source code to Shader id
    glShaderSource(id, 1, &src, 0);
    // compile shader with id
    glCompileShader(id);

    // print compilation errors
    int result;
    // get compilation result
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result != GL_TRUE){
        int length = 0;
        // retrieve length of error message
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        // create string for error message
        char* message = malloc(length * sizeof(char));
        // write error message to string
        glGetShaderInfoLog(id, length, &length, message);
        // print error message
        printf("--------- Shader compilation error -----------\n%s\nErro \
        r code: %x\n================================\n\n", message, result);
        // delete string containing message
        free(message);
    }

    return id;
}

void ShaderParse(char* filename, char* contents, unsigned int buffer_size){
    // create file object
    FILE* file;
    // open the file by creating pointer
    file = fopen(filename, "rb");

    // checking if file is opened
    if (file == NULL){
        printf("[ERROR] File %s not found.\n", filename);
        return;
    }
    // clearing string
    contents[0] = '\0';
    // counter for string length
    int counter = 1;
    // strnig for storing read chars
    char current[2];
    // while there are chars in the file and counter is less than maxSize
    while(fgets(current, 2, file) && counter < buffer_size){

        if (feof(file)) break;
        // add read string to contents
        strcat(contents, current);
        counter ++;
    }
    // if maxSize was not big enough
    if (!(counter < buffer_size)) printf("[ERROR] Contents string not big enough.\n");

    // close file
    fclose(file);
}

void ShaderCreate(SHADER* sh, char* vertexShader, char* fragmentShader,
                  unsigned int buffer_size){

    // vertexShader contains filepath to file to be read.
    // vertexShader will contain contents of the file. Set buffer_size
    // accordingly.
    printf("[INFO] Vertex Shader \"%s\" compiling...\n", vertexShader);
    ShaderParse(vertexShader, vertexShader, buffer_size);
    // fragmentShader contains filepath to file to be read.
    // fragmentShader will contain contents of the file. Set buffer_size
    // accordingly.
    printf("[INFO] Fragment Shader \"%s\" compiling...\n", fragmentShader);
    ShaderParse(fragmentShader, fragmentShader, buffer_size);

    GLuint program = glCreateProgram();

    GLuint vertShader = ShaderCompile(vertexShader, GL_VERTEX_SHADER);
    GLuint fragShader = ShaderCompile(fragmentShader, GL_FRAGMENT_SHADER);

    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);

    //glDetachShader(program, vertShader);
    //glDetachShader(porgram, fragShader);
    //glDeleteShader(vertShader);
    //glDeleteShader(fragShader);

    printf("[INFO] Shaders successfully loaded...\n");

    sh -> shaderID = program;
}

void ShaderDestroy(SHADER* sh){
    glDeleteProgram(sh -> shaderID);
}

void ShaderBind(SHADER* sh){
    glUseProgram(sh -> shaderID);
}

void ShaderUnbind(){
    glUseProgram(0);
}
