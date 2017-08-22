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
		//desc : Update all input data by polling event from SDL
		//Note : Need to be called before trying to access input data
		void Update();
		
		//desc : return true if the key has been pressed DURING THIS FRAME, false otherwise
		bool IsKeyDown(SDL_Scancode code) const;
		//desc : return true if the key has been released DURING THIS FRAME, false otherwise
		bool IsKeyUp(SDL_Scancode code) const;
		//desc : return true if the key is currently held down, false otherwise
		bool IsKeyHeld(SDL_Scancode code) const;
		
		//desc : return true if the button has been pressed DURING THIS FRAME, false otherwise
		bool IsButtonUp(int button) const;
		//desc : return true if the button has been released DURING THIS FRAME, false otherwise
		bool IsButtonDown(int button) const;
		//desc : return true if the button is currently held down, false otherwise
		bool IsButtonHeld(int button) const;

		//desc : returns mouseX position relative to window
		int GetMouseX() const;
		//desc : returns mouseY position relative to window
		int GetMouseY() const;
		//desc : returns mouse position relative to window
		Vector3 GetMousePosition() const;
		//desc : returns how much the mouse has moved since last frame on the X axis
		int GetMouseXRelative() const;
		//desc : returns how much the mouse has moved since last frame on the Y axis
		int GetMouseYRelative() const;
		//desc : returns how much the mouse has moved since last frame
		Vector3 GetMousePositionRelative() const;
		//desc : Has the user pressed the close window button ?
		bool closed() const;
		//desc : true = cursor is locked in window, false = cursor is free to go wherever it goddamn pleases
		void SetCursorRelative(bool state) const;

};