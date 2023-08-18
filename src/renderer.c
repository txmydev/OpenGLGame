#include <stdlib.h>
#include <stdio.h>
#include "renderer.h"

boolean check(u32 shader, u32 process) {
    u32 out;
    glGetShaderiv(shader, process, &out);

    if(!out) 
    {
        char message[512];
        glGetShaderInfoLog(shader, 512, NULL, &message);
        printf("Error compiling shader: %s\n", message);
        free(message);
    }

    return out;
}

void setupShader(Shader* shader, const char* vertexSource, const char* fragmentSource) {
    u32 vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    if(!check(vertexShader, GL_COMPILE_STATUS)) {
        return;
    }

    u32 fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    if(!check(fragmentShader, GL_COMPILE_STATUS)) {
        return;
    }

    shader->programId = glCreateProgram();
    glAttachShader(shader->programId, vertexShader);
    glAttachShader(shader->programId, fragmentShader);
    glLinkProgram(shader->programId);

    if(!check(shader->programId, GL_LINK_STATUS)) {
        return;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    free(vertexShader);
    free(fragmentShader);

    free(fragmentSource);
    free(vertexSource);
}

void readFile(char* buf, u32 size, FILE* file){ 

    u32 count = 0;
    char p;

    while ( (p = fgetc(file)) != EOF) {
        if(count > size) 
            break;

        buf[count] = p;
        count++;
    }

}

Shader *readFromFiles(const char *vertexSourcePath, const char *fragmentSourcePath)
{
    FILE* vFile = fopen(vertexSourcePath, 'r');

    if(vFile == NULL) {
        printf("Couldn't open the file located at: %s", vertexSourcePath);
        return NULL;
    }

    char vertexBuffer[1024];
    readFile(vertexBuffer, 1024, vFile);

    printf("VB: \n%s", vertexBuffer);

    fclose(vFile);

    vFile = fopen(fragmentSourcePath, 'r');
    
    char fragmentBuffer[1024];

}
