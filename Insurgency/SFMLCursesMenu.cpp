#include "StdAfx.h"
#include "SFMLCursesMenu.h"


SFMLCursesMenu::SFMLCursesMenu(void)
{
}


SFMLCursesMenu::~SFMLCursesMenu(void)
{
}

void SFMLCursesMenu::setTrunk(SFMLCursesMenuList* menuList)
{
	currentMenuList = menuList;
	previousMenuList = nullptr;
	branch.clear();
	branch.push_back(menuList);
	update();
}

void SFMLCursesMenu::select(int n)
{
	selection = n;
	currentMenuList->selection = n;
	if(currentMenuList->options.size())
	{
		if(currentMenuList->options[n]->target)
		{
			nextMenuList = currentMenuList->options[n]->target;
		} 
		else 
		{
			nextMenuList = nullptr;
		}
	}
	else
	{
		nextMenuList = nullptr;
	}
	/*
	if(parent) 
		renderMenu();
	if(!hideChangeSelection) 
		changeSelection();
		*/
}

void SFMLCursesMenu::stepRight()
{
	if(!(nextMenuList && !nextMenuList->accessible) && currentMenuList->options[selection]->active)
	{
		// walk forward
		if(nextMenuList)
		{
			branch.push_back(nextMenuList);
			previousMenuList = currentMenuList;
			currentMenuList = nextMenuList;	
		// nothing to walk forward to - call the executeSelection
		} 
		else 
		{
			executeSelection();
			int selectionStep = currentMenuList->options[currentMenuList->selection]->selectionStep;
			if(selectionStep == SFMLCursesMenuOption::TRUNK) 
				setTrunk(branch[0]);
			else 
			{
				if(selectionStep == SFMLCursesMenuOption::EXIT_MENU)
				{
					setTrunk(branch[0]);
				} 
				else 
				{
					// inspect the branch list for empty menu lists that will crash the walk back
					// upon finding one we drop out to the root menu
					for(int i = branch.size() - 1; i > -1; i--)
					{
						if(branch[i]->options.size() == 0)
						{
							setTrunk(branch[0]);
							return;
						}
					}
					// the step back and forth shakes out select events and updates the labels
					while(selectionStep--)
					{
						stepLeft();
					}
					stepRight();
				}
			}
		}
	}
}

void SFMLCursesMenu::stepLeft()
{
	if(previousMenuList)
	{
		branch.pop_back();
		nextMenuList = currentMenuList;
		currentMenuList = previousMenuList;
		if(branch.size() > 1)
			previousMenuList = branch[branch.size() - 2];
		else
			previousMenuList = nullptr;
		update();
	}
}

void SFMLCursesMenu::update()
{
	select(currentMenuList->selection);
}
