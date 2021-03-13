#pragma once
#include <string>
#include <vector>
#include <memory>

#include "IndexBuffer.h"
#include "TextureBasic.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"


class Mesh
{
public:

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<std::shared_ptr<TextureBasic>> textures);


	inline unsigned int GetTextureCount() const { return m_Textures.size(); }
	inline std::string GetTextureType(unsigned int i) const { return m_Textures[i]->GetType(); }
	inline unsigned int GetEBOCount() const { return m_EBO.GetCount();}
	
	void BindTexture(unsigned int i) const;
	void Bind() const;
	void Unbind() const;

private:

	VertexArray m_VAO;
	VertexBuffer m_VBO;
	IndexBuffer m_EBO;
	std::vector<std::shared_ptr<TextureBasic>> m_Textures;


	
	void setupMesh();
};
