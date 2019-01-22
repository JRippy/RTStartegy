#pragma once
#include "Unit.h"

class Movement
{
public:
	Movement();

	bool getPath();

	void setPath(bool b);

	float getIsMoving();

	void move(Unit& unit, float timeStep);

	bool travel(Unit& unit, float x, float y);

	void moveEnemy(Unit& unit, float timeStep);

private:

	Config c;

	bool pathFound;

	bool isMovingX;
	bool isMovingY;

	int stepTravel;

	float pathEnemyX;
	float pathEnemyY;

	bool toXUpdated, toYUpdated;
};
