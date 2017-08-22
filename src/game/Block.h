#pragma once

class Chunk;

enum class BlockType {
	Air,
	Dirt, 
	Stone
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
	
	//desc : returns X coordinate of this block in World Space
	int GetWorldX() const; 
	//desc : returns Y coordinate of this block in World Space
	int GetWorldY() const; 
	//desc : returns Z coordinate of this block in World Space
	int GetWorldZ() const;

	//desc : returns X coordinate of this block in Chunk Space
	int GetChunkX() const;
	//desc : returns Y coordinate of this block in Chunk Space
	int GetChunkY() const; //returns coordinates in chunk space
	//desc : returns Z coordinate of this block in Chunk Space
	int GetChunkZ() const;
	
	//desc : Returns block type (Dirt, Stone, Air etc..)
	BlockType GetType() const;

	//desc: returns a pointer to the parent chunk
	Chunk* GetChunk() const;

	void SetType(BlockType newType);
};

