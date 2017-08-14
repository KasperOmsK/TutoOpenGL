#pragma once
#include <string>
#include <SDL2\SDL.h>
#include <GL\glew.h>
#include "../input/Input.h"

class OpenGLScene
{
	public:
		OpenGLScene(std::string _title, int _width, int _height);
		~OpenGLScene();
	private:
		std::string m_title;
		unsigned int m_width;
		unsigned int m_height;
		SDL_Window* m_window;
		SDL_GLContext m_openGLContext;
		Input m_inputs;
		bool m_closed;

	public:
		bool initWindow();
		bool initGL();
		void events();
		void swapBuffers();
		bool closed();
		void close();
		const Input& inputs();
};

