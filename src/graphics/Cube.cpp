#include "Cube.h"
#include <iostream>

Cube::Cube(float size, std::string vertexShader, std::string fragShader)
	: m_shader(vertexShader, fragShader), position(0, 0, 0)
{
	m_size = size;
	m_shader.charger();
	build();
}

void Cube::render(glm::mat4 &projection, glm::mat4 &modelView) 
{
	using namespace glm;
	glUseProgram(m_shader.getProgramID());
	{
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, m_vertices);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, m_colors);
		glEnableVertexAttribArray(1);

		//save matrix
		mat4 saveTransformMatrix = modelView;

		//==========translation should be here====================
		modelView = translate(modelView, position);
		modelView = rotate(modelView, eulerAngles.x, vec3(1,0,0));
		modelView = rotate(modelView, eulerAngles.y, vec3(0, 1, 0));
		modelView = rotate(modelView, eulerAngles.z, vec3(0, 0, 1));



		glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelView));
		glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		//restore matrix
		modelView = saveTransformMatrix;

		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(0);
	}
	glUseProgram(0);
}

Cube::~Cube()
{
}

void Cube::build() {
	m_size /= 2;
	float verticesTmp[] = {
		-m_size, -m_size, -m_size,   m_size, -m_size, -m_size,   m_size, m_size, -m_size,     // Face 1
		-m_size, -m_size, -m_size,   -m_size, m_size, -m_size,   m_size, m_size, -m_size,     // Face 1

		m_size, -m_size, m_size,   m_size, -m_size, -m_size,   m_size, m_size, -m_size,       // Face 2
		m_size, -m_size, m_size,   m_size, m_size, m_size,   m_size, m_size, -m_size,         // Face 2

		-m_size, -m_size, m_size,   m_size, -m_size, m_size,   m_size, -m_size, -m_size,      // Face 3
		-m_size, -m_size, m_size,   -m_size, -m_size, -m_size,   m_size, -m_size, -m_size,    // Face 3

		-m_size, -m_size, m_size,   m_size, -m_size, m_size,   m_size, m_size, m_size,        // Face 4
		-m_size, -m_size, m_size,   -m_size, m_size, m_size,   m_size, m_size, m_size,        // Face 4

		-m_size, -m_size, -m_size,   -m_size, -m_size, m_size,   -m_size, m_size, m_size,     // Face 5
		-m_size, -m_size, -m_size,   -m_size, m_size, -m_size,   -m_size, m_size, m_size,     // Face 5

		-m_size, m_size, m_size,   m_size, m_size, m_size,   m_size, m_size, -m_size,         // Face 6
		-m_size, m_size, m_size,   -m_size, m_size, -m_size,   m_size, m_size, -m_size		   // Face 6
	};

	float colorTmp[] = {
	1.0, 0.0, 0.0,   1.0, 0.0, 0.0,   1.0, 0.0, 0.0,           // Face 1
	1.0, 0.0, 0.0,   1.0, 0.0, 0.0,   1.0, 0.0, 0.0,           // Face 1

	0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,           // Face 2
	0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,           // Face 2

	0.0, 0.0, 1.0,   0.0, 0.0, 1.0,   0.0, 0.0, 1.0,           // Face 3
	0.0, 0.0, 1.0,   0.0, 0.0, 1.0,   0.0, 0.0, 1.0,           // Face 3

	1.0, 0.0, 0.0,   1.0, 0.0, 0.0,   1.0, 0.0, 0.0,           // Face 4
	1.0, 0.0, 0.0,   1.0, 0.0, 0.0,   1.0, 0.0, 0.0,           // Face 4

	0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,           // Face 5
	0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,           // Face 5

	0.0, 0.0, 1.0,   0.0, 0.0, 1.0,   0.0, 0.0, 1.0,           // Face 6
	0.0, 0.0, 1.0,   0.0, 0.0, 1.0,   0.0, 0.0, 1.0			   // Face 6
	};

	
	for (int i = 0; i < 108; i++) {
		m_vertices[i] = verticesTmp[i];
		m_colors[i] = colorTmp[i];
	}

	std::cout << "cube buit" << std::endl;
}
