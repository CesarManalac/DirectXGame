#include "InputSystem.h"

#include <Windows.h>

InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
}

void InputSystem::update()
{
	POINT current_mouse = {};
	::GetCursorPos(&current_mouse);

	if (first_time) {
		m_old = Point(current_mouse.x, current_mouse.y);
		first_time = false;
	}

	if (current_mouse.x != m_old.m_x || current_mouse.y != m_old.m_y) {
		
		std::unordered_set<InputListener*>::iterator it = m_set_listeners.begin();

		while (it != m_set_listeners.end()) {

			(*it)->onMouseMove(Point(current_mouse.x - m_old.m_x, current_mouse.y - m_old.m_y));
			++it;
		}
	}
	m_old = Point(current_mouse.x, current_mouse.y);

	if (::GetKeyboardState(m_keys_state)) {
		for (unsigned int i = 0; i < 256; i++) {
			//Key is down
			if (m_keys_state[i] & 0x80) {
				std::unordered_set<InputListener*>::iterator it = m_set_listeners.begin();

				while (it != m_set_listeners.end()) {
					if (i == VK_LBUTTON) {
						if (m_keys_state[i] != m_old_keys_state[i]) {
							(*it)->onLeftMouseDown(Point(current_mouse.x, current_mouse.y));
						}
					}
					else if (i == VK_RBUTTON) {
						if (m_keys_state[i] != m_old_keys_state[i]) {
							(*it)->onRightMouseDown(Point(current_mouse.x, current_mouse.y));
						}
					}
					else
						(*it)->onKeyDown(i);
					++it;
				}
			}
			else {
				if (m_keys_state[i] != m_old_keys_state[i]) {
					std::unordered_set<InputListener*>::iterator it = m_set_listeners.begin();

					while (it != m_set_listeners.end()) {
						if (i == VK_LBUTTON) {
							if (m_keys_state[i] != m_old_keys_state[i]) {
								(*it)->onLeftMouseUp(Point(current_mouse.x, current_mouse.y));
							}
						}
						else if (i == VK_RBUTTON) {
							if (m_keys_state[i] != m_old_keys_state[i]) {
								(*it)->onRightMouseUp(Point(current_mouse.x, current_mouse.y));
							}
						}
						else
							(*it)->onKeyUp(i);
						++it;
					}
				}
			}
		}
		//store current keys state to old keys state buffer
		::memcpy(m_old_keys_state, m_keys_state, sizeof(unsigned char) * 256);
	}

}

void InputSystem::addListener(InputListener* listener)
{
	
	m_set_listeners.insert(listener);
}

void InputSystem::removeListener(InputListener* listener)
{
	m_set_listeners.erase(listener);
}

InputSystem* InputSystem::get()
{
	static InputSystem system;
	return &system;
}
