#include "StdAfx.h"
#include "SFMLEvent.h"


SFMLEvent::SFMLEvent(void)
{
}


SFMLEvent::~SFMLEvent(void)
{
}

void SFMLEvent::OnEvent(sf::Event& Event)
{
	switch(Event.type)
	{
	case sf::Event::Closed:
		OnClose();
		break;
	case sf::Event::Resized:
		OnResize(Event.size.width, Event.size.height);
		break;
	case sf::Event::LostFocus:
		OnLoseFocus();
		break;
	case sf::Event::GainedFocus:
		OnGainFocus();
		break;
	case sf::Event::TextEntered:
		OnTextEntered(Event.text.unicode);
		break;
	case sf::Event::KeyPressed:
		OnKeyPressed(Event.key.code, Event.key.alt, Event.key.control, Event.key.shift);
		break;
	case sf::Event::KeyReleased:
		OnKeyReleased(Event.key.code, Event.key.alt, Event.key.control, Event.key.shift);
		break;
	case sf::Event::MouseWheelMoved:
		OnMouseWheelMoved(Event.mouseWheel.delta, Event.mouseWheel.x, Event.mouseWheel.y);
		break;
	case sf::Event::MouseButtonPressed:
		OnMouseButtonPressed(Event.mouseButton.button, Event.mouseButton.x, Event.mouseButton.y);
		break;
	case sf::Event::MouseButtonReleased:
		OnMouseButtonReleased(Event.mouseButton.button, Event.mouseButton.x, Event.mouseButton.y);
		break;
	case sf::Event::MouseMoved:
		OnMouseMoved(Event.mouseMove.x, Event.mouseMove.y);
		break;
	case sf::Event::MouseEntered:
		OnMouseEnter();
		break;
	case sf::Event::MouseLeft:
		OnMouseLeave();
		break;
	case sf::Event::JoystickButtonPressed:
		OnJoystickButtonPressed(Event.joystickButton.button, Event.joystickButton.joystickId);
		break;
	case sf::Event::JoystickButtonReleased:
		OnJoystickButtonReleased(Event.joystickButton.button, Event.joystickButton.joystickId);
		break;
	case sf::Event::JoystickMoved:
		OnJoystickMoved(Event.joystickMove.axis, Event.joystickMove.position, Event.joystickMove.joystickId);
		break;
	case sf::Event::JoystickConnected:
		OnJoystickConnected(Event.joystickConnect.joystickId);
		break;
	case sf::Event::JoystickDisconnected:
		OnJoystickDisconnected(Event.joystickConnect.joystickId);
		break;
	default:
		printf("EVENT NOT HANDLED\n");
		}
}