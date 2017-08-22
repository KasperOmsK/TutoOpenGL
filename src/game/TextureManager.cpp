#include "TextureManager.h"
#include <iostream>

//==================static members=================

std::map<BlockType, Texture*> TextureManager::textures_map;


//====================public static methods=========================

//load all textures, need to be called at game start
bool TextureManager::Init() {
	if (!load(BlockType::Dirt, "resources/dirt.png")) {
		return false;
	}
	if (!load(BlockType::Stone, "resources/stone.png")) {
		return false;
	}
	return true;
}

void TextureManager::Free() {
	std::map<BlockType, Texture*>::iterator it;
	for (it = textures_map.begin(); it != textures_map.end(); it++){
		delete it->second;
	}
	textures_map.clear();
}

Texture * TextureManager::GetTexture(BlockType type)
{
	return textures_map[type];
}

TextureManager::~TextureManager()
{
	Free();
}

//=============private static methods===============

//returns true if loaded succesfully, false otherwise (obviously)
bool TextureManager::load(BlockType t, std::string texturePath) {
	Texture* newTexture = new Texture(texturePath);
	
	if (newTexture->load()) {
		textures_map[t] = newTexture;
		return true;
	}
	else {
		return false;
	}
}