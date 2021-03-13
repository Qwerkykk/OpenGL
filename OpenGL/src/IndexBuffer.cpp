#include "IndexBuffer.h"
#include "Renderer.h"
#include <glad/glad.h>

IndexBuffer::IndexBuffer(const unsigned int* data, const unsigned int count)
	: m_Count(count)
{

	GLCall(glGenBuffers(1, &m_RendederID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendederID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER,count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendederID));
}

void IndexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendederID));
}

void IndexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
