#include "VertexBuffer.h"
#include "Renderer.h"
#include <glad/glad.h>

VertexBuffer::VertexBuffer(const void* data, const unsigned int size)
{
	GLCall(glGenBuffers(1, &m_RendederID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendederID));
	GLCall(glBufferData(GL_ARRAY_BUFFER,size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendederID));
}

void VertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendederID));
}

void VertexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
