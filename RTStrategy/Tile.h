#pragma once
class Tile
{
public:
	Tile();
	Tile(int x, int y, int coord, int nmB, int visib);

	int posBX;
	int posBY;
	int coordinate;
	int numTile;
	bool visible;
};

