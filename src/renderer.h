#include <glad.h>
#include "window.h"

typedef struct Shader {
    u32 programId;
} Shader;

inline void bind(Shader* shader) { glUseProgram(shader->programId); } 
inline void unbind(Shader* shader) { glUseProgram(0); }

void setupShader(Shader* shader, const char* vertexSource, const char* fragmentSource);
Shader* readFromFiles(const char* vertexSourcePath, const char* fragmentSourcePath);