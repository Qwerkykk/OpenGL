#pragma once


class IndexBuffer
{
private:
	unsigned int m_RendederID;
	unsigned int m_Count;
public:
	IndexBuffer(const unsigned int* data, const unsigned int count);
	~IndexBuffer();


	inline unsigned int GetCount() const
	{
		return m_Count;
	}

	void Bind() const;
	void Unbind() const;
};
