#include "Renderer.h"


#include <glad/glad.h>
#include <iostream>

#include "Model.h"
#include "Shader.h"

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << "):" <<
			function << " " << file << "; Line:" << line << std::endl;
		return false;
	}

	return true;
}


void Renderer::DrawElements(const VertexArray& va, const IndexBuffer& ib, Shader& shader) const
{
	shader.Bind();
	va.Bind();
	ib.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::DrawArrays(const VertexArray& va,int count, Shader& shader) const
{
	shader.Bind();
	va.Bind();
	
	GLCall(glDrawArrays(GL_TRIANGLES, 0, count));

	va.Unbind();
}

void Renderer::DrawMesh(const Mesh& mesh, Shader& shader) const
{
       
        unsigned int diffuseNr  = 1;
        unsigned int specularNr = 1;
        unsigned int normalNr   = 1;
        unsigned int heightNr   = 1;
        for(unsigned int i = 0; i < mesh.GetTextureCount(); i++)
        {
        	mesh.BindTexture(i);

            std::string number;
            std::string name = mesh.GetTextureType(i);
            if(name == "texture_diffuse")
                number = std::to_string(diffuseNr++);
            else if(name == "texture_specular")
                number = std::to_string(specularNr++);
            else if(name == "texture_normal")
                number = std::to_string(normalNr++); 
             else if(name == "texture_height")
                number = std::to_string(heightNr++); 

      
            shader.SetUniform1i(name + number, i);

        }
        
        
        mesh.Bind();
        GLCall(glDrawElements(GL_TRIANGLES, mesh.GetEBOCount(), GL_UNSIGNED_INT, 0));
        mesh.Unbind();

        
        GLCall(glActiveTexture(GL_TEXTURE0));
	
}

void Renderer::DrawModel(const Model& model, Shader& shader) const
{
	

	for(auto mesh:model.m_Meshes)
		DrawMesh(*mesh,shader);
	
}

void Renderer::Clear() const
{
	GLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f););
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}
