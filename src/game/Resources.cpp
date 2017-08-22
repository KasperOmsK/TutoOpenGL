#include "Resources.h"
#include <iostream>

//==================static members=================

std::map<BlockType, Texture*> Resources::textures;

//=============private static methods===============

//returns true if loaded succesfully, false otherwise (obviously)
bool Resources::load(BlockType t, std::string texturePath) {
	Texture* newTexture = new Texture(texturePath);
	
	if (newTexture->load()) {
		textures[t] = newTexture;
		return true;
	}
	else {
		return false;
	}
}

//====================public static methods=========================

//load all textures, need to be called at game start
bool Resources::Init() {
	if (!load(BlockType::Dirt, "resources/crate13.jpg")) {
		return false;
	}
	if (!load(BlockType::Air, "resources/crate13.jpg")) {
		return false;
	}
}

void Resources::Free() {
	std::map<BlockType, Texture*>::iterator it;
	for (it = textures.begin(); it != textures.end(); it++){
		delete it->second;
	}
	textures.clear();
}

Texture * Resources::GetTexture(BlockType type)
{
	return textures[type];
}

Resources::~Resources()
{
	Free();
}