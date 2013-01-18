#pragma once
#include <SFML/Window.hpp>
class SFMLEvent
{
public:
	SFMLEvent(void);
	virtual ~SFMLEvent(void);

	void OnEvent(sf::Event& Event);

	virtual void OnClose(void) {} 
	virtual void OnResize(int width, int height) {}
	virtual void OnLoseFocus(void) {}
	virtual void OnGainFocus(void) {}
	virtual void OnTextEntered(sf::Uint32 text) {}
	virtual void OnKeyPressed(sf::Keyboard::Key key, bool alt, bool control, bool shift) {}
	virtual void OnKeyReleased(sf::Keyboard::Key key, bool alt, bool control, bool shift) {}
	virtual void OnMouseWheelMoved(int delta, int x, int y) {}
	virtual void OnMouseButtonPressed(sf::Mouse::Button button, int x, int y) {}
	virtual void OnMouseButtonReleased(sf::Mouse::Button button, int x, int y) {}
	virtual void OnMouseMoved(int x, int y) {}
	virtual void OnMouseEnter(void) {}
	virtual void OnMouseLeave(void) {}
	virtual void OnJoystickButtonPressed(unsigned int button, unsigned int joystickId) {}
	virtual void OnJoystickButtonReleased(unsigned int button, unsigned int joystickId) {}
	virtual void OnJoystickMoved(sf::Joystick ::Axis axis, float position, unsigned int joystickId) {}
	virtual void OnJoystickConnected(unsigned int joystickId) {}
	virtual void OnJoystickDisconnected(unsigned int joystickId) {}
};

