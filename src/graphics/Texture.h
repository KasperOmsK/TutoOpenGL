#pragma once
#include <GL\glew.h>
#include <string>
#include "SDL2\SDL_image.h"
class Texture
{
private:
	GLuint m_textureID;
	std::string m_filepath;

public:
	Texture(std::string path);
	~Texture();
	bool load();
	GLuint GetID() const;
private:
	SDL_Surface* flipTexture(SDL_Surface *surf);
};

