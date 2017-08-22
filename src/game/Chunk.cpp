#include "Chunk.h"
#include "../graphics/CubeMesh.h"
#include "../math/math.h"

#define sqr(x) x*x

Chunk::Chunk(int x, int z)
{
	m_x = x;
	m_z = z;
}

Chunk::~Chunk()
{
	blocks.clear();
}

void Chunk::build() {
	blocks = std::vector<Block>();
	for (int x = 0; x < CHUNK_SIZE; x++){
		for (int z = 0; z < CHUNK_SIZE; z++) {
			for (int y = 0; y < CHUNK_HEIGHT; y++) {
				blocks.push_back(Block(x, y, z, BlockType::Dirt, this));
			}
		}
	}
}
void Chunk::render(const Camera& cam) {
	CubeMesh::drawBlocks(cam.getProjectionMatrix(), cam.getModelViewMatrix(), &blocks, sqr(CHUNK_SIZE)*CHUNK_HEIGHT);
}
void Chunk::Update() {
	//std::cout << "update" << std::endl;
}
bool Chunk::IsInBound(int x, int y, int z) const
{
	if (x<0||x>=GetSize() || z<0||z>=GetSize() || y<0 || y>=GetHeight()) {
		return false;
	}
	return true;
}

//getters & setters
int Chunk::GetX() const {
	return m_x;
}
int Chunk::GetZ() const {
	return m_z;
}

Block *Chunk::GetBlockAt(int x, int y, int z)
{
	if (IsInBound(x, y, z)) {
		return &(blocks.at(math::from3D_indexing_to_1d(x, y, z, GetSize(), GetHeight())));
	}
	return NULL;
}

int Chunk::GetHeight() 
{
	return CHUNK_HEIGHT;
}
int Chunk::GetSize() 
{
	return CHUNK_SIZE;
}
