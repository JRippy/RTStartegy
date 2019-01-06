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

	static int getVelUnit();

private:

	//Screen dimension constants
	static const int SCREEN_WIDTH = 800;
	static const int SCREEN_HEIGHT = 600;

	static const int UNIT_NUM = 5;

	static const int UNIT_VEL = 50;

	static const int UNIT_WIDTH = 20;
	static const int UNIT_HEIGHT = 20;

};