#pragma once
#include <string>
class WorldTileType
{
public:

	WorldTileType(void);
	~WorldTileType(void);
	//getters
	bool getPassable() const;
	bool getTransparent() const;
	std::string getTitle() const;
	//temp
	char getDispCh() const;

	//setters
	void setPassable(bool val);
	void setTransparent(bool val);
	void setTitle(std::string lTitle);
	//temp
	void setDispCh(char lChar);

private:
	std::string m_title;
	bool m_passable;
	bool m_transparent;
	//temp
	char m_dispCh;
};

