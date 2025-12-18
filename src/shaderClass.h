#ifndef SHADER_CLASS
#define SHADER_CLASS

#include <glad/glad.h>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cerrno>

std::string get_file_contents(const char* filename);

class Shader {
public:
	GLuint ID;
	Shader(const char* vertexFile, const char* fragmentFile);

	void Activate();
	void Delete();
};

#endif