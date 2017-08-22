#pragma once

class Chunk;

enum class BlockType {
	Air,
	Dirt
};

class Block
{
private:
	int m_x;
	int m_y;
	int m_z;
	BlockType m_type;
	Chunk* m_chunk = 0; //pointer to Chunk

public:
	Block(int x, int y, int z, BlockType t, Chunk* pchunk);
	~Block();

	//getters & setters
	
	int GetWorldX() const; 
	int GetWorldY() const; //return coordinates in world space
	int GetWorldZ() const;

	int GetChunkX() const;
	int GetChunkY() const; //returns coordinates in chunk space
	int GetChunkZ() const;
	
	BlockType GetType() const;
	Chunk* GetChunk() const;

	void SetType(BlockType newType);
};

