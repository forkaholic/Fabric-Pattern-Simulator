#ifndef SHADERFUNCS_H
#define SHADERFUNCS_H

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <string>


// This process works for all types of shaders
void ReadShaderFile(std::string, std::string&);
void AddShader(GLuint, const char*, GLenum);
void CompileShaders();

#endif // !SHADERFUNCS_H
