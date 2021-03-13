#include "TextureBasic.h"
#include <glad/glad.h>
#include "stb_image/stb_image.h"
#include <iostream>

#include "Renderer.h"

TextureBasic::TextureBasic(const std::string& path, const std::string& type,int flipY)
	: Texture(path, type,flipY)
{
	ReadTexture(path);
}

TextureBasic::TextureBasic(const std::string& path, const std::string& directory, const std::string& type,int flipY):
	Texture(path, directory, type,flipY)
{
	std::string filename = std::string(path);
	filename = directory + '/' + filename;

	ReadTexture(filename);
}

TextureBasic::~TextureBasic()
{
	GLCall(glDeleteTextures(1, &m_RendererID));
}


void TextureBasic::ReadTexture(const std::string& path)
{
	stbi_set_flip_vertically_on_load(flipY);

	GLCall(glGenTextures(1, &m_RendererID));

	int width, height, nrComponents;
	m_LocalBuffer = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
	if (m_LocalBuffer)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, m_LocalBuffer));
		GLCall(glGenerateMipmap(GL_TEXTURE_2D));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

		stbi_image_free(m_LocalBuffer);
	}
	else
	{
		std::cout << "TextureBasic failed to load at path: " << path << std::endl;
		stbi_image_free(m_LocalBuffer);
	}
}


void TextureBasic::Bind(unsigned slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void TextureBasic::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
