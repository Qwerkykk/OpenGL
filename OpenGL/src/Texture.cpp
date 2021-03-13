#include "Texture.h"


Texture::Texture(const std::string& path, const std::string& type,int flipY)
	: m_RendererID(0), m_FilePath(path), m_Type(type), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0),flipY(flipY)
{
}

Texture::Texture(const std::string& path, const std::string& directory, const std::string& type,int flipY):
	m_RendererID(0), m_FilePath(path), m_Type(type), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0),flipY(flipY)
{
}



