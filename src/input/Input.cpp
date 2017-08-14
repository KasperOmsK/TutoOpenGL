#include "Input.h"
#include <iostream>



Input::Input()
{
	m_mouseX = m_mouseX_rel = m_mouseY = m_mouseY_rel = 0;

	for (int i = 0; i < SDL_NUM_SCANCODES; i++) {
		if (i < 8) {
			m_buttons[i] = 0;
		}
		m_keys[i] = 0;
	}
	SetRelativeMouse(false);
}

void Input::Update()
{
	m_mouseX_rel = m_mouseY_rel = 0;

	while (SDL_PollEvent(&m_event)) {

		if (m_event.window.event == SDL_WINDOWEVENT_CLOSE) {
			m_closed = true;
			return;
		}

		//============Keyboard============
		if (m_event.type == SDL_KEYDOWN) {
			m_keys[m_event.key.keysym.scancode] = true;
		}
		else if (m_event.type == SDL_KEYUP) {
			m_keys[m_event.key.keysym.scancode] = false;
		}

		//=============mouse button==========
		if (m_event.type == SDL_MOUSEBUTTONDOWN) {
			m_buttons[m_event.button.button] = true;
		}
		else if (m_event.type == SDL_MOUSEBUTTONUP) {
			m_buttons[m_event.button.button] = false;
		}

		if (m_event.type == SDL_MOUSEMOTION) {
			m_mouseX = m_event.motion.x;
			m_mouseY = m_event.motion.y;
			m_mouseX_rel = m_event.motion.xrel;
			m_mouseY_rel = m_event.motion.xrel;
		}

		//==============mouse cursor==========
	}
}

bool Input::IsKeyDown(SDL_Scancode code) const
{
	return m_keys[code];
}

void Input::SetRelativeMouse(bool value)
{
	if (value)
		SDL_SetRelativeMouseMode(SDL_TRUE);
	else
		SDL_SetRelativeMouseMode(SDL_FALSE );
}

bool Input::IsButtonDown(int button) const {
	return m_buttons[button];
}

int Input::GetMouseX() const
{
	return m_mouseX;
}
int Input::GetMouseY() const
{
	return m_mouseY;
}
int Input::GetMouseXRelative() const
{
	return m_mouseX_rel;
}
int Input::GetMouseYRelative() const
{
	return m_mouseY_rel;
}
bool Input::closed() const {
	return m_closed;
}

Input::~Input()
{
}
