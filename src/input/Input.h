#pragma once
#include "SDL2\SDL.h"
class Input
{
	private:
		SDL_Event m_event;
		bool m_closed;
		bool m_keys[1024];
		bool m_buttons[8];

		int m_mouseX;
		int m_mouseY;
		int m_mouseX_rel;
		int m_mouseY_rel;

	public:
		Input();
		~Input();
		void Update();
		bool IsKeyDown(SDL_Scancode code) const;
		void SetRelativeMouse(bool value);
		bool IsButtonDown(int button) const;
		int GetMouseX() const;
		int GetMouseY() const;
		int GetMouseXRelative() const;
		int GetMouseYRelative() const;
		bool closed() const;

};

//!:;,'g,;:!%%m