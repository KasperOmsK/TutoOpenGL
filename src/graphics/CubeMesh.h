#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include "Shader.h"
#include "../math/Vector3.h"
#include "../game/Block.h"

class CubeMesh
{
	private:
		static float s_vertices[108];
		static float s_uvs[108];
		static Shader s_shader;
		static float s_size;
	private:
		CubeMesh();
		~CubeMesh();
	public:
		static void BuildMesh(float size, std::string vertexShader, std::string fragShader);
		static int drawBlocks(glm::mat4 &projection, glm::mat4 &modelView, std::vector<Block> *positions_array, int count);
};
