#include "shaderClass.h"

// Reads a text file and outputs a string with everything in the text file
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile) {
    std::string vertexCode = get_file_contents(vertexFile);
    std::string fragmentCode = get_file_contents(fragmentFile);

    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

	// instantiate vertex shader object and get the reference to it
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// set the shader source for the vertex as the one define above
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	// compile vertex shader into machine code
	glCompileShader(vertexShader);
	compileErrors(vertexShader, "VERTEX");

	// instantiate fragment shader object and get the reference to it 
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// attach shader source to fragment shader
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	// compile fragment shader into machine code
	glCompileShader(fragmentShader);
	compileErrors(fragmentShader, "FRAGMENT");

	// instantiate a program and get its reference
	ID = glCreateProgram();

	// attach the vertex shader to the program object
	glAttachShader(ID, vertexShader);
	// attach the fragmente shader to the program object
	glAttachShader(ID, fragmentShader);
	// link all the specified shaders into the program
	glLinkProgram(ID);
	compileErrors(ID, "PROGRAM");

	// delete shaders because they are already in the program
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);    
}

void Shader::Activate() {
    glUseProgram(ID);
}

void Shader::Delete() {
    glDeleteProgram(ID);
}

void Shader::compileErrors(unsigned int shader, const char* type) {
	GLint hasCompiled;
	char infoLog[1024];
	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for: " << type << "\n" << std::endl;
		}
	} else {
		glGetProgramiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE) {
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for: " << type << "\n" << std::endl;
		}
	}
}