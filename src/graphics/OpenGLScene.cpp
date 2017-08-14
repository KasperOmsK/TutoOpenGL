#include "OpenGLScene.h"
#include <iostream>
#include "../version/version.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Shader.h"


OpenGLScene::OpenGLScene(std::string _title, int _width, int _height)
	:m_title(_title), m_window(0), m_openGLContext(0), m_inputs()
{
	m_width = _width;
	m_height = _height;
	m_closed = false;
}

OpenGLScene::~OpenGLScene()
{
	SDL_GL_DeleteContext(m_openGLContext);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

bool OpenGLScene::initWindow()
{
	//================init SDL =============
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Could not initialize SDL " << SDL_GetError() << std::endl;
		SDL_Quit();
		return false;
	}
	
	//===============setting OPENGL attributes for SDL (see version.h)======================
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, APP_OPENGL_MAJOR_VERSION);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, APP_OPENGL_MINOR_VERSION);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, APP_OPENGL_DOUBLEBUFFER);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, APP_OPENGL_DEPTH_SIZE);

	//========================window creation=====================
	m_window = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		m_width, m_height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if (m_window == NULL) {
		std::cout << "Could not create window : " << SDL_GetError() << std::endl;
		SDL_Quit();
		return false;
	}

	//========================OPENGL context creation=====================
	m_openGLContext = SDL_GL_CreateContext(m_window);
	if (m_openGLContext == 0) {
		std::cout << "Failed to create OpenGL context : " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(m_window);
		SDL_Quit();

		return false;
	}

	

	std::cout << "OpenGL : " << glGetString(GL_VERSION) << std::endl;
	return true;
}

bool OpenGLScene::initGL()
{
	GLenum glewInitResult(glewInit());
	if (glewInitResult != GLEW_OK) {
		std::cout << "Could not init. GLEW : " <<
			glewGetErrorString(glewInitResult) << std::endl;
		return false;
	}

	//enable depth buffer test
	glEnable(GL_DEPTH_TEST);
	
	return true;
}

void OpenGLScene::events()
{
	m_inputs.Update();
	m_closed = m_inputs.closed();
}

void OpenGLScene::swapBuffers()
{
	SDL_GL_SwapWindow(m_window);
}

bool OpenGLScene::closed(){
	return m_closed;
}

void OpenGLScene::close() {
	m_closed = true;
}

const Input & OpenGLScene::inputs()
{
	return m_inputs;
}
