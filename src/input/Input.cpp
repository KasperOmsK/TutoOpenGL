#include "Input.h"
#include <iostream>
#include "../math/math.h"
Input::Input()
{
	m_mouseX = m_mouseX_rel = m_mouseY = m_mouseY_rel = 0;

	for (int i = 0; i < SDL_NUM_SCANCODES+8; i++) {
			m_keys[i] = KeyData(i);
	}
	SetRelativeMouse(false);
}

void Input::Update()
{
	//reinit
	for (int i = 0; i < SDL_NUM_SCANCODES+8; i++)
	{
		m_keys[i].up = m_keys[i].down = false;
	}
	m_mouseX_rel = m_mouseY_rel = 0;

	//event handling
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		
		if (e.window.event == SDL_WINDOWEVENT_CLOSE) {
			m_closed = true;
			return;
		}

		if (e.type == SDL_KEYDOWN) {
			if (e.key.repeat == 0) {
				int code = e.key.keysym.scancode;
				m_keys[code].down = true;
				m_keys[code].held = true;
			}
		}
		else if (e.type == SDL_KEYUP) {
			if (e.key.repeat == 0) {
				int code = e.key.keysym.scancode;
				m_keys[code].up = true;
				m_keys[code].held = false;
			}
		}

		if (e.type == SDL_MOUSEBUTTONDOWN) {
			m_keys[511+e.button.button].down = true;
			m_keys[511+e.button.button].held = true;
		}
		else if (e.type == SDL_MOUSEBUTTONUP) {
			m_keys[511+e.button.button].up = true;
			m_keys[511+e.button.button].held = false;
		}

		if (e.type == SDL_MOUSEMOTION) {
			m_mouseX = e.motion.x;
			m_mouseY = e.motion.y;
			m_mouseX_rel += e.motion.xrel;
			m_mouseY_rel += e.motion.yrel;
		}
	}
}

bool Input::IsKeyDown(SDL_Scancode code) const
{
	return m_keys[code].down;
}
bool Input::IsKeyUp(SDL_Scancode code) const
{
	return m_keys[code].up;
}
bool Input::IsKeyHeld(SDL_Scancode code) const
{
	return m_keys[code].held;
}

bool Input::IsButtonUp(int button) const
{
	if (button < 1 || button > 8)
		return false;

	return m_keys[511+button].up;
}
bool Input::IsButtonDown(int button) const
{
	if (button < 1 || button > 8)
		return false;

	return m_keys[511 + button].down;
}
bool Input::IsButtonHeld(int button) const
{
	if (button < 1 || button > 8)
		return false;

	return m_keys[511 + button].held;
}

void Input::SetRelativeMouse(bool value)
{
	if (value)
		SDL_SetRelativeMouseMode(SDL_TRUE);
	else
		SDL_SetRelativeMouseMode(SDL_FALSE );
}
int Input::GetMouseX() const
{
	return m_mouseX;
}
int Input::GetMouseY() const
{
	return m_mouseY;
}
Vector3 Input::GetMousePosition() const {
	return Vector3(GetMouseX(), GetMouseY(), 0);
}

int Input::GetMouseXRelative() const
{
	return m_mouseX_rel;
}
int Input::GetMouseYRelative() const
{
	return m_mouseY_rel;
}

Vector3 Input::GetMousePositionRelative() const
{
	return Vector3(GetMouseXRelative(), GetMouseYRelative(), 0);
}

bool Input::closed() const {
	return m_closed;
}
void Input::SetCursorRelative(bool state) const
{
	SDL_bool s = state ? SDL_TRUE : SDL_FALSE;
	SDL_SetRelativeMouseMode(s);
}

Input::~Input()
{
}


Input::KeyData::KeyData()
	: KeyData(SDL_SCANCODE_0)
{	
}
Input::KeyData::KeyData(int _code)
{
	up = down = held = false;
	code = _code;
}
