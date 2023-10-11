#include "Shader.h"
#include <iostream>
#include <fstream>

#define DIRECTORY_SHADERS "Assets/shaders/"
#define BUFFERSIZE_SOURCECODE 8192

void Shader::init(const GLchar* filename)
{
	mAllOK = false;
	GLchar* buffer = (GLchar*)malloc(sizeof(GLchar) * BUFFERSIZE_SOURCECODE);
	memset(buffer, 0, BUFFERSIZE_SOURCECODE);
	std::fstream srcCodeFile;
	std::string tempFullFileName;
	GLchar information[1024];
	GLint  allOK = GL_FALSE;
	//Generate program
	mIDprogram = glCreateProgram();

	//Create vertex and fragment shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	//Get vertex source
	tempFullFileName = DIRECTORY_SHADERS;
	tempFullFileName += filename;
	tempFullFileName += ".vertex";
	srcCodeFile.open(tempFullFileName, std::ios::in | std::ios::binary);
	if (!srcCodeFile.is_open()) {
		std::cerr << "*** No se encuentra: " << filename << ".vertex" << std::endl;
	}
	srcCodeFile.read(buffer, BUFFERSIZE_SOURCECODE);
	srcCodeFile.close();

	//Set vertex source
	glShaderSource(vertexShader, 1, &buffer, NULL);
	//Compile vertex source
	glCompileShader(vertexShader);
	//Test if compile has been successful
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &allOK);
	if (allOK != GL_TRUE) {
		glGetShaderInfoLog(vertexShader, 1024, NULL, information);
		std::cerr << "*** Compilacion del vertex shader " << filename << ": " << information << std::endl;
	}

	//Get fragment source
	memset(buffer, 0, BUFFERSIZE_SOURCECODE);
	tempFullFileName = DIRECTORY_SHADERS;
	tempFullFileName += filename;
	tempFullFileName += ".fragment";
	srcCodeFile.open(tempFullFileName, std::ios::in | std::ios::binary);
	if (!srcCodeFile.is_open()) {
		std::cerr << "*** No se encuentra: " << filename << ".fragment" << std::endl;
	}
	srcCodeFile.read(buffer, BUFFERSIZE_SOURCECODE);
	srcCodeFile.close();

	//Set fragment source
	glShaderSource(fragmentShader, 1, &buffer, NULL);
	//Compile fragment source
	glCompileShader(fragmentShader);
	//Test if compile has been successful
	allOK = GL_FALSE;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &allOK);
	if (allOK != GL_TRUE) {
		glGetShaderInfoLog(fragmentShader, 1024, NULL, information);
		std::cerr << "*** Compilacion del fragment shader " << filename << ": ERROR:" << information << std::endl;
	}

	//Attach vertex and fragment shader to program
	glAttachShader(mIDprogram, vertexShader);
	glAttachShader(mIDprogram, fragmentShader);
	glLinkProgram(mIDprogram);
	//TEst if link shader has been successful
	allOK = GL_FALSE;
	glGetProgramiv(mIDprogram, GL_LINK_STATUS, &allOK);
	if (allOK != GL_TRUE) {
		glGetProgramInfoLog(mIDprogram, 1024, NULL, information);
		std::cerr << "*** Enlace de shaders a program: " << information << std::endl;
	}

	// Delete shaders, cause, now they are in the program.
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	free(buffer);
	std::cout << "Shader " << filename << " Cargado !" << std::endl;
	mAllOK = true;
}

Shader::Shader() {
	mAllOK = false;
}

Shader::~Shader()
{
}
