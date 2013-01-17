#pragma once
#include "SFMLEvent.h"
#include "SFMLStateMessage.h"
#include "ImageManager.h"
#include "SpriteManager.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include "FontManager.h"
#include "SFMLGUIElement.h"
#include "SFMLButton.h"
#include "AnimatedSprite.h"
#include "Functor.h"
#include "SFMLStateInfo.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <memory>


class GameStateBase : public SFMLEvent
{
public:
	typedef std::unique_ptr<GameStateBase> ptr;

	GameStateBase(const sf::Window& window);
	virtual ~GameStateBase(void);

	virtual void OnAwake(const SFMLStateInfo* lStateInfo) {}
	virtual void OnUpdate(void) {}
	virtual void OnRender(sf::RenderTarget& target) {drawDisplayList(target);}
	virtual void OnCleanup(void) {Cleanup();}
	virtual void OnSuspend(void) {}
	virtual void OnResume(void) {}

	//OnUpdate() called on all active states, then OnRender()

	void OnEvent(sf::Event& Event);

	SFMLStateMessage* GetStateMessage(void);

	void addStateMessage(SFMLStateMessage* stateMessage);
	
	//default events that most likely won't be overwritten
	virtual void OnClose(void);
	virtual void OnResize(int width, int height);
	virtual void OnMouseButtonPressed(sf::Mouse::Button button, int x, int y);
	virtual void OnMouseButtonReleased(sf::Mouse::Button button, int x, int y);
	virtual void OnMouseMoved(int x, int y);

	void addDrawable(std::unique_ptr<sf::Drawable> target);
	void removeDrawable(int index);
	void addGUIElement(std::unique_ptr<SFMLGUIElement> target); //must be used so mouse listeners work
	void removeGUIElement(SFMLGUIElement* target);

	SFMLGUIElement* getTopGUIElement(int X, int Y);
	bool pointCollided(SFMLGUIElement* target, int X, int Y);

	//these are called in derived classes that use mouse driven GUIs to handle click events
	//place them in the virtual overrides for SFMLEvent e.g. OnMouseButtonPressed(...)
	void MouseEvent_Pressed(sf::Mouse::Button button, int x, int y);
	void MouseEvent_Released(sf::Mouse::Button button, int x, int y);
	void MouseEvent_Moved(int x, int y);

	void Cleanup();

	//this function is usually called by derived classes in their OnCleanup function to clear out the display list
private:
	void CleanupDisplayList(void);
	void CleanupGUIElements(void);

protected:
	std::vector<SFMLStateMessage*> m_messages;
	const sf::Window* m_window;
private:
	std::vector<std::unique_ptr<sf::Drawable>> m_displayList;
	std::vector<SFMLGUIElement*> m_GUIElements;
public:
	bool m_transparent;
	bool m_allowSubUpdate;
	bool m_subUpdate;
	bool m_subRender;
protected:
	void drawDisplayList(sf::RenderTarget& target) const;
	void updateGUIElements();
	const std::vector<std::unique_ptr<sf::Drawable>>& getDisplayList() const;
	const std::vector<SFMLGUIElement*>& getGUIElements() const;
};
