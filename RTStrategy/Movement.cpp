#include "pch.h"
#include "Movement.h"


Movement::Movement() :
	isMovingX(false),
	isMovingY(false),
	stepTravel(0),
	pathFound(false),
	toXUpdated(false),
	toYUpdated(false)
{
	pathEnemyX = c.getScreenWidth();
	pathEnemyY = c.getScreenHeight();

	tilesA = TilesArray();

	tilesA.load();
}

bool Movement::getPath(Unit& unit)
{
	return pathFound;
}

void Movement::setPath(Unit& unit, bool b)
{
	pathFound = b;
}

float Movement::getIsMoving()
{
	return isMovingX && isMovingY;
}

void Movement::move(Unit& unit, float timeStep)
{
	if (!pathFound)
	{
		unit.pathNode.clear();
		unit.clearPath();

		Node player;
		player.x = unit.getUPosX() / X_STEP;
		player.y = unit.getUPosY() / Y_STEP;

		Node destination;
		destination.x = unit.getUDestinationX() / X_STEP;
		destination.y = unit.getUDestinationY() / Y_STEP;

		printf("\n");

		for (Node node : cordinate.aStar(player, destination)) {

			unit.pathNode.push_back(node);
			printf("Movement::Node X: %d Node Y: %d\n", node.x, node.y);

		}

		pathFound = true;
		stepTravel = 0;
	}

	if (stepTravel < unit.pathNode.size() && unit.pathNode.size() > 0)
	{
		int stepX = unit.getNodeX(stepTravel);
		int stepY = unit.getNodeY(stepTravel);

		//Not last Node
		if (stepTravel <= unit.pathNode.size() - 1)
		{
			//if (travel(stepX2 * c.getTileWidth() + c.getTileWidth() / 2, unit.getNodeY(stepTravel) * c.getTileHeight() + c.getTileHeight() / 2))
			if (travel(unit, stepX * c.getTileWidth() + c.getTileWidth() / 2, stepY * c.getTileHeight() + c.getTileHeight() / 2))
			{
				printf("Movement::Path node X Y : %i, %i\n", unit.pathNode[stepTravel].x, unit.pathNode[stepTravel].y);
				toXUpdated = false;
				toYUpdated = false;
				stepTravel++;
			}
		}
		else
		{
			if (travel(unit, stepX * c.getTileWidth(), stepY * c.getTileHeight()))
			{
				printf("Movement::Path last node X Y : %i, %i\n", unit.getNodeX(stepTravel), unit.getNodeY(stepTravel));
				toXUpdated = false;
				toYUpdated = false;
				unit.clearPath();
				stepTravel++;
			}
		}

	}

}


bool Movement::travel(Unit& unit, float x, float y)
{
	if (unit.getUPosX() != x + unit.getUOffsetX())
	{
		if (!toXUpdated)
		{
			//printf("Movement::Path X : %f \nOffSetX : %f\n", x, unit.getUOffsetX());

			if (unit.getUDestinationX() != x + unit.getUOffsetX())
			{
				unit.setUDestinationX(x + unit.getUOffsetX());
			}

			toXUpdated = true;
		}

		float xAng = unit.getUDestinationX() - unit.getUPosX() + unit.getUOffsetX();
		float yAng = unit.getUDestinationY() - unit.getUPosY() + unit.getUOffsetY();
		float tan = atan2(yAng, xAng);

		//float gPx= getUPosX();
		//setUPosX(gPx + c.getVelUnit() * cos(tan) / 10);
		unit.setUPosX(unit.getUPosX() + c.getVelUnit() * cos(tan) / 10);

		if (fabs(unit.getUPosX() - unit.getUDestinationX() - unit.getUOffsetX()) <= 0.5f)
		{
			unit.setUPosX(unit.getUDestinationX() + unit.getUOffsetX());
		}
	}
	else
	{
		isMovingX = false;
	}

	unit.shiftColliders();

	if (unit.getUPosY() != y + unit.getUOffsetY())
	{
		if (!toYUpdated)
		{
			float tmpy = unit.getUDestinationY() - ((unit.getUDestinationY() / c.getTileHeight()) * c.getTileHeight());

			if (unit.getUDestinationY() != y + unit.getUOffsetY())
			{
				unit.setUDestinationY(y + unit.getUOffsetY());
				//printf("Movement::ToY : %f\nOffSetY : %f\n\n", unit.getUPosToY(), unit.getUOffsetY());
			}

			toYUpdated = true;
		}

		float xAng = unit.getUDestinationX() - unit.getUPosX() + unit.getUOffsetX();
		float yAng = unit.getUDestinationY() - unit.getUPosY() + unit.getUOffsetY();
		float tan = atan2(yAng, xAng);

		unit.setUPosY(unit.getUPosY() + c.getVelUnit() * sin(tan) / 10);

		if (fabs(unit.getUPosY() - unit.getUDestinationY() - unit.getUOffsetY()) <= 0.5f)
		{
			unit.setUPosY(unit.getUDestinationY() + unit.getUOffsetY());
		}
	}
	else
	{
		isMovingY = false;
	}

	unit.shiftColliders();

	bool b = false;
	if (unit.getUPosY() == unit.getUDestinationY() + unit.getUOffsetY() && unit.getUPosX() == unit.getUDestinationX() + unit.getUOffsetX())
	{
		b = true;
	}

	return b;
}


void Movement::moveEnemy(Unit& unit, float timeStep)
{
	if (!unit.isUnitDead())
	{
		if (tilesA.isCollide(unit.getCollider()))
		{
			float randX = unit.randomFloat(0, c.getScreenWidth());
			float randY = unit.randomFloat(0, c.getScreenHeight());

			unit.setUDestinationX(randX);
			unit.setUDestinationY(randY);
		}

		if (unit.getUPosX() != unit.getUDestinationX() + unit.getUOffsetX())
		{
			isMovingX = true;
			//TODO
			float xAng = unit.getUDestinationX() - unit.getUPosX() + unit.getUOffsetX();
			float yAng = unit.getUDestinationY() - unit.getUPosY() + unit.getUOffsetY();
			float tan = atan2(yAng, xAng);

			unit.setUPosX(unit.getUPosX() + c.getVelUnit() * cos(tan) / 10);

			if (fabs(unit.getUPosX() - unit.getUDestinationX() + unit.getUOffsetX()) <= 0.5f)
			{
				unit.setUPosX(unit.getUDestinationX() + unit.getUOffsetX());
			}
		}
		else
		{

			isMovingX = false;
			unit.setUDestinationX(unit.randomFloat(0, pathEnemyX));
			pathEnemyX = pathEnemyX / 2;
		}

		unit.shiftColliders();

		if (unit.getUPosY() != unit.getUDestinationY() + unit.getUOffsetY())
		{
			float xAng = unit.getUDestinationX() - unit.getUPosX() + unit.getUOffsetX();
			float yAng = unit.getUDestinationY() - unit.getUPosY() + unit.getUOffsetY();
			float tan = atan2(yAng, xAng);

			isMovingY = true;

			unit.setUPosY(unit.getUPosY() + c.getVelUnit() * sin(tan) / 10);

			if (fabs(unit.getUPosY() - unit.getUDestinationY() + unit.getUOffsetY()) <= 0.5f)
			{
				unit.setUPosY(unit.getUDestinationY() + unit.getUOffsetY());

			}
		}
		else
		{
			isMovingY = false;
			unit.setUDestinationY(unit.randomFloat(0, pathEnemyY));
			pathEnemyY = pathEnemyY / 2;
		}

		unit.shiftColliders();
	}
}
