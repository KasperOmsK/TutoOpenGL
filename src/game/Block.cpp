#include "Block.h"
#include <iostream>
#include "Chunk.h"

Block::Block(int x, int y, int z, BlockType t, Chunk* chunk)
{
	if (chunk != NULL) {
		m_x = x;
		m_y = y;
		m_z = z;
		m_type = t;
		m_chunk = chunk;
	}
	else {
		std::cout << "Null chunk given as argument. Wtf??";
	}
}

Block::~Block()
{
}

//getters & setters
int Block::GetWorldX() const
{
	return GetChunkX() + m_chunk->GetX()* CHUNK_SIZE;
}
int Block::GetWorldY() const
{
	return m_y;
}
int Block::GetWorldZ() const
{
	return GetChunkZ() + m_chunk->GetZ()*CHUNK_SIZE;
}

int Block::GetChunkX() const {
	return m_x;
}
int Block::GetChunkZ() const {
	return m_z;
}

BlockType Block::GetType() const
{
	return m_type;
}
Chunk* Block::GetChunk() const {
	return m_chunk;
}

void Block::SetType(BlockType newType) {
	m_type = newType;
	m_chunk->Update();
}