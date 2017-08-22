#pragma once

#define CHUNK_SIZE 16 //depth & width
#define CHUNK_HEIGHT 16

#include <vector>
#include "Block.h"
#include "../render/Camera.h"


class Chunk
{
private :
	int m_x;
	int m_z;
	std::vector<Block> blocks;

public:
	Chunk(int x, int z);
	~Chunk();

	//desc : Build a CHUNK_SIZE*CHUNK_SIZE*CHUNK_HEIGHT chunk (used for testing)
	void build();

	//desc : render the chunk to the camera
	void render(const Camera& cam);
	
	//TODO: Implement chunk updating 
	void Update();

	//desc : returns chunk X coordinate in WORLD
	int GetX() const;
	//desc : returns chunk Z coordinate in WORLD
	int GetZ() const;

	//desc : Returns the block a coordinate x,y,z in this chunk
	//note : Can return NULL
	Block* GetBlockAt(int x, int y, int z);

	static int GetHeight();
	static int GetSize();

private:
	bool IsInBound(int x, int y, int z) const;

};

