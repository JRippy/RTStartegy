#include "Config.h"
#include "Texture.h"

#pragma once
class Unit
{
public:
	Unit();
	
	Unit(SDL_Renderer * gRenderer);

	//Getter and setter
	float getUPosX();
	float getUPosY();

	void setUPosX(float f);
	void setUPosY(float f);

	float getUPosToX();
	float getUPosToY();

	void setUPosToX(float f);
	void setUPosToY(float f);

	float randomFloat(float a, float b);

	bool loadMediaUnit(SDL_Renderer * gRenderer);

	void move(float timeStep);

	void render(SDL_Renderer * gRenderer);

	void reset();

private:

	//Coordinate
	float uPosX, uPosY;
	float toX, toY;
	float offSetX, offSetY;

	//Dead Flag
	bool iDead;

	//Loaded
	bool Loaded;

	Config c;

	//Texture
	Texture unitTexture;
};

