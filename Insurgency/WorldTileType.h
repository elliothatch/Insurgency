#pragma once
#include <string>
class WorldTileType
{
public:

	WorldTileType(void)
		:passable(true),
		transparent(true)
	{
		title = "Tile";
		dispCh = '.';
	}

	~WorldTileType(void)
	{
	}
	//getters
	bool getPassable() const {return passable;}
	bool getTransparent() const {return transparent;}
	std::string getTitle() const {return title;}
	//temp
	char getDispCh() const {return dispCh;}

	//setters
	void setPassable(bool val) {passable = val;}
	void setTransparent(bool val) {transparent = val;}
	void setTitle(std::string lTitle) {title = lTitle;}
	//temp
	void setDispCh(char lChar) {dispCh = lChar;}

private:
	std::string title;
	bool passable;
	bool transparent;
	//temp
	char dispCh;
};

