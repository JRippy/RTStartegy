#pragma once

#include "GameObjectUnit.h"

class UnitEnemy :
	public GameObjectUnit
{
public:
	UnitEnemy();
	UnitEnemy(SDL_Renderer * gRenderer);
	virtual ~UnitEnemy();

	bool loadMediaUnit(SDL_Renderer * gRenderer);

	void render(SDL_Renderer * gRenderer);

	void reset();

	float randomFloat(float a, float b);

private:


	//Coordinate
	float uPosX, uPosY;
	float uMidX, uMidY;
	float toX, toY;
	float offSetX, offSetY;

	//Dead Flag
	bool isDead;

	bool isSelected;

	//bool PathFound;

	//Loaded
	bool Loaded;
	bool LoadedDead;

	Config c;

	//Texture
	Texture unitTexture;

	//Unit's collision circle
	Circle mCollider;
};

