#include "TextureCubeMap.h"


#include <iostream>
#include <glad/glad.h>

#include "Renderer.h"
#include "stb_image/stb_image.h"


TextureCubeMap::TextureCubeMap(const std::vector<std::string> facesPaths, const std::string& type, int flipY)
	: Texture("path", type,flipY), m_FacesPaths(facesPaths)
{
	ReadTexture(m_FacesPaths);
}

TextureCubeMap::~TextureCubeMap()
{
	GLCall(glDeleteTextures(1, &m_RendererID));
}

void TextureCubeMap::Bind(unsigned slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0));
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID));
}

void TextureCubeMap::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
}

void TextureCubeMap::ReadTexture(const std::vector<std::string> faces)
{
	stbi_set_flip_vertically_on_load(flipY);
	GLCall(glGenTextures(1, &m_RendererID));
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID));


	for (unsigned int i = 0; i < faces.size(); i++)
	{
		m_LocalBuffer = stbi_load(faces[i].c_str(), &m_Width, &m_Height,
		                          &m_BPP, 0);
		if (m_LocalBuffer)
		{
			GLCall(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE,
			             m_LocalBuffer));
			stbi_image_free(m_LocalBuffer);
		}
		else
		{
			std::cout << "Cubemap failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(m_LocalBuffer);
		}
	}
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE));
}
