#include "StdAfx.h"
#include "CursesGameWorldWindow.h"


CursesGameWorldWindow::CursesGameWorldWindow(int lStartY, int lStartX, int lHeight, int lWidth)
	:CursesWindow(lStartY, lStartX, lHeight, lWidth)
{
}

CursesGameWorldWindow::~CursesGameWorldWindow(void)
{
}

void CursesGameWorldWindow::refWin(const GameWorld& lGameWorld, std::pair<int,int> lCenterLoc)
{
	//const chtype attrVisible = A_NORMAL;
	//const chtype attrRemembered = COLOR_PAIR(BBLACK_BLACK);
	for(int i = 0; i < height; i++)
	{
		const int y = lCenterLoc.second + (i-height/2);
		for(int j = 0; j<width; j++)
		{
			const int x = lCenterLoc.first + (j-width/2);
			std::pair<int,int> tPair(x,y);
			//std::map<std::pair<int,int>,CUnit*>::const_iterator unitIt = lGameWorld.unitCoord.find(tPair);
			//FOV
			//int distX = width/2 - lGameWorld.unitList[0]->fovCnt.centerX;
			//int distY = height/2 - lGameWorld.unitList[0]->fovCnt.centerY;
			//std::map<std::pair<int,int>,bool>::const_iterator it = lGameWorld.unitList[0]->fovCnt.rememberedCell.find(tPair);
			//if(it != lGameWorld.unitList[0]->fovCnt.rememberedCell.end())
			//{
				//if(lGameWorld.unitList[0]->visible(tPair.first,tPair.second))
					//wattron(main,attrVisible);
				//else
					//wattron(main,attrRemembered);
				//if there is a unit at that square, draw the unit
				//if(unitIt != lGameWorld.unitCoord.end())
				//{
				//	mvwaddch(main,i,j,unitIt->second->dispCh);
				//}
				//else if there is an object on the ground there, draw the object
				//multiple objects???
				//else
				//{
					//std::map<std::pair<int,int>,std::vector<CItem*>>::const_iterator itemIt = lGameWorld.itemCoord.find(tPair);
					//if(itemIt != lGameWorld.itemCoord.end())
					//{
						//mvwaddch(main,i,j,itemIt->second.front()->dispCh);
					//}
					//else
					//{
						//std::map<std::pair<int,int>,eInteract*>::const_iterator interIt = lGameWorld.eInterCoord.find(tPair);
						//else if there is an entity there (furniture) draw the entity
						//if(interIt != lGameWorld.eInterCoord.end())
						//{
							//mvwaddch(main,i,j,interIt->second->dispCh);
						//}
						//otherwise just draw the floor or wall there
						//else
						//{
			//testing stuff - yeah I know...
			wattron(main, COLOR_PAIR(WHITE_BLACK));
							mvwaddch(main,i,j,lGameWorld.lookupTile(tPair).getDisplayID());
			if(!lGameWorld.lookupTile(tPair).isPassable())
			{
				//setCharFGColor(i,j, WHITE);
				setCharFGColor(i,j,GREEN);
			}
						//}
					//}
				//}
				//wattroff(main,attrVisible);
				//wattroff(main,attrRemembered);
			//}
			//else
			//{
			//	mvwaddch(main,i,j,' ');
			//}
		}
	}
	touchwin(main);
	wrefresh(main);
}