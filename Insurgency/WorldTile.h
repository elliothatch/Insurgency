#pragma once
#include <string>
#include <memory>
#include "WorldTileType.h"

class WorldTile
{
public:
	typedef std::unique_ptr<WorldTile> ptr;
	WorldTile(const WorldTileType& lType);
	~WorldTile(void);

	bool isPassable(void) const;
	bool isTransparent(void) const;
	std::string getTitle(void) const;

private:
	const WorldTileType* m_type;
};

