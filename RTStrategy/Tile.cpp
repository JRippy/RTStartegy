#include "pch.h"
#include "Tile.h"


Tile::Tile()
{
}

Tile::Tile(int x, int y, int coord, int nmB, int visib)
{
	posBX = x;
	posBY = y;
	coordinate = coord;
	numTile = numTile;
	if (visib == 1)
	{
		visible = true;
	}
	else
	{
		visible = false;
	}
}