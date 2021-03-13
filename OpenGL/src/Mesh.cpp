#include "Mesh.h"

#include <utility>

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<std::shared_ptr<TextureBasic>> textures) :
	m_Textures(std::move(textures)),
	m_VBO(&vertices[0], vertices.size() * sizeof(Vertex)),
	m_EBO(&indices[0], indices.size())
{
	setupMesh();
}

void Mesh::BindTexture(unsigned int i) const
{
	 m_Textures[i]->Bind(i); 
}


void Mesh::Bind() const
{
	m_VAO.Bind();
}

void Mesh::Unbind() const
{
	m_VAO.Unbind();
}

void Mesh::setupMesh()
{
	VertexBufferLayout VBOLayout;


	m_VAO.Bind();
	m_VBO.Bind();
	m_EBO.Bind();

	VBOLayout.Push<float>(3);
	VBOLayout.Push<float>(3);
	VBOLayout.Push<float>(2);
	VBOLayout.Push<float>(3);
	VBOLayout.Push<float>(3);

	m_VAO.AddBuffer(m_VBO, VBOLayout);

	m_VAO.Unbind();
	m_VBO.Unbind();
	m_EBO.Unbind();
}
