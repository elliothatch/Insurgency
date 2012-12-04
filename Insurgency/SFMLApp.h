#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <memory>

#include "SFML-Template/SFMLEvent.h"
#include "SFML-Template/GameStateBase.h"
#include "SFML-Template/SoundManager.h"
#include "SFML-Template/TextureManager.h"
#include "SFML-Template/SpriteManager.h"
#include "SFML-Template/FontManager.h"
#include "SFMLCursesCharManager.h"

#include "GameState_InsurgencyGame.h"
#include "GameState_InsurgencyInventory.h"
#include "GameState_InsurgencyEntityActions.h"


class SFMLApp
{
public:
	SFMLApp(void);
	~SFMLApp(void);

	int OnExecute(void);

	bool OnInit(void);
	void OnEvent(sf::Event& Event);
    void OnUpdate(void);
    void OnRender(void);
    void OnCleanup(void);

	void registerState(GameStateBase::ptr gameState, std::string stateID);
	void unregisterState(std::string stateID); //can invalidate active states
	void changeState(std::string stateID, SFMLStateInfo* stateInfo); //replaces the current state
	void pushState(std::string stateID, SFMLStateInfo* stateInfo);
	void popState(void);
	void removeState(std::string stateID);

	GameStateBase* getState(std::string stateID);

	//message handling functions
	void decipherMessage(SFMLStateMessage* message);
	void OnClose(void);
	void OnResize(int width, int height);

private:
	bool m_running;
	sf::RenderWindow m_mainWindow;
	std::vector<GameStateBase*> m_states;
	std::map<std::string, GameStateBase::ptr> m_registeredGameStates;
};

