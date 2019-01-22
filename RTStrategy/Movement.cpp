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
}

bool Movement::getPath()
{
	return pathFound;
}

void Movement::setPath(bool b)
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

		for (Node node : Cordinate::aStar(player, destination)) {

			unit.pathNode.push_back(node);
			printf("Node X: %d Node Y: %d\n", node.x, node.y);

		}

		pathFound = true;
		stepTravel = 0;
	}

	if (stepTravel < unit.pathNode.size() && unit.pathNode.size() != 0)
	{
		//Not last Node
		if (stepTravel != unit.pathNode.size() - 1)
		{
			if (travel(unit.pathNode[stepTravel].x * c.getTileWidth() + c.getTileWidth() / 2, unit.pathNode[stepTravel].y * c.getTileHeight() + c.getTileHeight() / 2))
			{
				printf("Path node X Y : %i, %i\n", unit.pathNode[stepTravel].x, pathNode[stepTravel].y);
				toXUpdated = false;
				toYUpdated = false;
				stepTravel++;
			}
		}
		else
		{
			if (travel(unit.pathNode[stepTravel].x * c.getTileWidth(), unit.pathNode[stepTravel].y * c.getTileHeight()))
			{
				printf("Path last node X Y : %i, %i\n", unit.pathNode[stepTravel].x, unit.pathNode[stepTravel].y);
				toXUpdated = false;
				toYUpdated = false;
				unit.pathNode.clear();
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
			//printf("Befor Modif ToX : %f\n", toX);
			//float tmpx = toX - ((int)(toX / c.getTileWidth()) * c.getTileWidth());
			//int tmpx1 = (int)toX / c.getTileWidth();
			//float tmpx2 = tmpx1 * c.getTileWidth();
			//float tmpx3 = toX - tmpx1 * c.getTileWidth();
			printf("Path X : %f \nOffSetX : %f\n", x, unit.getUOffsetX());

			if (unit.getUPosToX != x + unit.getUOffsetX())
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
		unit.setUPosToX(unit.getUPosToX() + c.getVelUnit() * cos(tan) / 10);

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
			float tmpy = toY - ((toY / c.getTileHeight()) * c.getTileHeight());

			if (toY != y + unit.getUOffsetY())
			{
				toY = y + unit.getUOffsetY();
				printf("ToY : %f\nOffSetY : %f\n\n", toY, unit.getUOffsetY());
			}

			toYUpdated = true;
		}

		//if (toY != y)
		//{
		//	toY = y ;
		//	printf("ToY : %f\n\n", toY);
		//}

		float xAng = toX - unit.getUPosX() + unit.getUOffsetX();
		float yAng = toY - unit.getUPosY() + unit.getUOffsetY();
		float tan = atan2(yAng, xAng);

		//isMovingY = true;

		uPosY += c.getVelUnit() * sin(tan) / 10;

		if (fabs(unit.getUPosY() - toY - unit.getUOffsetY()) <= 0.5f)
		{
			unit.setUPosY(toY + unit.getUOffsetY());
		}
	}
	else
	{
		isMovingY = false;
	}

	unit.shiftColliders();

	bool b = false;
	if (unit.getUPosY() == toY + unit.getUOffsetY() && unit.getUPosX() == toX + unit.getUOffsetX())
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
			float randX = randomFloat(0, c.getScreenWidth());
			float randY = randomFloat(0, c.getScreenHeight());

			unit.setUPosToX(randX);
			unit.setUPosToY(randY);
		}

		if (uPosX != toX + unit.getUOffsetX())
		{
			isMovingX = true;
			//TODO
			float xAng = toX - uPosX + unit.getUOffsetX();
			float yAng = toY - uPosY + unit.getUOffsetY();
			float tan = atan2(yAng, xAng);

			uPosX += c.getVelUnit() * cos(tan) / 10;

			if (fabs(uPosX - toX + unit.getUOffsetX()) <= 0.5f)
			{
				uPosX = toX + unit.getUOffsetX();
			}
		}
		else
		{

			isMovingX = false;
			unit.setUPosToX(randomFloat(0, pathEnemyX));
			pathEnemyX = pathEnemyX / 2;
		}

		unit.shiftColliders();

		if (uPosY != toY + unit.getUOffsetY())
		{
			float xAng = toX - uPosX + unit.getUOffsetX();
			float yAng = toY - uPosY + unit.getUOffsetY();
			float tan = atan2(yAng, xAng);

			isMovingY = true;

			uPosY += c.getVelUnit() * sin(tan) / 10;

			if (fabs(uPosY - toY + unit.getUOffsetY()) <= 0.5f)
			{
				uPosY = toY + unit.getUOffsetY();

			}
		}
		else
		{
			isMovingY = false;
			unit.setUPosToY(randomFloat(0, pathEnemyY));
			pathEnemyY = pathEnemyY / 2;
		}

		unit.shiftColliders();
	}
}
