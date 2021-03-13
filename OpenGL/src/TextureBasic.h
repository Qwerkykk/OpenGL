#pragma once
#include "Texture.h"

#include <string>



class TextureBasic : public Texture
{

public:


	TextureBasic(const std::string& path, const std::string& type,int flipY);
	TextureBasic(const std::string& path, const std::string& directory, const std::string& type,int flipY);
	virtual ~TextureBasic();

	void ReadTexture(const std::string& path);
	void Bind(unsigned int slot = 0) const;
	void Unbind() const;
};
