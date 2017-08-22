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
		//desc : handle SDL initialization & create a non initialized openGL context
		//returns : true if init succeeded, false otherwise
		bool initWindow();
		//desc : init openGL stuff (glew...)
		//returns : true if init succeeded, false otherwise
		bool initGL();
		//desc : call Input member update method
		//note : has to be called before using inputs
		void updateInputs();
		//desc : wrap up for SDL_SwapBuffers
		void swapBuffers();
		//desc : close the window at next update
		void close();
		//desc : is the window supposed to be close ?
		bool closed() const;

		//desc : returns the window's current title
		const std::string& GetTitle() const;
		
		//desc : Set the window's current title
		void SetTitle(const std::string& newTitle);

		//desc : returns a reference to Input member, used to get input information (key pressed, mouse position...)
		const Input& inputs();
};

