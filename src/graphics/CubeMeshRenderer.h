#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include "Shader.h"
#include "../math/Vector3.h"
#include "../game/Block.h"

//Desc : Static used to draw blocks on screen
class CubeMeshRenderer
{
	private:
		static float s_vertices[108];
		static float s_uvs[72];
		static Shader s_shader;
		static float s_size;
	private:
		CubeMeshRenderer();
		~CubeMeshRenderer();
	public:
		//desc : Build the static mesh with given size and shaders
		static void Build(float size, std::string vertexShader, std::string fragShader);

		//desc : draw the given blocks to screen
		//returns : number of draw calls
		static int drawBlocks(glm::mat4 &projection, glm::mat4 &modelView, std::vector<Block> *positions_array, int count);
};
