#include "CubeMesh.h"
#include <iostream>
#include "../game/Chunk.h"

//static members
float CubeMesh::s_vertices[];
float CubeMesh::s_colors[];
float CubeMesh::s_size;
Shader CubeMesh::s_shader;

CubeMesh::CubeMesh()
{
}

/*void CubeMesh::render(glm::mat4 &projection, glm::mat4 &modelView) 
{
	using namespace glm;
	glUseProgram(s_shader.getProgramID());
	{
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, s_vertices);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, s_colors);
		glEnableVertexAttribArray(1);

		//save matrix
		mat4 saveTransformMatrix = modelView;

		//==========translation should be here====================
		modelView = translate(modelView, position.toVec3());
		modelView = rotate(modelView, eulerAngles.x, vec3(1,0,0));
		modelView = rotate(modelView, eulerAngles.y, vec3(0, 1, 0));
		modelView = rotate(modelView, eulerAngles.z, vec3(0, 0, 1));



		glUniformMatrix4fv(glGetUniformLocation(s_shader.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelView));
		glUniformMatrix4fv(glGetUniformLocation(s_shader.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		//restore matrix
		modelView = saveTransformMatrix;

		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(0);
	}
	glUseProgram(0);
}*/

CubeMesh::~CubeMesh()
{
}

void CubeMesh::BuildMesh(float size, std::string vertexShader, std::string fragShader) {
	s_size = size;
	s_shader = Shader(vertexShader, fragShader);

	s_size /= 2;
	float verticesTmp[] = {
		-s_size, -s_size, -s_size,   s_size, -s_size, -s_size,   s_size, s_size, -s_size,     // Face 1
		-s_size, -s_size, -s_size,   -s_size, s_size, -s_size,   s_size, s_size, -s_size,     // Face 1

		s_size, -s_size, s_size,   s_size, -s_size, -s_size,   s_size, s_size, -s_size,       // Face 2
		s_size, -s_size, s_size,   s_size, s_size, s_size,   s_size, s_size, -s_size,         // Face 2

		-s_size, -s_size, s_size,   s_size, -s_size, s_size,   s_size, -s_size, -s_size,      // Face 3
		-s_size, -s_size, s_size,   -s_size, -s_size, -s_size,   s_size, -s_size, -s_size,    // Face 3

		-s_size, -s_size, s_size,   s_size, -s_size, s_size,   s_size, s_size, s_size,        // Face 4
		-s_size, -s_size, s_size,   -s_size, s_size, s_size,   s_size, s_size, s_size,        // Face 4

		-s_size, -s_size, -s_size,   -s_size, -s_size, s_size,   -s_size, s_size, s_size,     // Face 5
		-s_size, -s_size, -s_size,   -s_size, s_size, -s_size,   -s_size, s_size, s_size,     // Face 5

		-s_size, s_size, s_size,   s_size, s_size, s_size,   s_size, s_size, -s_size,         // Face 6
		-s_size, s_size, s_size,   -s_size, s_size, -s_size,   s_size, s_size, -s_size		   // Face 6
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
		s_vertices[i] = verticesTmp[i];
		s_colors[i] = colorTmp[i];
	}

	std::cout << "static cube mesh built !" << std::endl;
}

//void CubeMesh::drawTest(glm::mat4 & projection, glm::mat4 & modelView, Block * positions_array, int count)
//{
//	using namespace glm;
//	glUseProgram(s_shader.getProgramID());
//	{
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, s_vertices);
//		glEnableVertexAttribArray(0);
//
//
//		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, s_colors);
//		glEnableVertexAttribArray(1);
//
//		mat4 saveTransformMatrix = modelView;
//		int drawCalls = 0;
//
//		for (int i = 0; i < count; i++) {
//			if (positions_array[i].GetType() == BlockType::Air)
//				continue;
//			int x = positions_array[i].GetX();
//			int y = positions_array[i].GetY();
//			int z = positions_array[i].GetZ();
//
//
//			if (x == 0 || x == 15 || y == 0 || y == 15 || z == 0 || z == 15) {
//				modelView = translate(modelView, vec3(x, y, z));
//				glUniformMatrix4fv(glGetUniformLocation(s_shader.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelView));
//				glUniformMatrix4fv(glGetUniformLocation(s_shader.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
//				glDrawArrays(GL_TRIANGLES, 0, 36);
//				drawCalls++;
//				//restore matrix
//				modelView = saveTransformMatrix;
//			}
//		}
//		glDisableVertexAttribArray(1);
//		glDisableVertexAttribArray(0);
//		std::cout << drawCalls << " draw calls." << std::endl;
//	}
//}

void CubeMesh::drawTest(glm::mat4 & projection, glm::mat4 & modelView, std::vector<Block>* positions_array, int count)
{
	using namespace glm;
	glUseProgram(s_shader.getProgramID());
	{
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, s_vertices);
		glEnableVertexAttribArray(0);


		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, s_colors);
		glEnableVertexAttribArray(1);

		mat4 saveTransformMatrix = modelView;
		int drawCalls = 0;

		for (int i = 0; i < count; i++) {
			Block& b = positions_array->at(i);
			if (b.GetType() == BlockType::Air)
				continue;

			int chunkSize = Chunk::GetSize();
			Vector3 pos(
				b.GetWorldX(),
				b.GetWorldY(),
				b.GetWorldZ()
			);

			//if (x == 0 || x == chunkSize - 1 || y == 0 || y == b.GetChunk()->GetHeight() - 1 || z == 0 || z == chunkSize - 1) {
				modelView = translate(modelView, pos.toVec3());
				glUniformMatrix4fv(glGetUniformLocation(s_shader.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelView));
				glUniformMatrix4fv(glGetUniformLocation(s_shader.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
				glDrawArrays(GL_TRIANGLES, 0, 36);
				drawCalls++;
				//restore matrix
				modelView = saveTransformMatrix;
			//}
		}
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(0);
	}
}


