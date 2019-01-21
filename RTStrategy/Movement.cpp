#include "pch.h"
#include "Movement.h"


Movement::Movement()
{
	pathFound = false;
}


void Movement::move(float timeStep)
{
	if (!pathFound)
	{
		pathNode.clear();

		Node player;
		player.x = getUPosX() / X_STEP;
		player.y = getUPosY() / Y_STEP;

		Node destination;
		destination.x = toX / X_STEP;
		destination.y = toY / Y_STEP;

		printf("\n");

		for (Node node : Cordinate::aStar(player, destination)) {

			pathNode.push_back(node);
			printf("Node X: %d Node Y: %d\n", node.x, node.y);

		}

		pathFound = true;
		stepTravel = 0;
	}

	if (stepTravel < pathNode.size() && pathNode.size() != 0)
	{
		//Not last Node
		if (stepTravel != pathNode.size() - 1)
		{
			if (travel(pathNode[stepTravel].x * c.getTileWidth() + c.getTileWidth() / 2, pathNode[stepTravel].y * c.getTileHeight() + c.getTileHeight() / 2))
			{
				printf("Path node X Y : %i, %i\n", pathNode[stepTravel].x, pathNode[stepTravel].y);
				toXUpdated = false;
				toYUpdated = false;
				stepTravel++;
			}
		}
		else
		{
			if (travel(pathNode[stepTravel].x * c.getTileWidth(), pathNode[stepTravel].y * c.getTileHeight()))
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


bool Movement::travel(float x, float y)
{
	if (getUPosX() != x + getUOffsetX())
	{
		if (!toXUpdated)
		{
			//printf("Befor Modif ToX : %f\n", toX);
			//float tmpx = toX - ((int)(toX / c.getTileWidth()) * c.getTileWidth());
			//int tmpx1 = (int)toX / c.getTileWidth();
			//float tmpx2 = tmpx1 * c.getTileWidth();
			//float tmpx3 = toX - tmpx1 * c.getTileWidth();
			printf("Path X : %f \nOffSetX : %f\n", x, getUOffsetX());

			if (toX != x + getUOffsetX())
			{
				toX = x + getUOffsetX();
			}

			toXUpdated = true;
		}

		//if (toX != x)
		//{
		//	toX = x;
		//	printf("ToX : %f\n", toX);
		//}

		//isMovingX = true;

		float xAng = toX - getUPosX() + getUOffsetX();
		float yAng = toY - getUPosY() + getUOffsetY();
		float tan = atan2(yAng, xAng);

		//float gPx= getUPosX();
		//setUPosX(gPx + c.getVelUnit() * cos(tan) / 10);
		uPosX += c.getVelUnit() * cos(tan) / 10;

		if (fabs(getUPosX() - toX - getUOffsetX()) <= 0.5f)
		{
			setUPosX(toX + getUOffsetX());
		}

		//printf("Position X final : %f\n", uPosX);
	}
	else
	{
		isMovingX = false;
	}

	shiftColliders();

	if (uPosY != y + getUOffsetY())
	{
		if (!toYUpdated)
		{
			float tmpy = toY - ((toY / c.getTileHeight()) * c.getTileHeight());

			if (toY != y + getUOffsetY())
			{
				toY = y + getUOffsetY();
				printf("ToY : %f\nOffSetY : %f\n\n", toY, getUOffsetY());
			}

			toYUpdated = true;
		}

		//if (toY != y)
		//{
		//	toY = y ;
		//	printf("ToY : %f\n\n", toY);
		//}

		float xAng = toX - getUPosX() + getUOffsetX();
		float yAng = toY - getUPosY() + getUOffsetY();
		float tan = atan2(yAng, xAng);

		//isMovingY = true;

		uPosY += c.getVelUnit() * sin(tan) / 10;

		if (fabs(getUPosY() - toY - getUOffsetY()) <= 0.5f)
		{
			setUPosY(toY + getUOffsetY());
		}
	}
	else
	{
		isMovingY = false;
	}

	shiftColliders();

	bool b = false;
	if (getUPosY() == toY + getUOffsetY() && getUPosX() == toX + getUOffsetX())
	{
		b = true;
	}

	return b;
}


void Movement::moveEnemy(float timeStep)
{
	if (!isDead)
	{
		if (tilesA.isCollide(getCollider()))
		{
			float randX = randomFloat(0, c.getScreenWidth());
			float randY = randomFloat(0, c.getScreenHeight());

			setUPosToX(randX);
			setUPosToY(randY);
		}

		if (uPosX != toX + getUOffsetX())
		{
			isMovingX = true;
			//TODO
			float xAng = toX - uPosX + getUOffsetX();
			float yAng = toY - uPosY + getUOffsetY();
			float tan = atan2(yAng, xAng);

			uPosX += c.getVelUnit() * cos(tan) / 10;

			if (fabs(uPosX - toX + getUOffsetX()) <= 0.5f)
			{
				uPosX = toX + getUOffsetX();
			}
		}
		else
		{

			isMovingX = false;
			setUPosToX(randomFloat(0, pathEnemyX));
			pathEnemyX = pathEnemyX / 2;
		}

		shiftColliders();

		if (uPosY != toY + getUOffsetY())
		{
			float xAng = toX - uPosX + getUOffsetX();
			float yAng = toY - uPosY + getUOffsetY();
			float tan = atan2(yAng, xAng);

			isMovingY = true;

			uPosY += c.getVelUnit() * sin(tan) / 10;

			if (fabs(uPosY - toY + getUOffsetY()) <= 0.5f)
			{
				uPosY = toY + getUOffsetY();

			}
		}
		else
		{
			isMovingY = false;
			setUPosToY(randomFloat(0, pathEnemyY));
			pathEnemyY = pathEnemyY / 2;
		}

		shiftColliders();
	}
}
