#include "pch.h"
#include "GameObjectUnit.h"


GameObjectUnit::GameObjectUnit()
{
}

GameObjectUnit::GameObjectUnit(SDL_Renderer * gRenderer) :
	isSelected(false),
	isDead(false)
{
	//Set collision circle size
	mCollider.r = c.getUnitWidth() * 2;

	setUOffsetX(0);
	setUOffsetX(0);
	//printf("Display on : %f %f\n", uPosX, uPosY);

	//movement = Movement();

	//tilesA = TilesArray();

	//tilesA.load();

	//toXUpdated = false;
	//toYUpdated = false;
}

GameObjectUnit::~GameObjectUnit()
{
}
//
//GameObjectUnit::GameObjectUnit(SDL_Renderer * gRenderer, int enemy) :
//	isSelected(false),
//	isPathFound(false),
//	isDead(false)
//{
//	loadMediaUnitEnemy(gRenderer);
//	resetEnemy();
//
//	//Set collision circle size
//	mCollider.r = c.getUnitWidth() * 2;
//
//	//offSetX = randomFloat(-20, 20);
//	//offSetY = randomFloat(-20,20);
//	setUOffsetX(0);
//	setUOffsetX(0);
//	//printf("Display Enemy on : %f %f\n", uPosX, uPosY);
//}

float GameObjectUnit::getUPosX()
{
	return uPosX;
}

float GameObjectUnit::getUPosY()
{
	return uPosY;
}

void GameObjectUnit::setUPosX(float f)
{

	if (uPosX >= c.getScreenWidth() - c.getUnitWidth())
	{
		uPosX = c.getScreenWidth() - c.getUnitWidth();
	}
	else {
		uPosX = f;
	}
}

void GameObjectUnit::setUPosY(float f)
{
	if (uPosY >= c.getScreenWidth() - c.getUnitWidth())
	{
		uPosY = c.getScreenWidth() - c.getUnitWidth();
	}
	else {
		uPosY = f;
	}
}

float GameObjectUnit::getUDestinationX()
{
	return toX;
}

float GameObjectUnit::getUDestinationY()
{
	return toY;
}

void GameObjectUnit::setUDestinationX(float f)
{
	if (toX > c.getScreenWidth() - c.getUnitWidth())
	{
		toX = c.getScreenWidth() - c.getUnitWidth();
	}
	else {
		toX = f;
	}
}

void GameObjectUnit::setUDestinationY(float f)
{
	if (toY > c.getScreenHeight() - c.getUnitHeight())
	{
		toY = c.getScreenHeight() - c.getUnitHeight();
	}
	else {
		toY = f;
	}
}

float GameObjectUnit::getUOffsetX()
{
	return offSetX;
}

float GameObjectUnit::getUOffsetY()
{
	return offSetY;
}

void GameObjectUnit::setUOffsetX(float f)
{
	offSetX = f;
}

void GameObjectUnit::setUOffsetY(float f)
{
	offSetY = f;
}

float GameObjectUnit::getSelected()
{
	return isSelected;
}

bool GameObjectUnit::isUnitDead()
{
	return isDead;
}

void GameObjectUnit::setUnitDead(bool b)
{
	isDead = b;;
}

bool GameObjectUnit::getIsMoving()
{
	return false;
}

void GameObjectUnit::setIsMoving(bool b)
{
	isMoving = b;
}

bool GameObjectUnit::isPathFound()
{
	return PathFound;
}

void GameObjectUnit::isPathFound(bool b)
{
	PathFound = b;
}

Circle & GameObjectUnit::getCollider()
{
	return mCollider;
}

void GameObjectUnit::shiftColliders()
{
	//Align collider to center of Unit
	mCollider.x = (int)getUPosX() + getUOffsetX() + (c.getUnitWidth() / 2);
	mCollider.y = (int)getUPosY() + getUOffsetY() + (c.getUnitHeight() / 2);

	uMidX = (int)getUPosX() + getUOffsetX() + (c.getUnitWidth() / 2);
	uMidY = (int)getUPosY() + getUOffsetY() + (c.getUnitHeight() / 2);
}

double GameObjectUnit::distanceSquared(int x1, int y1, int x2, int y2)
{
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	return deltaX * deltaX + deltaY * deltaY;
}

void GameObjectUnit::setSelected(bool b)
{
	isSelected = b;
}

bool GameObjectUnit::isInSelection(SDL_Rect r)
{
	bool b = false;

	if (r.x <= getUPosX() + c.getUnitWidth() / 2 && r.x + r.w >= getUPosX() + c.getUnitWidth() / 2)
	{
		if (r.y <= getUPosY() + c.getUnitHeight() / 2 && r.y + r.h >= getUPosY() + c.getUnitHeight() / 2)
		{
			b = true;
		}
	}

	//// Compare radius of circle with distance of its center from given point 
	if ((r.x - getUPosX() + c.getUnitWidth() / 2) * (r.x - getUPosX() + c.getUnitWidth() / 2) +
		(r.y - getUPosY() + c.getUnitHeight() / 2) * (r.y - getUPosY() + c.getUnitHeight() / 2) <= (c.getUnitWidth() / 2) * (c.getUnitWidth() / 2))
		b = true;

	return b;
}

//float GameObjectUnit::randomFloat(float a, float b)
//{
//	float random = ((float)rand()) / (float)RAND_MAX;
//	float diff = b - a;
//	float r = random * diff;
//	return a + r;
//}