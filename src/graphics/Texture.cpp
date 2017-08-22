#include "Texture.h"
#include <iostream>

Texture::Texture(std::string path)
	: m_filepath(path)
{
	m_textureID = 0;
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_textureID);
	std::cout << "texture deleted" << std::endl;
}

bool Texture::load()
{
	//load texture with SDL
	SDL_Surface* texture = flipTexture(IMG_Load(m_filepath.c_str()));
	if (texture == NULL) {
		std::cout << "error : could not load texture." << SDL_GetError() << std::endl;
		return false;
	}

	glGenTextures(1, &m_textureID); //generate texture id
	std::cout << glGetError() << std::endl;
	glBindTexture(GL_TEXTURE_2D, m_textureID); //lock texture so we can use it

	//check for texture file format (rgb or rgba) & store it in internalFormat
	//check for color data format (rgb, bgr etc...) & store it in format
	GLenum internalFormat = 0;
	GLenum dataFormat = 0;

	if (texture->format->BytesPerPixel == 3) {
		internalFormat = GL_RGB;
		if(texture->format->Rmask == 0xff){
			dataFormat = GL_RGB;
		}
		else {
			dataFormat = GL_BGR;
		}
	}
	else if (texture->format->BytesPerPixel == 4) {
		internalFormat = GL_RGBA;
		if (texture->format->Rmask == 0xff) {
			dataFormat = GL_RGBA;
		}
		else {
			dataFormat = GL_BGRA;
		}
	}
	else {
		std::cout << "Error : format de texture inconnu" << std::endl;
		SDL_FreeSurface(texture);
		return false;
	}

	//load texture into openGL from SDL Surface
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, texture->w, texture->h, 0, dataFormat,
		GL_UNSIGNED_BYTE, texture->pixels);
	
	//add filters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	//unlock texture
	glBindTexture(GL_TEXTURE_2D, 0); 
	SDL_FreeSurface(texture);
	return true;
}

GLuint Texture::GetID() const
{
	return m_textureID;
}

SDL_Surface* Texture::flipTexture(SDL_Surface *src)
{
	if (src == NULL) {
		return NULL;
	}

	SDL_Surface *reversedTexture = SDL_CreateRGBSurface(0, src->w,
		src->h, src->format->BitsPerPixel, src->format->Rmask, src->format->Gmask,
		src->format->Bmask, src->format->Amask);

	unsigned char* pix_src = (unsigned char*)src->pixels;
	unsigned char* pix_reversed = (unsigned char*)reversedTexture->pixels;

	for (int y = 0; y < src->h; y++){
		for (int x = 0; x < src->w*src->format->BytesPerPixel; x++){
			pix_reversed[x+(y*src->w*src->format->BytesPerPixel)] = pix_src[x+(src->h-1-y)*src->w*src->format->BytesPerPixel];
		}
	}
	reversedTexture->pixels = pix_reversed;
	return reversedTexture;
}
