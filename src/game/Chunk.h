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

	void build();
	void render(const Camera& cam);
	void Update();

	//misc-utils
	bool IsInBound(int x, int y, int z) const;

	//getters & setters
	int GetX() const;
	int GetZ() const;
	Block* GetBlockAt(int x, int y, int z);

	static int GetHeight();
	static int GetSize();

};

