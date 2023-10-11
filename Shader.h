#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

class Shader
{
public:

	Shader();
	~Shader();


	void init(const GLchar* filename);
	GLuint getID() { return mIDprogram; };
	void Use() { if (mAllOK) glUseProgram(mIDprogram); };
	void deleteProgram() { if (mAllOK) glDeleteProgram(mIDprogram); };

private:
	GLuint	mIDprogram;
	bool	mAllOK;

};

#endif // !SHADER