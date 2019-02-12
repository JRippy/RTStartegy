#pragma once
#include <SDL.h>
#include "Config.h"
#include "Texture.h"
#include "TilesArray.h"
#include "CircleC.h"
#include "Cordinate.h"
//#include "Vector2.h"

class GameObjectUnit
{
public:
	GameObjectUnit();
	GameObjectUnit(SDL_Renderer * gRenderer);
	virtual ~GameObjectUnit();

	std::vector<Node> getVNode();

	//Getter and setter
	float getUPosX();
	float getUPosY();

	void setUPosX(float f);
	void setUPosY(float f);

	float getUDestinationX();
	float getUDestinationY();

	void setUDestinationX(float f);
	void setUDestinationY(float f);

	float getUOffsetX();
	float getUOffsetY();

	void setUOffsetX(float f);
	void setUOffsetY(float f);

	//float getIsMoving();

	float getSelected();

	bool isUnitDead();

	void setUnitDead(bool b);

	bool getIsMoving();

	void setIsMoving(bool b);

	bool isPathFound();

	void isPathFound(bool b);

	//Gets collision circle
	Circle& getCollider();

	void shiftColliders();

	double distanceSquared(int x1, int y1, int x2, int y2);

	void setSelected(bool b);

	bool isInSelection(SDL_Rect r);

	//void attack(GameObjectUnit& u);

	//void kill(GameObjectUnit& u);

	//float randomFloat(float a, float b);

	//virtual void update(float dt) = 0;
	//virtual void draw(SDL_Renderer& renderer_) = 0;

	virtual bool loadMediaUnit(SDL_Renderer * gRenderer) = 0;

	virtual void render(SDL_Renderer * gRenderer) = 0;

	virtual void reset() = 0;

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

	bool PathFound;

	bool isMoving;

};

