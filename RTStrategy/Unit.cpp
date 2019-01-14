#include "pch.h"
#include "Unit.h"
#include <cstdlib>

Unit::Unit()
{
}


Unit::Unit(SDL_Renderer * gRenderer) :
	isSelected(false),
	isMovingX(false),
	isMovingY(false),
	isDead(false)
{
	loadMediaUnit(gRenderer);
	reset();

	//Set collision circle size
	mCollider.r = c.getUnitWidth() * 2;

	//offSetX = randomFloat(-20, 20);
	//offSetY = randomFloat(-20,20);

	offSetX = 0;
	offSetY = 0;
	pathEnemyX = c.getScreenWidth();
	pathEnemyY = c.getScreenHeight();
	//printf("Display on : %f %f\n", uPosX, uPosY);


	tilesA = TilesArray();

	tilesA.load();

	pathfound = false;
	toXUpdated = false;
	toYUpdated = false;
	stepTravel = 0;
}

Unit::Unit(SDL_Renderer * gRenderer, int enemy) :
	isSelected(false),
	isMovingX(false),
	isMovingY(false),
	isDead(false)
{
	loadMediaUnitEnemy(gRenderer);
	resetEnemy();

	//Set collision circle size
	mCollider.r = c.getUnitWidth() * 2;

	//offSetX = randomFloat(-20, 20);
	//offSetY = randomFloat(-20,20);
	offSetX = 0;
	offSetY = 0;
	pathEnemyX = c.getScreenWidth();
	pathEnemyY = c.getScreenHeight();
	//printf("Display Enemy on : %f %f\n", uPosX, uPosY);


	tilesA = TilesArray();

	tilesA.load();

	pathfound = false;
	toXUpdated = false;
	toYUpdated = false;
	stepTravel = 0;
}

float Unit::getUPosX()
{
	return uPosX;
}

float Unit::getUPosY()
{
	return uPosY;
}

void Unit::setUPosX(float f)
{

	if (uPosX >= c.getScreenWidth() - c.getUnitWidth())
	{
		uPosX = c.getScreenWidth() - c.getUnitWidth();
	}
	else {
		uPosX = f;
	}
}

void Unit::setUPosY(float f)
{
	if (uPosY >= c.getScreenWidth() - c.getUnitWidth())
	{
		uPosY = c.getScreenWidth() - c.getUnitWidth();
	}
	else {
		uPosY = f;
	}
}

float Unit::getUPosToX()
{
	return toX;
}

float Unit::getUPosToY()
{
	return toY;
}

void Unit::setUPosToX(float f)
{
	if (toX > c.getScreenWidth() - c.getUnitWidth())
	{
		toX = c.getScreenWidth() - c.getUnitWidth();
	}
	else {
		toX = f;
	}
}

void Unit::setUPosToY(float f)
{
	if (toY > c.getScreenHeight() - c.getUnitHeight())
	{
		toY = c.getScreenHeight() - c.getUnitHeight();
	}
	else {
		toY = f;
	}
}

float Unit::getIsMoving()
{
	return isMovingX && isMovingY;
}

float Unit::getSelected()
{
	return isSelected;
}

bool Unit::isUnitDead()
{
	return isDead;
}

Circle & Unit::getCollider()
{
	return mCollider;
}

void Unit::shiftColliders()
{
	//Align collider to center of Unit
	mCollider.x = (int)uPosX + (c.getUnitWidth() / 2);
	mCollider.y = (int)uPosY + (c.getUnitHeight() / 2);

	uMidX = (int)uPosX + (c.getUnitWidth() / 2);
	uMidY = (int)uPosY + (c.getUnitHeight() / 2);
}

bool Unit::checkCollisionEnemy(Circle & a, int x, int y)
{
	//Closest point on collision box
	int cX, cY;

	//Find closest x offset
	if (a.x < x)
	{
		cX = x;
	}
	else
	{
		cX = a.x;
	}

	//Find closest y offset
	if (a.y < y)
	{
		cY = y;
	}
	else
	{
		cY = a.y;
	}

	//If the closest point is inside the circle
	if (distanceSquared(a.x, a.y, cX, cY) <= a.r * a.r)
	{
		//This box and the circle have collided
		return true;
	}

	//If the shapes have not collided
	return false;
}

double Unit::distanceSquared(int x1, int y1, int x2, int y2)
{
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	return deltaX * deltaX + deltaY * deltaY;
}

bool Unit::getPath()
{
	return pathfound;
}

void Unit::setPath(bool b)
{
	pathfound = b;
}

void Unit::setSelected(bool b)
{
	isSelected = b;
}

bool Unit::isInSelection(SDL_Rect r)
{
	bool b = false;

	if (r.x <= uPosX + c.getUnitWidth() / 2 && r.x + r.w >= uPosX + c.getUnitWidth() / 2)
	{
		if (r.y <= uPosY + c.getUnitHeight() / 2 && r.y + r.h >= uPosY + c.getUnitHeight() / 2)
		{
			b = true;
		}
	}

	//// Compare radius of circle with distance of its center from given point 
	if ((r.x - uPosX + c.getUnitWidth() / 2) * (r.x - uPosX + c.getUnitWidth() / 2) +
		(r.y - uPosY + c.getUnitHeight() / 2) * (r.y - uPosY + c.getUnitHeight() / 2) <= (c.getUnitWidth() / 2) * (c.getUnitWidth() / 2))
		b = true;

	return b;
}

void Unit::attack(Unit& u)
{
	setUPosToX(u.getUPosX());
	setUPosToY(u.getUPosY());

	//Closest point on collision box
	int cX, cY;
	float uEX = u.getUPosX();
	float uEY = u.getUPosY();

	//Find closest x offset
	if (uMidX < uEX)
	{
		cX = uEX;
	}
	else
	{
		cX = uMidX;
	}

	//Find closest y offset
	if (uMidY < uEY)
	{
		cY = uEY;
	}
	else
	{
		cY = uMidY;
	}

	if (distanceSquared(getUPosX(), getUPosY(), cX, cY) <= c.getUnitHeight() * c.getUnitWidth())
	{
		kill(u);
	}
}

void Unit::kill(Unit& u)
{
	if (!u.isDead)
	{
		u.isDead = true;
	}
}

float Unit::randomFloat(float a, float b)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

bool Unit::loadMediaUnit(SDL_Renderer * gRenderer)
{
	//Loading success flag
	Loaded = true;

	//Load Car texture
	if (!unitTexture.loadFromFile("dot.bmp", gRenderer))
	{
		printf("Failed to load dot texture!\n");
		Loaded = false;
	}

	return Loaded;
}

bool Unit::loadMediaUnitEnemy(SDL_Renderer * gRenderer)
{
	//Loading success flag
	LoadedEnemy = true;

	//Load Car texture
	if (!unitEnemyTexture.loadFromFile("dot_Enemy.bmp", gRenderer))
	{
		printf("Failed to load dot enemy texture!\n");
		LoadedEnemy = false;
	}

	return LoadedEnemy;
}

void Unit::move(float timeStep)
{
	if (!pathfound)
	{
		Node player;
		player.x = uPosX / X_STEP;
		player.y = uPosY / Y_STEP;

		Node destination;
		destination.x = toX / X_STEP;
		destination.y = toY / Y_STEP;

		for (Node node : Cordinate::aStar(player, destination)) {

			pathNode.push_back(node);
			printf("Node X: %d Node Y: %d\n", node.x, node.y);

		}

		pathfound = true;
		stepTravel = 0;
	}

	if (stepTravel < pathNode.size() && travel(pathNode[stepTravel].x * c.getTileWidth() + c.getTileWidth() / 2, pathNode[stepTravel].y * c.getTileHeight() + c.getTileHeight() / 2))
	{
		printf("Path node X Y : %i, %i\n", pathNode[stepTravel].x, pathNode[stepTravel].y);
		toXUpdated = false;
		toYUpdated = false;
		stepTravel++;
	}

}


bool Unit::travel(float x, float y)
{
	if (uPosX != x + offSetX)
	{
		if (!toXUpdated)
		{
			printf("Befor Modif ToX : %f\n", toX);
			float tmpx = toX - ((toX / c.getTileWidth()) * c.getTileWidth());
			float tmpx1 = toX / c.getTileWidth();
			float tmpx2 = tmpx1 * c.getTileWidth();
			float tmpx3 = toX - tmpx1 * c.getTileWidth();

			if (toX != x + tmpx)
			{
				toX = x + tmpx;
				printf("ToX : %f and TMP : %f and TMP2 : %f and TMP3 : %f\n", toX, tmpx, tmpx2, tmpx3);
			}

			toXUpdated = true;
		}

		//if (toX != x)
		//{
		//	toX = x;
		//	printf("ToX : %f\n", toX);
		//}

		//isMovingX = true;

		float xAng = toX - uPosX + offSetX;
		float yAng = toY - uPosY + offSetY;
		float tan = atan2(yAng, xAng);

		uPosX += c.getVelUnit() * cos(tan) / 10;

		if (fabs(uPosX - toX + offSetX) <= 0.5f)
		{
			uPosX = toX + offSetX;
		}

		//printf("Position X final : %f\n", uPosX);
	}
	else
	{
		isMovingX = false;
	}

	shiftColliders();

	if (uPosY != y + offSetY)
	{
		if (!toYUpdated)
		{
			float tmpy = toY - ((toY / c.getTileHeight()) * c.getTileHeight());

			if (toY != y + tmpy)
			{
				toY = y + tmpy;
				printf("ToY : %f; Tmp : %f\n\n", toY, tmpy);
			}

			toYUpdated = true;
		}



		//if (toY != y)
		//{
		//	toY = y ;
		//	printf("ToY : %f\n\n", toY);
		//}

		float xAng = toX - uPosX + offSetX;
		float yAng = toY - uPosY + offSetY;
		float tan = atan2(yAng, xAng);

		//isMovingY = true;
		
		uPosY += c.getVelUnit() * sin(tan) / 10;

		if (fabs(uPosY - toY + offSetY) <= 0.5f)
		{
			uPosY = toY + offSetY;
		}

		//printf("Position Y final : %f\n\n", uPosY);
	}
	else
	{
		isMovingY = false;
	}

	shiftColliders();

	bool b = false;
	if (uPosY == toY + offSetY && uPosX == toX + offSetX)
	{
		b = true;
	}

	return b;
}


void Unit::moveEnemy(float timeStep)
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

		if (uPosX != toX + offSetX)
		{
			isMovingX = true;
			//TODO
			float xAng = toX - uPosX + offSetX;
			float yAng = toY - uPosY + offSetY;
			float tan = atan2(yAng, xAng);

			uPosX += c.getVelUnit() * cos(tan) / 10;

			if (fabs(uPosX - toX + offSetX) <= 0.5f)
			{
				uPosX = toX + offSetX;
			}
		}
		else
		{

			isMovingX = false;
			setUPosToX(randomFloat(0, pathEnemyX));
			pathEnemyX = pathEnemyX / 2;
		}

		shiftColliders();

		if (uPosY != toY + offSetY)
		{
			float xAng = toX - uPosX + offSetX;
			float yAng = toY - uPosY + offSetY;
			float tan = atan2(yAng, xAng);

			isMovingY = true;

			uPosY += c.getVelUnit() * sin(tan) / 10;

			if (fabs(uPosY - toY + offSetY) <= 0.5f)
			{
				uPosY = toY + offSetY;

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

void Unit::render(SDL_Renderer* gRenderer)
{
	if (!Loaded || !unitTexture.loadFromFile("dot.bmp", gRenderer))
	{
		printf("Failed to load dot texture!\n");
	}

	if (getSelected() == true)
	{
		SDL_Rect lasso;

		lasso.x = uPosX - 1;
		lasso.y = uPosY - 1;
		lasso.w = c.getUnitWidth() + 2;
		lasso.h = c.getUnitHeight() + 2;

		//printf("Lasso : %f, %f, %f, %f\n", xStart, yStart, xEnd, yEnd);

		//Render rext
		SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
		SDL_RenderDrawRect(gRenderer, &lasso);
	}

	unitTexture.render((int)uPosX, (int)uPosY, gRenderer);

}

void Unit::renderEnemy(SDL_Renderer* gRenderer)
{

	if (!isDead)
	{

		if (!LoadedEnemy || !unitEnemyTexture.loadFromFile("dot_Enemy.bmp", gRenderer))
		{
			printf("Failed to load dot enemy texture!\n");
		}
	}
	else
	{
		//LoadedDead = true;

		//if (!LoadedDead || !unitEnemyTexture.loadFromFile("dot_Dead.bmp", gRenderer) )
		if (!unitEnemyTexture.loadFromFile("dot_Dead.bmp", gRenderer) )
		{
			printf("Failed to load dot dead enemy texture!\n");
			//LoadedDead = false;
		}
	}

	if (getSelected() == true)
	{
		SDL_Rect lasso;

		lasso.x = uPosX - 1;
		lasso.y = uPosY - 1;
		lasso.w = c.getUnitWidth() + 2;
		lasso.h = c.getUnitHeight() + 2;

		//printf("Lasso : %f, %f, %f, %f\n", xStart, yStart, xEnd, yEnd);

		//Render rext
		SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
		SDL_RenderDrawRect(gRenderer, &lasso);
	}

	unitEnemyTexture.render((int)uPosX, (int)uPosY, gRenderer);

}

void Unit::reset()
{
	float randX = randomFloat(0, (float)c.getScreenWidth() / 2);
	float randY = randomFloat(0, (float)c.getScreenHeight() / 2);

	setUPosX(randX);
	setUPosY(randY);

	uMidX = uPosX + c.getUnitWidth();
	uMidY = uPosY + c.getUnitHeight();

	setUPosToX(randX);
	setUPosToY(randY);
}

void Unit::resetEnemy()
{
	float randX = randomFloat((float)c.getScreenWidth() * 3/ 4, (float)c.getScreenWidth());
	float randY = randomFloat((float)c.getScreenHeight() * 3 / 4, (float)c.getScreenHeight());

	setUPosX(randX);
	setUPosY(randY);

	uMidX = uPosX + c.getUnitWidth();
	uMidY = uPosY + c.getUnitHeight();

	setUPosToX(randX);
	setUPosToY(randY);
}
