#pragma once
#include <string>
#include <unordered_map>
//#include <glad/glad.h>
#include <glm.hpp>
#include <vector>
#include <fstream>
#include <iostream>
#include "Utils.h"

struct ShaderSource
{
	std::string VertexCode;
	std::string FragmentCode;
};

const std::string shaderFolder = "Shader/";

class Shader
{
private:
	unsigned int ID;
	std::string FilePath;
	std::unordered_map<std::string, int> UniformsCache;

public:
	Shader()
	{
		// Todo for wraper
	}
	Shader(const std::string& VertexShaderFileName, const std::string& FragmentShaderFileName);
	~Shader();

	void Bind();
	void Unbind();


	//set Uniforms

	//float uniforms
	void SetUniform1f(const std::string name, float v0);
	void SetUniform2f(const std::string name, float v0, float v1);
	void SetUniform3f(const std::string name, float v0, float v1, float v2);
	void SetUniform3f(const std::string name, glm::vec3 vector);
	void SetUniform4f(const std::string name, float v0, float v1, float v2, float v3);
	//int uniforms
	void SetUniform1i(const std::string name, int v0);
	//...
	//Matrix uniforms
	void SetUniformMat4f(const std::string name, const glm::mat4& matrix);

	inline unsigned int GetProgramId()
	{
		return ID;
	}

private:
	int GetUniformLocation(const std::string& name);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexshader, const std::string& fragmentShader);
	ShaderSource ParseShaders(const std::string& VertexShaderFile, const std::string& FragmentShaderFile);
	void GetFileContent(std::ifstream& file, std::string& content);
};

