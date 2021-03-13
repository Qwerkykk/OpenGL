#pragma once
#include "Texture.h"

class TextureCubeMap : public Texture
{
public:


	TextureCubeMap(const std::vector<std::string> facesPaths, const std::string& type,int flipY);

	~TextureCubeMap() override;
	void Bind(unsigned slot) const override;
	void Unbind() const override;
	void ReadTexture(const std::vector<std::string> faces) override;

private:
	std::vector<std::string> m_FacesPaths;
};

