#pragma once
#include <GL/glew.h>
#include <string>

#include "def.h"


class Sh
{
public:
	Sh(const char* vertexShaderFilename, const char* fragmentShaderFilename);

	virtual ~Sh();

	void bind();

	void unbind();



private:
	GLuint compile(std::string shaderSource, GLenum type);
	std::string parse(const char* filename);
	GLuint createSh(const char* vertexShaderFilename, const char* fragmentShaderFilename);

	GLuint shaderId;
};