#pragma once


class UniformBuffer
{
public:

	UniformBuffer(unsigned rendererID, unsigned size);

	void Bind() const;
	void Unbind() const;
	void BindToSlot(unsigned int slot) const;

private:
	unsigned int m_RendererID;
	unsigned int m_Size;
};
