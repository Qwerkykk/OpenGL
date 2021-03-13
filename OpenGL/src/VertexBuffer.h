#pragma once


class VertexBuffer
{
private:
	unsigned int m_RendederID;

public:
	explicit VertexBuffer(const void* data, const unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};
