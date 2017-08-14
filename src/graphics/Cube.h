#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include "../Shader.h"

class Cube
{
	private:
		float m_size;
		float m_vertices[108];
		float m_colors[108];
		Shader m_shader;
	
	public:
		glm::vec3 position;
		glm::vec3 eulerAngles;
	public:
		Cube(float size, std::string vertexShader, std::string fragShader);
		void render(glm::mat4 &projection, glm::mat4 &modelView);
		~Cube();
	private:
		void build();

};

