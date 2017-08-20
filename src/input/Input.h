#pragma once
#include "SDL2\SDL.h"
#include "../math/Vector3.h"
class Input
{
	struct KeyData {
		KeyData();
		KeyData(int code);
		int code;
		bool up;
		bool held;
		bool down;
	};
	
	private:
		SDL_Event m_event;
		bool m_closed;
		KeyData m_keys[511+8];
		KeyData m_keys_prev[511+8];
	

		int m_mouseX;
		int m_mouseY;
		int m_mouseX_rel;
		int m_mouseY_rel;

	public:
		Input();
		~Input();
		void Update();
		
		bool IsKeyDown(SDL_Scancode code) const;
		bool IsKeyUp(SDL_Scancode code) const;
		bool IsKeyHeld(SDL_Scancode code) const;
		
		bool IsButtonUp(int button) const;
		bool IsButtonDown(int button) const;
		bool IsButtonHeld(int button) const;

		void SetRelativeMouse(bool value);
		int GetMouseX() const;
		int GetMouseY() const;
		Vector3 GetMousePosition() const;
		int GetMouseXRelative() const;
		int GetMouseYRelative() const;
		Vector3 GetMousePositionRelative() const;
		bool closed() const;
		void SetCursorRelative(bool state) const;

};