#include "CubeMeshRenderer.h"
#include <iostream>
#include "../game/Chunk.h"
#include "../game/TextureManager.h"

//static members
float CubeMeshRenderer::s_vertices[];
float CubeMeshRenderer::s_uvs[];
float CubeMeshRenderer::s_size;
Shader CubeMeshRenderer::s_shader;

//private methods
CubeMeshRenderer::CubeMeshRenderer()
{
}
CubeMeshRenderer::~CubeMeshRenderer()
{
}

//static methods
void CubeMeshRenderer::Build(float size, std::string vertexShader, std::string fragShader) {
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

	float uvstmp[] = { 
		0, 0,   1, 0,   1, 1,     // Face 1
		0, 0,   0, 1,   1, 1,     // Face 1

		0, 0,   1, 0,   1, 1,     // Face 2
		0, 0,   0, 1,   1, 1,     // Face 2

		0, 0,   1, 0,   1, 1,     // Face 3
		0, 0,   0, 1,   1, 1,     // Face 3

		0, 0,   1, 0,   1, 1,     // Face 4
		0, 0,   0, 1,   1, 1,     // Face 4

		0, 0,   1, 0,   1, 1,     // Face 5
		0, 0,   0, 1,   1, 1,     // Face 5

		0, 0,   1, 0,   1, 1,     // Face 6
		0, 0,   0, 1,   1, 1 };    // Face 6

	
	for (int i = 0; i < 108; i++) {
		s_vertices[i] = verticesTmp[i];
		s_uvs[i] = uvstmp[i];
	}

	std::cout << "static cube mesh built !" << std::endl;
}

//TODO : handle optimization logic in CHUNK. CubeMeshRenderer should not have to access game stuff. It should only draw what is given as parameter
int CubeMeshRenderer::drawBlocks(glm::mat4 & projection, glm::mat4 & modelView, std::vector<Block>* positions_array, int count)
{
	using namespace glm;

	glUseProgram(s_shader.getProgramID());
	{
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, s_vertices);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, s_uvs);
		glEnableVertexAttribArray(2);

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
			const int& x = b.GetChunkX();
			const int& y = b.GetChunkY();
			const int& z = b.GetChunkZ();

			if (x == 0 || x == chunkSize - 1 || y == 0 || y == b.GetChunk()->GetHeight() - 1 || z == 0 || z == chunkSize - 1) {
				modelView = translate(modelView, pos.toVec3());
				glUniformMatrix4fv(glGetUniformLocation(s_shader.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelView));
				glUniformMatrix4fv(glGetUniformLocation(s_shader.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
				
				glBindTexture(GL_TEXTURE_2D, TextureManager::GetTexture(b.GetType())->GetID() );
				glDrawArrays(GL_TRIANGLES, 0, 36);
				glBindTexture(GL_TEXTURE_2D, 0);
				
				drawCalls++;
				//restore matrix
				modelView = saveTransformMatrix;
			}
		}
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(0);
		return drawCalls;
	}
}


