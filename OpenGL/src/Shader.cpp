#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <glad/glad.h>

#include "Shader.h"
#include "Renderer.h"



Shader::Shader(const std::string& filepath): m_FilePath(filepath), m_RenderedID(0)
{
	ShaderProgramSource source = ParseShader(filepath);
	m_RenderedID = CreateShader(source.VertexSource, source.FragmentSource);

}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_RenderedID))
}

void Shader::Bind() const
{
	GLCall(glUseProgram(m_RenderedID));
}

void Shader::SetUniformBlock(std::string uniformName,unsigned int slot)
{
	unsigned int index = glGetUniformBlockIndex(m_RenderedID,uniformName.c_str());
	GLCall(glUniformBlockBinding(m_RenderedID,index,slot));
}

void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}

void Shader::SetUniform1i(const std::string& name, int value)
{
	GLCall(glUniform1i( glGetUniformLocation(m_RenderedID, name.c_str()), value));
}

void Shader::SetUniform1f(const std::string& name, float v0)
{
	GLCall(glUniform1f(GetUniformLocation(name),v0));
}

void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
{
	GLCall(glUniform3f(GetUniformLocation(name),v0,v1,v2));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	GLCall(glUniform4f(GetUniformLocation(name),v0,v1,v2,v3));
}

void Shader::SetUniformVec3f(const std::string& name , const glm::vec3& value)
{
	GLCall(glUniform3fv(GetUniformLocation(name), 1, &value[0]));
}


void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

int Shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];
	
	GLCall(int location = glGetUniformLocation(m_RenderedID, name.c_str()));
	if (location == -1)
		std::cout << "Warning: uniform" << name << " doesn't exist!" << std::endl;

	m_UniformLocationCache[name] = location;
	return location;

}




unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	GLCall(unsigned int id = glCreateShader(type));
	const char* src = source.c_str();
	GLCall(glShaderSource(id, 1, &src, nullptr));
	GLCall(glCompileShader(id));

	int result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE)
	{
		int length;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char message[500];
		GLCall(glGetShaderInfoLog(id, length, &length, message));
		std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader\n";
		std::cout << message << std::endl;

		GLCall(glDeleteShader(id));
		return 0;
	}

	return id;
}



ShaderProgramSource Shader::ParseShader(const std::string& filepath) const
{
	std::ifstream stream(filepath);

	enum class ShaderType
	{
		NODE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NODE;


	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[static_cast<int>(type)] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };
}



unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	GLCall(unsigned int program = glCreateProgram());
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	GLCall(glAttachShader(program, vs));
	GLCall(glAttachShader(program, fs));
	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));
	return program;
}

