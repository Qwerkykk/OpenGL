#pragma once

#include <string>
#include <vector>


class Texture
{
protected:
	unsigned int m_RendererID;
	std::string m_FilePath;
	std::string m_Type;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP,flipY;
	

public:


	Texture(const std::string& path, const std::string& type,int flipY);
	Texture(const std::string& path, const std::string& directory, const std::string& type,int flipY);


	virtual ~Texture() = default;
	virtual void Bind(unsigned int slot = 0) const = 0;
	virtual void Unbind() const = 0;
	virtual void ReadTexture(const std::string& path) {}
	virtual void ReadTexture(const std::vector<std::string> facesPaths) {}

	inline std::string GetPath() const { return m_FilePath; }
	inline std::string GetType() const { return m_Type; }
	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
};
