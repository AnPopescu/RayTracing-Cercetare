#include "GLWrapper.h"


static void glfw_error_callback(int error, const char* desc)
{
	fputs(desc, stderr);
}

GLWrapper::GLWrapper(int width, int height)
{
	this->Width = width;
	this->Height = height;
	this->useCustomResolution = true;
}

GLWrapper::~GLWrapper()
{
	glDeleteVertexArrays(1, &quadVAO);
	glDeleteBuffers(1, &quadVBO);

	glDeleteTextures(1, &skyboxTex);
	glDeleteTextures(textures.size(), textures.data());
}

int GLWrapper::GetWidth()
{
	return Width;
}

int GLWrapper::GetHeight()
{
	return Height;
}

GLuint GLWrapper::GetProgramID()
{
	return _shader->GetProgramId();
}

bool GLWrapper::InitWindow()
{
	if (!glfwInit())
		return false;

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (!useCustomResolution)
	{
		Width = mode->width;
		Height = mode->height;
	}

	glfwSetErrorCallback(glfw_error_callback);

	//Here you can set fullscreen
	WindowScreen = glfwCreateWindow(Width, Height, "RayTracing", NULL, NULL);
	glfwGetWindowSize(WindowScreen, &Width, &Height);

	if (!WindowScreen)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(WindowScreen);

	if (!gladLoadGL())
	{
		printf("gladLoadGL failed!\n");
		return false;
	}
	printf("OpenGL %d.%d\n", GLVersion.major, GLVersion.minor);

	float quadVertices[] =
	{
		-1.0f, -1.0f, 0.0f, 0.0f,
		 1.0f, -1.0f, 1.0f, 0.0f,
		 1.0f,  1.0f, 1.0f, 1.0f,
	
		-1.0f, -1.0f, 0.0f, 0.0f,
		 1.0f,  1.0f, 1.0f, 1.0f,
		-1.0f,  1.0f, 0.0f, 1.0f
	};
	
	// quad VAO
	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glBindVertexArray(0);

	// SMAA framebuffers
	//if (SMAA_enabled)
	//{
	//	gen_framebuffer(&fboColor, &fboTexColor, GL_RGBA, GL_RGBA);
	//	gen_framebuffer(&fboEdge, &fboTexEdge, GL_RG, GL_RG);
	//	gen_framebuffer(&fboBlend, &fboTexBlend, GL_RGBA, GL_RGBA);
	//}

	return true;

}

void GLWrapper::InitShader(Shader *shader)
{
	_shader = shader;
}


void GLWrapper::SetSkybox(unsigned int textureId)
{
	skyboxTex = textureId;
	_shader->SetUniform1i("skybox", 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTex);
}

void GLWrapper::Stop()
{
	glfwDestroyWindow(WindowScreen);
	glfwTerminate();
}

void GLWrapper::Draw()
{
	_shader->Bind();
	glBindVertexArray(quadVAO);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	checkGlErrors("Draw raytraced image");
}

GLuint GLWrapper::LoadCubemap(std::vector<std::string> faces, bool genMipmap)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	if (genMipmap)
	{
		glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, genMipmap ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}

GLuint GLWrapper::LoadTexture(int textureNumber, const char* name, const char* uniformName, GLuint wrapMode)
{
	const std::string path =  "Textures/Res" + std::string(name);
	const unsigned int tex = LoadTexture(path.c_str(), wrapMode);
	_shader->SetUniform1i(uniformName, textureNumber);
	textures.push_back(tex);
	return tex;
}

GLuint GLWrapper::LoadTexture(char const* path, GLuint wrapMode)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}
