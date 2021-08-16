#include "Shader.h"

Shader::Shader(const std::string& VertexShaderFileName, const std::string& FragmentShaderFileName)
	:FilePath(shaderFolder), ID(0)
{
	ShaderSource source = ParseShaders(VertexShaderFileName, FragmentShaderFileName);
	ID = CreateShader(source.VertexCode, source.FragmentCode);
}

Shader::~Shader()
{
	glDeleteProgram(ID);
}

void Shader::Bind()
{
	glUseProgram(ID);
}

void Shader::Unbind()
{
	GLCall(glUseProgram(0));
}

void Shader::SetUniform1f(const std::string name, float v0)
{
	GLCall(glUniform1f(GetUniformLocation(name), v0));
}

void Shader::SetUniform2f(const std::string name, float v0, float v1)
{
	GLCall(glUniform2f(GetUniformLocation(name), v0, v1));
}

void Shader::SetUniform3f(const std::string name, float v0, float v1, float v2)
{
	GLCall(glUniform3f(GetUniformLocation(name), v0, v1, v2));
}

void Shader::SetUniform3f(const std::string name, glm::vec3 vector)
{
	GLCall(glUniform3f(GetUniformLocation(name), vector.x, vector.y, vector.z));
}

void Shader::SetUniform4f(const std::string name, float v0, float v1, float v2, float v3)
{
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniform1i(const std::string name, int v0)
{
	GLCall(glUniform1i(GetUniformLocation(name), v0));
}

void Shader::SetUniformMat4f(const std::string name, const glm::mat4& matrix)
{
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

int Shader::GetUniformLocation(const std::string& name)
{
	if (UniformsCache.find(name) != UniformsCache.end())
		return UniformsCache[name];

	int location = glGetUniformLocation(ID, name.c_str());
	if (location == -1)
	{
		std::cout << "Warning: uniform " << name << " doesn't exist." << std::endl;
	}
	UniformsCache[name] = location;

	return location;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	GLCall(unsigned int sID = glCreateShader(type));
	const char* src = source.c_str();
	GLCall(glShaderSource(sID, 1, &src, nullptr));
	GLCall(glCompileShader(sID));

	//Error Handeling
	int result;
	glGetShaderiv(sID, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(sID, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(sID, length, &length, message);
		std::cout << "Failed to compile! " << (type == GL_VERTEX_SHADER ? " the Vertex Shader " : "Fragment Shader") << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(sID);
		return 0;

	}
	return sID;
}

unsigned int Shader::CreateShader(const std::string& vertexshader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexshader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	GLCall(glAttachShader(program, vs));
	GLCall(glAttachShader(program, fs));
	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));
	return program;
}

ShaderSource Shader::ParseShaders(const std::string& VertexShaderFile, const std::string& FragmentShaderFile)
{
	std::ifstream f_VS(FilePath + VertexShaderFile);
	std::ifstream f_FS(FilePath + FragmentShaderFile);
	if (!f_VS.is_open())
	{
		std::cout << "\n";
		std::cout << "No " << VertexShaderFile << " file in ." << FilePath << std::endl;


	}
	if (!f_FS.is_open())
	{
		std::cout << "No " << FragmentShaderFile << " file in " << FilePath << std::endl;
		//throw("Nu exista shader.");

	}
	std::string vsInfo;
	std::string fsInfo;

	GetFileContent(f_VS, vsInfo);
	GetFileContent(f_FS, fsInfo);

	return { vsInfo,fsInfo };
}

void Shader::GetFileContent(std::ifstream& file, std::string& content)
{
	file.seekg(0, std::ios::end);
	content.resize(file.tellg());
	file.seekg(0, std::ios::beg);
	file.read(&content[0], content.size());
	file.close();
}
