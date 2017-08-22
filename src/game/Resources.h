#pragma once
#include "Block.h"
#include <map>
#include "../graphics/Texture.h"

class Resources
{
private:
	static std::map<BlockType, Texture*> textures;

public:
	static bool Init();
	static void Free();
	static Texture* GetTexture(BlockType type);

private:
	Resources();
	~Resources();
	static bool load(BlockType type, std::string texturePath);
};

