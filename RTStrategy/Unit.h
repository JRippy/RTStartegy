#include "Config.h"
#include "Texture.h"
#include "TilesArray.h"
#include "CircleC.h"
#include "Cordinate.h"

#pragma once

class Unit
{
public:
	Unit();
	
	Unit(SDL_Renderer * gRenderer);

	Unit(SDL_Renderer * gRenderer, int enemy);


	std::vector<Node> pathNode;

	//Getter and setter
	float getUPosX();
	float getUPosY();

	void setUPosX(float f);
	void setUPosY(float f);

	float getUPosToX();
	float getUPosToY();

	void setUPosToX(float f);
	void setUPosToY(float f);

	float getUOffsetX();
	float getUOffsetY();

	void setUOffsetX(float f);
	void setUOffsetY(float f);
	
	//float getIsMoving();

	float getSelected();

	bool isUnitDead();

	//Gets collision circle
	Circle& getCollider();

	void shiftColliders();

	//Gets collision
	bool checkCollisionEnemy(Circle& a, int x, int y);

	double distanceSquared(int x1, int y1, int x2, int y2);

	//bool getPath();
	//void setPath(bool b);

	std::vector<Node> getVNode();

	void setSelected(bool b);

	bool isInSelection(SDL_Rect r);

	void attack(Unit& u);

	void kill(Unit & u);

	float randomFloat(float a, float b);

	bool loadMediaUnit(SDL_Renderer * gRenderer);

	bool loadMediaUnitEnemy(SDL_Renderer * gRenderer);

	//void move(float timeStep);
	//void moveEnemy(float timeStep);

	//bool travel(float x, float y);

	int getNodeX(int i);
	int getNodeY(int i);

	bool getPathFound();
	void setPathFound(bool b);

	void render(SDL_Renderer * gRenderer);
	void renderEnemy(SDL_Renderer * gRenderer);

	void reset();

	void resetEnemy();

private:

	//Coordinate
	float uPosX, uPosY;
	float uMidX, uMidY;
	float toX, toY;
	float offSetX, offSetY;
	//float pathEnemyX;
	//float pathEnemyY;

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
	Texture unitEnemyTexture;

	//Unit's collision circle
	Circle mCollider;

	TilesArray tilesA;

	bool isPathFound;

};

