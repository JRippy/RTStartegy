#include "pch.h"
#include "Config.h"


Config::Config()
{
}


int Config::getScreenHeight()
{
	return SCREEN_HEIGHT;
}

int Config::getScreenWidth()
{
	return SCREEN_WIDTH;
}

int Config::getUnitHeight()
{
	return UNIT_HEIGHT;
}

int Config::getUnitWidth()
{
	return UNIT_WIDTH;
}

int Config::getNumUnit()
{
	return UNIT_NUM;
}

int Config::getVelUnit()
{
	return UNIT_VEL;
}
