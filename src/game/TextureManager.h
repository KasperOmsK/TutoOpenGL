#pragma once
#include "Block.h"
#include <map>
#include "../graphics/Texture.h"

class TextureManager
{
private:
	static std::map<BlockType, Texture*> textures_map;

public:
	// desc : Load textures, return true if loading succeeded, false otherwise
	// note : HAS to be called AFTER openGL initalization & context creation
	static bool Init();
	// desc : Free allocated memory for textures
	static void Free();
	// desc : Return a pointer to the Texture of the given BlockType
	// note : Can return NULL
	static Texture* GetTexture(BlockType type);

private:
	TextureManager();
	~TextureManager();
	static bool load(BlockType type, std::string texturePath);
};

