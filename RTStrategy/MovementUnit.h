#pragma once
#include "Unit.h"
#include "UnitEnemy.h"

class MovementUnit
{
public:
	MovementUnit();

	std::vector<Node> pathNode;

	//bool getPath(Unit& unit);

	//void setPath(Unit& unit, bool b);

	Node getNode(int i);

	bool isPathFound(GameObjectUnit& unit);

	void isPathFound(GameObjectUnit& unit, bool b);

	void clearPath();

	void move(Unit& unit, float timeStep);

	void moveEnemy(UnitEnemy& unitE, float timeStep);

	bool travel(GameObjectUnit& unit, float x, float y);

	float randomFloat(float a, float b);

private:

	Config c;

	int stepTravel;

	float pathEnemyX;
	float pathEnemyY;

	bool toXUpdated, toYUpdated;

	TilesArray tilesA;

	Cordinate cordinate;
};

