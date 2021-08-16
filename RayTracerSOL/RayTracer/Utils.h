#pragma once

#include <glad/glad.h>
#include <iostream>

#define ASSERT(x) if(!(x)) __debugbreak()
#define GLCall(x) GLClearError(); x; ASSERT(GLLogCall(#x,__FILE__,__LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);
class Utils
{
public:

	void Clear() const;
};

static void checkGlErrors(std::string desc)
{
	GLenum e = glGetError();
	if (e != GL_NO_ERROR)
	{
		fprintf(stderr, "OpenGL error in \"%s\": (%d)\n", desc.c_str(), e); //todo error must be here
		exit(20);
	}
}


