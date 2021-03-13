#include "UniformBuffer.h"

#include <glad/glad.h>

#include "Renderer.h"

UniformBuffer::UniformBuffer(unsigned rendererId, unsigned size)
	: m_RendererID(rendererId), m_Size(size)
{
	GLCall(glGenBuffers(1,&m_RendererID));
	GLCall(glBindBuffer(GL_UNIFORM_BUFFER, m_RendererID));
	GLCall(glBufferData(GL_UNIFORM_BUFFER, m_Size, nullptr, GL_STATIC_DRAW));
	GLCall(glBindBuffer(GL_UNIFORM_BUFFER, 0));
}

void UniformBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_UNIFORM_BUFFER,m_RendererID));
}

void UniformBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_UNIFORM_BUFFER,0));
}

void UniformBuffer::BindToSlot(unsigned int slot) const 
{
	GLCall(glBindBufferRange(GL_UNIFORM_BUFFER, slot, m_RendererID, 0,m_Size));
}
