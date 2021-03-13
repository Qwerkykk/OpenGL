#pragma once
#include <string>
#include <unordered_map>

#include "glm/glm.hpp"


struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};


class Shader
{
private:
	std::string m_FilePath;
	unsigned int m_RenderedID;
	std::unordered_map<std::string, int> m_UniformLocationCache;

public:

	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	unsigned int const GetId() const {return m_RenderedID; }
	//Set uniforms
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float v0);
	void SetUniform3f(const std::string& name, float v0, float v1, float v2);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformVec3f(const std::string& name , const glm::vec3&  vec);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
	void SetUniformBlock(std::string uniformName,unsigned int slot);
	
private:

	ShaderProgramSource ParseShader(const std::string& filepath) const;
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	int GetUniformLocation(const std::string& name);
};
