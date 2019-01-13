#pragma once
class Config
{
public:
	Config();

	static int getScreenHeight();
	static int getScreenWidth();

	static int getUnitHeight();
	static int getUnitWidth();

	static int getNumUnit();
	static int getNumUnitEnemy();

	static int getVelUnit();

	static int getTileHeight();
	static int getTileWidth();
	static int getTileNum();
	static int getTileNumColumn();
	static int * getTileGrid();

private:

	//Screen dimension constants
	static const int SCREEN_WIDTH = 1000;
	static const int SCREEN_HEIGHT = 800;

	static const int UNIT_NUM = 10;

	static const int UNIT_ENEMY_NUM = 2;

	static const int UNIT_VEL = 5;

	static const int UNIT_WIDTH = 20;
	static const int UNIT_HEIGHT = 20;

	//The dimensions of the tile
	static const int TILE_WIDTH = 100;
	static const int TILE_HEIGHT = 80;
	static const int TILE_NUM = 80;
	static const int TILE_NUMCOLUMN = 10;

};