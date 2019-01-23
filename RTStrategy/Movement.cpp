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

		Node player;
		player.x = unit.getUPosX() / X_STEP;
		player.y = unit.getUPosY() / Y_STEP;

		Node destination;
		destination.x = unit.getUPosToX() / X_STEP;
		destination.y = unit.getUPosToY() / Y_STEP;

		printf("\n");

		for (Node node : cordinate.aStar(player, destination)) {

			unit.pathNode.push_back(node);
			printf("Movement::Node X: %d Node Y: %d\n", node.x, node.y);

		}

		pathFound = true;
		stepTravel = 0;
	}

	if (stepTravel < unit.pathNode.size() && unit.pathNode.size() != 0)
	{
		int stepX = unit.getNodeX(stepTravel);
		int stepY = unit.getNodeY(stepTravel);

		//Not last Node
		if (stepTravel != unit.pathNode.size() - 1)
		{
			//if (travel(stepX2 * c.getTileWidth() + c.getTileWidth() / 2, unit.getNodeY(stepTravel) * c.getTileHeight() + c.getTileHeight() / 2))
			if (travel(unit, stepX * c.getTileWidth() + c.getTileWidth() / 2, unit.getNodeY(stepTravel) * c.getTileHeight() + c.getTileHeight() / 2))
			{
				printf("Movement::Path node X Y : %i, %i\n", unit.pathNode[stepTravel].x, unit.pathNode[stepTravel].y);
				toXUpdated = false;
				toYUpdated = false;
				stepTravel++;
			}
			else
			{
				printf("InPathStep but not Travel\n");
			}
		}
		else
		{
			if (travel(unit, stepX * c.getTileWidth(), stepY * c.getTileHeight()))
			{
				printf("Movement::Path last node X Y : %i, %i\n", unit.getNodeX(stepTravel), unit.getNodeY(stepTravel));
				toXUpdated = false;
				toYUpdated = false;
				unit.pathNode.clear();
				stepTravel++;
			}
			else
			{
				printf("Not in inPathStep and not Travel\n");
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
			//printf("Befor Modif ToX : %f\n", toX);
			//float tmpx = toX - ((int)(toX / c.getTileWidth()) * c.getTileWidth());
			//int tmpx1 = (int)toX / c.getTileWidth();
			//float tmpx2 = tmpx1 * c.getTileWidth();
			//float tmpx3 = toX - tmpx1 * c.getTileWidth();
			printf("Movement::Path X : %f \nOffSetX : %f\n", x, unit.getUOffsetX());

			if (unit.getUPosToX() != x + unit.getUOffsetX())
			{
				unit.setUPosToX(x + unit.getUOffsetX());
			}

			toXUpdated = true;
		}

		//if (toX != x)
		//{
		//	toX = x;
		//	printf("ToX : %f\n", toX);
		//}

		//isMovingX = true;

		float xAng = unit.getUPosToX() - unit.getUPosX() + unit.getUOffsetX();
		float yAng = unit.getUPosToY() - unit.getUPosY() + unit.getUOffsetY();
		float tan = atan2(yAng, xAng);

		//float gPx= getUPosX();
		//setUPosX(gPx + c.getVelUnit() * cos(tan) / 10);
		unit.setUPosX(unit.getUPosX() + c.getVelUnit() * cos(tan) / 10);

		if (fabs(unit.getUPosX() - unit.getUPosToX() - unit.getUOffsetX()) <= 0.5f)
		{
			unit.setUPosX(unit.getUPosToX() + unit.getUOffsetX());
		}

		//printf("Position X final : %f\n", uPosX);
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
			float tmpy = unit.getUPosToY() - ((unit.getUPosToY() / c.getTileHeight()) * c.getTileHeight());

			if (unit.getUPosToY() != y + unit.getUOffsetY())
			{
				unit.setUPosToY(y + unit.getUOffsetY());
				printf("Movement::ToY : %f\nOffSetY : %f\n\n", unit.getUPosToY(), unit.getUOffsetY());
			}

			toYUpdated = true;
		}

		//if (toY != y)
		//{
		//	toY = y ;
		//	printf("ToY : %f\n\n", toY);
		//}

		float xAng = unit.getUPosToX() - unit.getUPosX() + unit.getUOffsetX();
		float yAng = unit.getUPosToY() - unit.getUPosY() + unit.getUOffsetY();
		float tan = atan2(yAng, xAng);

		//isMovingY = true;

		unit.setUPosY(unit.getUPosY() + c.getVelUnit() * sin(tan) / 10);

		if (fabs(unit.getUPosY() - unit.getUPosToY() - unit.getUOffsetY()) <= 0.5f)
		{
			unit.setUPosY(unit.getUPosToY() + unit.getUOffsetY());
		}
	}
	else
	{
		isMovingY = false;
	}

	unit.shiftColliders();

	bool b = false;
	if (unit.getUPosY() == unit.getUPosToY() + unit.getUOffsetY() && unit.getUPosX() == unit.getUPosToX() + unit.getUOffsetX())
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

			unit.setUPosToX(randX);
			unit.setUPosToY(randY);
		}

		if (unit.getUPosX() != unit.getUPosToX() + unit.getUOffsetX())
		{
			isMovingX = true;
			//TODO
			float xAng = unit.getUPosToX() - unit.getUPosX() + unit.getUOffsetX();
			float yAng = unit.getUPosToY() - unit.getUPosY() + unit.getUOffsetY();
			float tan = atan2(yAng, xAng);

			unit.setUPosX(unit.getUPosX() + c.getVelUnit() * cos(tan) / 10);

			if (fabs(unit.getUPosX() - unit.getUPosToX() + unit.getUOffsetX()) <= 0.5f)
			{
				unit.setUPosX(unit.getUPosToX() + unit.getUOffsetX());
			}
		}
		else
		{

			isMovingX = false;
			unit.setUPosToX(unit.randomFloat(0, pathEnemyX));
			pathEnemyX = pathEnemyX / 2;
		}

		unit.shiftColliders();

		if (unit.getUPosY() != unit.getUPosToY() + unit.getUOffsetY())
		{
			float xAng = unit.getUPosToX() - unit.getUPosX() + unit.getUOffsetX();
			float yAng = unit.getUPosToY() - unit.getUPosY() + unit.getUOffsetY();
			float tan = atan2(yAng, xAng);

			isMovingY = true;

			unit.setUPosY(unit.getUPosY() + c.getVelUnit() * sin(tan) / 10);

			if (fabs(unit.getUPosY() - unit.getUPosToY() + unit.getUOffsetY()) <= 0.5f)
			{
				unit.setUPosY(unit.getUPosToY() + unit.getUOffsetY());

			}
		}
		else
		{
			isMovingY = false;
			unit.setUPosToY(unit.randomFloat(0, pathEnemyY));
			pathEnemyY = pathEnemyY / 2;
		}

		unit.shiftColliders();
	}
}
