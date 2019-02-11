#include "pch.h"
#include "MovementUnit.h"


MovementUnit::MovementUnit()
{
}

//
//bool MovementUnit::getPath(Unit & unit)
//{
//	return false;
//}
//
//void MovementUnit::setPath(Unit & unit, bool b)
//{
//}

Node MovementUnit::getNode(int i)
{
	return pathNode[i];
}

bool MovementUnit::isPathFound(GameObjectUnit & unit)
{
	return unit.isPathFound();
}

void MovementUnit::isPathFound(GameObjectUnit & unit, bool b)
{
	unit.isPathFound(b);
}

void MovementUnit::clearPath()
{
	pathNode.clear();
}

void MovementUnit::move(Unit & unit, float timeStep)
{
	if (!unit.isPathFound())
	{
		pathNode.clear();

		Node player;
		player.x = unit.getUPosX() / X_STEP;
		player.y = unit.getUPosY() / Y_STEP;

		Node destination;
		destination.x = unit.getUPosToX() / X_STEP;
		destination.y = unit.getUPosToY() / Y_STEP;

		printf("\n");

		for (Node node : Cordinate::aStar(player, destination)) {

			pathNode.push_back(node);
			printf("Node X: %d Node Y: %d\n", node.x, node.y);

		}

		unit.isPathFound(true);
		stepTravel = 0;
	}

	if (stepTravel < pathNode.size() && pathNode.size() != 0)
	{
		//Not last Node
		if (stepTravel != pathNode.size() - 1)
		{
			if (travel(unit, pathNode[stepTravel].x * c.getTileWidth() + c.getTileWidth() / 2, pathNode[stepTravel].y * c.getTileHeight() + c.getTileHeight() / 2))
			{
				printf("Path node X Y : %i, %i\n", pathNode[stepTravel].x, pathNode[stepTravel].y);
				toXUpdated = false;
				toYUpdated = false;
				stepTravel++;
			}
		}
		else
		{
			if (travel(unit, pathNode[stepTravel].x * c.getTileWidth(), pathNode[stepTravel].y * c.getTileHeight()))
			{
				printf("Path last node X Y : %i, %i\n", pathNode[stepTravel].x, pathNode[stepTravel].y);
				toXUpdated = false;
				toYUpdated = false;
				pathNode.clear();
				stepTravel++;
			}
		}

	}
}

void MovementUnit::moveEnemy(UnitEnemy& unitE, float timeStep)
{
	if (unitE.isUnitDead() != false)
	{
				if (tilesA.isCollide(unitE.getCollider()))
				{
					float randX = randomFloat(0, c.getScreenWidth());
					float randY = randomFloat(0, c.getScreenHeight());
		
					unitE.setUPosToX(randX);
					unitE.setUPosToY(randY);
				}
		
				if (unitE.getUPosX() != unitE.getUPosToX() + unitE.getUOffsetX())
				{
					unitE.setUnitDead(true);
					//TODO
					float xAng = unitE.getUPosToX() - unitE.getUPosX() + unitE.getUOffsetX();
					float yAng = unitE.getUPosToY() - unitE.getUPosY() + unitE.getUOffsetY();
					float tan = atan2(yAng, xAng);
		
					unitE.setUPosX(unitE.getUPosX() + c.getVelUnit() * cos(tan) / 10);
		
					if (fabs(unitE.getUPosX() - unitE.getUPosToX() + unitE.getUOffsetX()) <= 0.5f)
					{
						unitE.setUPosX(unitE.getUPosToX() + unitE.getUOffsetX());
					}
				}
				else
				{
		
					unitE.setIsMoving(false);
					unitE.setUPosToX(randomFloat(0, pathEnemyX));
					pathEnemyX = pathEnemyX / 2;
				}
		
				unitE.shiftColliders();
		
				if (unitE.getUPosY() != unitE.getUPosToY() + unitE.getUOffsetY())
				{
					float xAng = unitE.getUPosToX() - unitE.getUPosX() + unitE.getUOffsetX();
					float yAng = unitE.getUPosToY() - unitE.getUPosY() + unitE.getUOffsetY();
					float tan = atan2(yAng, xAng);
		
					unitE.setUnitDead(true);
		
					unitE.setUPosY(unitE.getUPosY() + c.getVelUnit() * sin(tan) / 10);
		
					if (fabs(unitE.getUPosY()- unitE.getUPosToY() + unitE.getUOffsetY()) <= 0.5f)
					{
						unitE.setUPosY( unitE.getUPosToY() + unitE.getUOffsetY());
		
					}
				}
				else
				{
					unitE.setIsMoving(false);
					unitE.setUPosToY(randomFloat(0, pathEnemyY));
					pathEnemyY = pathEnemyY / 2;
				}
		
				unitE.shiftColliders();
	}
}

bool MovementUnit::travel(GameObjectUnit & unit, float x, float y)
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

			if (unit.getUPosToX() != x + unit.getUOffsetX())
			{
				unit.setUPosToX(x + unit.getUOffsetX());
			}

			toXUpdated = true;
		}

		float xAng = unit.getUPosToX() - unit.getUPosX() + unit.getUOffsetX();
		float yAng = unit.getUPosToY() - unit.getUPosY() + unit.getUOffsetY();
		float tan = atan2(yAng, xAng);

		//float gPx= getUPosX();
		//setUPosX(gPx + c.getVelUnit() * cos(tan) / 10);
		unit.setUPosX(unit.getUPosX() + c.getVelUnit() * cos(tan) / 10);

		if (fabs(unit.getUPosX() - unit.getUPosToX() - unit.getUOffsetX()) <= 0.5f)
		{
			unit.setUPosX(unit.getUPosX() + unit.getUOffsetX());
		}

		//printf("Position X final : %f\n", uPosX);
	}
	else
	{
		unit.setIsMoving(false);
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
				printf("ToY : %f\nOffSetY : %f\n\n", unit.getUPosToY(), unit.getUOffsetY());
			}

			toYUpdated = true;
		}

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
		unit.setIsMoving(false);
	}

	unit.shiftColliders();

	bool b = false;
	if (unit.getUPosY() == unit.getUPosToY() + unit.getUOffsetY() && unit.getUPosX() == unit.getUPosToX() + unit.getUOffsetX())
	{
		b = true;
	}

	return b;
}

float MovementUnit::randomFloat(float a, float b)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}