#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "stb_image/stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "TextureBasic.h"

#include <string>
#include <sstream>
#include <vector>


class Model
{
public:
	std::vector<std::shared_ptr<Mesh>> m_Meshes;

	Model(std::string const& path);
	

private:
	std::string m_Directory;
	std::vector<std::shared_ptr<TextureBasic>> textures_loaded;

	
	void loadModel(std::string const& path);
	void processNode(aiNode* node, const aiScene* scene);
	std::shared_ptr<Mesh> processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<std::shared_ptr<TextureBasic>> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};
