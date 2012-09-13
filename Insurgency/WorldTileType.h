#pragma once
#include <string>
class WorldTileType
{
public:
	typedef unsigned int DisplayID;
	WorldTileType(void);
	~WorldTileType(void);
	//getters
	bool getPassable() const;
	bool getTransparent() const;
	std::string getTitle() const;
	//temp
	DisplayID getDisplayID() const;

	//setters
	void setPassable(bool val);
	void setTransparent(bool val);
	void setTitle(std::string lTitle);
	//temp
	void setDisplayID(DisplayID dispID);

private:
	std::string m_title;
	bool m_passable;
	bool m_transparent;
	DisplayID m_displayID;
};

