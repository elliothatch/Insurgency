#pragma once
#include "WorldTile.h"
#include <memory>
#include <array>
class WorldRegion
{
public:
	typedef std::unique_ptr<WorldRegion> ptr;
	static const int kRegionSize = 10;

	WorldRegion(void);
	~WorldRegion(void);

	WorldTile& getTile(std::pair<int,int> loc);
	void setTile(std::pair<int,int> loc, WorldTile::ptr lTile); //deletes old tile
	void save(void);
	void load(void);

	int getSize() const {return kRegionSize;}

private:
	std::array<std::array<WorldTile::ptr, kRegionSize>, kRegionSize> tiles;

};

