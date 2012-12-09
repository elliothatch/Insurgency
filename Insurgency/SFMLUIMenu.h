#pragma once
#include "SFML-Template\SFMLGUIElement.h"
#include "UIMenu.h"
#include "SFMLCursesTextBox.h"
class SFMLUIMenu : public SFMLGUIElement
{
public:
	SFMLUIMenu(const sf::Window& window);
	virtual ~SFMLUIMenu(void);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual sf::FloatRect getLocalBounds(void) const = 0;
	virtual sf::FloatRect getGlobalBounds(void) const = 0;

	void moveSelection(int s);
	void moveCursorUp();
	void moveCursorDown();
	void selectCursor();
	bool stepBack();

	void updateMenus();
	void addMenuListTextBox(UIMenuList* list, int branchLevel, bool accessible = true);
	void setMenuListTextBoxColors(UIMenuList* list, int branchLevel, bool accessible);

	bool getMenuOptionAccessible(UIMenuOption* option);
	bool getMenuListOptionAccessible(UIMenuOption* option);

protected:
	std::vector<std::vector<SFMLCursesTextBox>> m_menuOptionTextBoxes; //external vector - menuList(branch) - internal vector menuOption
	SFMLCursesTextBox m_helpTextBox;
	std::unique_ptr<UIMenu> m_UIMenu;
	int m_selection;
	int m_branchLevel;
	sf::Color m_selectionTextColor;
	sf::Color m_selectionBackgroundColor;
	sf::Color m_textColor;
	sf::Color m_backgroundColor;
	sf::Color m_inaccessibleTextColorModifier;
	sf::Color m_inaccessibleBackgroundColorModifier;
};

