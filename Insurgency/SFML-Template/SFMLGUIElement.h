#pragma once
#include "Functor.h"
#include <SFML/Graphics.hpp>
#include <memory>

class SFMLGUIElement
	:public sf::Drawable, public sf::Transformable
{
public:
	SFMLGUIElement(void);
	~SFMLGUIElement(void);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates) const = 0;
	virtual sf::FloatRect getLocalBounds(void) const = 0;
	virtual sf::FloatRect getGlobalBounds(void) const = 0;

	void OnMouseLeftPressed(void);
	void OnMouseLeftReleased(void);
	void OnMouseRightPressed(void);
	void OnMouseRightReleased(void);
	void OnMouseMiddlePressed(void);
	void OnMouseMiddleReleased(void);

	//turn to unclicked, even if the button itself isn't released on
	void OnGlobalMouseLeftReleased(void);
	void OnGlobalMouseRightReleased(void);
	void OnGlobalMouseMiddleReleased(void);

	void setMouseLeftPressedFunction(std::shared_ptr<TFunctorBase> func) {m_MouseLeftPressedfunc = func;}
	void setMouseLeftReleasedFunction(std::shared_ptr<TFunctorBase> func) {m_MouseLeftReleasedfunc = func;}
	void setMouseRightPressedFunction(std::shared_ptr<TFunctorBase> func) {m_MouseRightPressedfunc = func;}
	void setMouseRightReleasedFunction(std::shared_ptr<TFunctorBase> func) {m_MouseRightReleasedfunc = func;}
	void setMouseMiddlePressedFunction(std::shared_ptr<TFunctorBase> func) {m_MouseMiddlePressedfunc = func;}
	void setMouseMiddleReleasedFunction(std::shared_ptr<TFunctorBase> func) {m_MouseMiddleReleasedfunc = func;}
	void setMouseLeftClickedFunction(std::shared_ptr<TFunctorBase> func) {m_MouseLeftClickedfunc = func;}
	void setMouseRightClickedFunction(std::shared_ptr<TFunctorBase> func) {m_MouseRightClickedfunc = func;}
	void setMouseMiddleClickedFunction(std::shared_ptr<TFunctorBase> func) {m_MouseMiddleClickedfunc = func;}
	
protected:
	bool m_leftPressed;
	bool m_rightPressed;
	bool m_middlePressed;

	std::shared_ptr<TFunctorBase> m_MouseLeftPressedfunc;
	std::shared_ptr<TFunctorBase> m_MouseLeftReleasedfunc;
	std::shared_ptr<TFunctorBase> m_MouseRightPressedfunc;
	std::shared_ptr<TFunctorBase> m_MouseRightReleasedfunc;
	std::shared_ptr<TFunctorBase> m_MouseMiddlePressedfunc;
	std::shared_ptr<TFunctorBase> m_MouseMiddleReleasedfunc;
	std::shared_ptr<TFunctorBase> m_MouseLeftClickedfunc;
	std::shared_ptr<TFunctorBase> m_MouseRightClickedfunc;
	std::shared_ptr<TFunctorBase> m_MouseMiddleClickedfunc;
};

