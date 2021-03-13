#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"

class Mesh;
class Model;
class Shader;
#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x,__FILE__,__LINE__))


void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
private:

public:
	void Clear() const;
	void DrawElements(const VertexArray& va, const IndexBuffer& ib, Shader& shader) const;
	void DrawArrays(const VertexArray& va, int count, Shader& shader) const;
	void DrawMesh(const Mesh& mesh, Shader& shader) const;
	void DrawModel(const Model& model, Shader& shader) const;
};


