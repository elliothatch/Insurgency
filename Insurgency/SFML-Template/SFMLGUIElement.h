#pragma once
#include "Functor.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <functional>

class SFMLGUIElement
	:public sf::Drawable, public sf::Transformable
{
public:
	SFMLGUIElement(const sf::Window& window);
	~SFMLGUIElement(void);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates) const = 0;
	virtual sf::FloatRect getLocalBounds(void) const = 0;
	virtual sf::FloatRect getGlobalBounds(void) const = 0;
	virtual void update();
	sf::Vector2f getLocalPoint(float x, float y) const;
	sf::Vector2f getLocalPoint(const sf::Vector2f& point) const;
	sf::Vector2i getLocalPoint(int x, int y) const;
	sf::Vector2i getLocalPoint(const sf::Vector2i& point) const;

	void OnMouseLeftPressed();
	void OnMouseLeftReleased();
	void OnMouseRightPressed();
	void OnMouseRightReleased();
	void OnMouseMiddlePressed();
	void OnMouseMiddleReleased();
	void OnMouseRollover();

	//turn to unclicked, even if the button itself isn't released on
	void OnGlobalMouseLeftReleased();
	void OnGlobalMouseRightReleased();
	void OnGlobalMouseMiddleReleased();

	void addMouseLeftPressedFunction(std::shared_ptr<TFunctorBase> func);
	void addMouseLeftReleasedFunction(std::shared_ptr<TFunctorBase> func);
	void addMouseRightPressedFunction(std::shared_ptr<TFunctorBase> func);
	void addMouseRightReleasedFunction(std::shared_ptr<TFunctorBase> func);
	void addMouseMiddlePressedFunction(std::shared_ptr<TFunctorBase> func);
	void addMouseMiddleReleasedFunction(std::shared_ptr<TFunctorBase> func);
	void addMouseLeftClickedFunction(std::shared_ptr<TFunctorBase> func);
	void addMouseRightClickedFunction(std::shared_ptr<TFunctorBase> func);
	void addMouseMiddleClickedFunction(std::shared_ptr<TFunctorBase> func);
	void addMouseRolloverFunction(std::shared_ptr<TFunctorBase> func);

	void removeMouseLeftPressedFunction(TFunctorBase& func);
	void removeMouseLeftReleasedFunction(TFunctorBase& func);
	void removeMouseRightPressedFunction(TFunctorBase& func);
	void removeMouseRightReleasedFunction(TFunctorBase& func);
	void removeMouseMiddlePressedFunction(TFunctorBase& func);
	void removeMouseMiddleReleasedFunction(TFunctorBase& func);
	void removeMouseLeftClickedFunction(TFunctorBase& func);
	void removeMouseRightClickedFunction(TFunctorBase& func);
	void removeMouseMiddleClickedFunction(TFunctorBase& func);
	void removeMouseRolloverFunction(TFunctorBase& func);

	std::vector<std::shared_ptr<TFunctorBase>>::iterator getFunctionVectorIterator(
		std::vector<std::shared_ptr<TFunctorBase>>& vec, TFunctorBase& func);
	
protected:
	bool m_leftPressed;
	bool m_rightPressed;
	bool m_middlePressed;
	std::reference_wrapper<const sf::Window> m_window;

	std::vector<std::shared_ptr<TFunctorBase>> m_MouseLeftPressedfunc;
	std::vector<std::shared_ptr<TFunctorBase>> m_MouseLeftReleasedfunc;
	std::vector<std::shared_ptr<TFunctorBase>> m_MouseRightPressedfunc;
	std::vector<std::shared_ptr<TFunctorBase>> m_MouseRightReleasedfunc;
	std::vector<std::shared_ptr<TFunctorBase>> m_MouseMiddlePressedfunc;
	std::vector<std::shared_ptr<TFunctorBase>> m_MouseMiddleReleasedfunc;
	std::vector<std::shared_ptr<TFunctorBase>> m_MouseLeftClickedfunc;
	std::vector<std::shared_ptr<TFunctorBase>> m_MouseRightClickedfunc;
	std::vector<std::shared_ptr<TFunctorBase>> m_MouseMiddleClickedfunc;
	std::vector<std::shared_ptr<TFunctorBase>> m_MouseRolloverfunc;
};

