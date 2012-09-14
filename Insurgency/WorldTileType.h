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

	//setters
	void setPassable(bool val);
	void setTransparent(bool val);
	void setTitle(std::string lTitle);

private:
	std::string m_title;
	bool m_passable;
	bool m_transparent;
};

