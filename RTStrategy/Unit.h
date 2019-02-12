#pragma once

#include "GameObjectUnit.h"
#include "Config.h"
#include "Texture.h"
#include "TilesArray.h"
#include "CircleC.h"
#include "Cordinate.h"

class Unit :
	public GameObjectUnit
{
public:
	Unit();
	
	Unit(SDL_Renderer * gRenderer);

	std::vector<Node> pathNode;

	float getSelected();

	bool isUnitDead();

	//Gets collision circle
	Circle& getCollider();

	void shiftColliders();

	//Gets collision
	bool checkCollisionEnemy(Circle& a, int x, int y);

	double distanceSquared(int x1, int y1, int x2, int y2);

	void setSelected(bool b);

	bool isInSelection(SDL_Rect r);

	void attack(GameObjectUnit & u);

	void kill(GameObjectUnit & u);

	float randomFloat(float a, float b);

	bool loadMediaUnit(SDL_Renderer * gRenderer);

	int getNodeX(int i);
	int getNodeY(int i);

	void clearPath();

	void render(SDL_Renderer * gRenderer);

	void reset();

private:

	//Coordinate
	float uPosX, uPosY;
	float uMidX, uMidY;
	float toX, toY;
	float offSetX, offSetY;

	//Dead Flag
	bool isDead;

	bool isSelected;

	//Loaded
	bool Loaded;
	bool LoadedEnemy;
	bool LoadedDead;

	Config c;

	//Texture
	Texture unitTexture;

	//Unit's collision circle
	Circle mCollider;

	TilesArray tilesA;

	//bool PathFound;

};

