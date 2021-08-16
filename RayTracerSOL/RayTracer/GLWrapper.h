#pragma once

#include <glad/glad.h>
#include <glfw3.h>
#include "Shader.h"
#include <string>
#include <vector>
#include <glm.hpp>
#include "stb_image.h"




class GLWrapper
{
public:
	GLWrapper(int width, int height);
	~GLWrapper();

	int GetWidth();
	int GetHeight();
	GLuint GetProgramID();

	bool InitWindow();
	void InitShader(Shader *shader); // TODO parametrii pentru shaderi
	void SetSkybox(unsigned int textureId);

	void Stop();
	
	GLFWwindow* WindowScreen;

	void Draw();
	static GLuint LoadCubemap(std::vector<std::string> faces, bool genMipmap = false);
	GLuint LoadTexture(int textureNumber, const char* name, const char* uniformName, GLuint wrapMode = GL_REPEAT);

	//DELETE THIS - EXPLAIN NEXT LINES
	//void init_buffer(GLuint* ubo, const char* name, int bindingPoint, size_t size, void* data) const;
	//static void update_buffer(GLuint ubo, size_t size, void* data);

private:

	static GLuint LoadTexture(char const* path, GLuint wrapMode = GL_REPEAT);

	std::vector<GLuint> textures;
	Shader *_shader;
	int Width;
	int Height;
	GLuint quadVAO, quadVBO;
	GLuint skyboxTex;
	bool useCustomResolution;


};

