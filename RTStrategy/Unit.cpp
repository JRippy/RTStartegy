#include "pch.h"
#include "Unit.h"
#include <cstdlib>

Unit::Unit()
{
}


Unit::Unit(SDL_Renderer * gRenderer) :
	isSelected(false),
	isDead(false), 
	GameObjectUnit(gRenderer)
{
	loadMediaUnit(gRenderer);
	reset();

	//Set collision circle size
	mCollider.r = c.getUnitWidth() * 2;

	setUOffsetX(0);
	setUOffsetX(0);
	isPathFound(false);
	printf("Display Unit on : %f %f\n", uPosX, uPosY);

	//movement = Movement();

	//tilesA = TilesArray();

	//tilesA.load();

	//toXUpdated = false;
	//toYUpdated = false;
}

//Unit::Unit(SDL_Renderer * gRenderer, int enemy) :
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
//
//	/*movement = Movement();*/
//
//	//tilesA = TilesArray();
//
//	//tilesA.load();
//
//	//toXUpdated = false;
//	//toYUpdated = false;
//}

//float Unit::getUPosX()
//{
//	return uPosX;
//}
//
//float Unit::getUPosY()
//{
//	return uPosY;
//}
//
//void Unit::setUPosX(float f)
//{
//
//	if (uPosX >= c.getScreenWidth() - c.getUnitWidth())
//	{
//		uPosX = c.getScreenWidth() - c.getUnitWidth();
//	}
//	else {
//		uPosX = f;
//	}
//}
//
//void Unit::setUPosY(float f)
//{
//	if (uPosY >= c.getScreenWidth() - c.getUnitWidth())
//	{
//		uPosY = c.getScreenWidth() - c.getUnitWidth();
//	}
//	else {
//		uPosY = f;
//	}
//}
//
//float Unit::getUPosToX()
//{
//	return toX;
//}
//
//float Unit::getUPosToY()
//{
//	return toY;
//}
//
//void Unit::setUPosToX(float f)
//{
//	if (toX > c.getScreenWidth() - c.getUnitWidth())
//	{
//		toX = c.getScreenWidth() - c.getUnitWidth();
//	}
//	else {
//		toX = f;
//	}
//}
//
//void Unit::setUPosToY(float f)
//{
//	if (toY > c.getScreenHeight() - c.getUnitHeight())
//	{
//		toY = c.getScreenHeight() - c.getUnitHeight();
//	}
//	else {
//		toY = f;
//	}
//}
//
//float Unit::getUOffsetX()
//{
//	return offSetX;
//}
//
//float Unit::getUOffsetY()
//{
//	return offSetY;
//}
//
//void Unit::setUOffsetX(float f)
//{
//	offSetX = f;
//}
//
//void Unit::setUOffsetY(float f)
//{
//	offSetY = f;
//}

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
	mCollider.x = (int)getUPosX() + getUOffsetX() + (c.getUnitWidth() / 2);
	mCollider.y = (int)getUPosY() + getUOffsetY() + (c.getUnitHeight() / 2);

	uMidX = (int)getUPosX() + getUOffsetX() + (c.getUnitWidth() / 2);
	uMidY = (int)getUPosY() + getUOffsetY() + (c.getUnitHeight() / 2);
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
		//printf("\nRectangle de dimension : %i, %i, %i, %i || touche le cercle : %i\n", a.x, a.y, cX, cY, a.r);
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
//
//bool Unit::getPath()
//{
//	return movement.getPath(*this);
//}
//
//void Unit::setPath(bool b)
//{
//	movement.setPath(*this, b);
//}
//
//std::vector<Node> Unit::getVNode()
//{
//	return pathNode;
//}

void Unit::setSelected(bool b)
{
	isSelected = b;
}

bool Unit::isInSelection(SDL_Rect r)
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

void Unit::attack(GameObjectUnit& u)
{
	//Closest point on collision box
	int cX, cY;
	float uEX = u.getUPosX() + u.getUOffsetX();
	float uEY = u.getUPosY() + u.getUOffsetY();

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

	if (distanceSquared(getUPosX(), getUPosY(), cX, cY) <= getCollider().r * getCollider().r || distanceSquared(getUPosX() + c.getUnitWidth(), getUPosY(), cX, cY) <= getCollider().r * getCollider().r || distanceSquared(getUPosX(), getUPosY() + c.getUnitHeight(), cX, cY) <= getCollider().r * getCollider().r || distanceSquared(getUPosX() + c.getUnitWidth(), getUPosY(), cX, cY) <= getCollider().r * getCollider().r)
	{
		kill(u);
	}
}

void Unit::kill(GameObjectUnit& u)
{
	if (!u.isUnitDead())
	{
		setUPosToX(u.getUPosX() + u.getUOffsetX());
		setUPosToY(u.getUPosY() + u.getUOffsetY());

		u.setUnitDead(true);
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

//bool Unit::loadMediaUnitEnemy(SDL_Renderer * gRenderer)
//{
//	//Loading success flag
//	LoadedEnemy = true;
//
//	//Load Car texture
//	if (!unitEnemyTexture.loadFromFile("dot_Enemy.bmp", gRenderer))
//	{
//		printf("Failed to load dot enemy texture!\n");
//		LoadedEnemy = false;
//	}
//
//	return LoadedEnemy;
//}

//void Unit::move(float timeStep)
//{
//	movement.move(*this ,timeStep);
//}
//
//void Unit::moveEnemy(float timeStep)
//{
//	movement.moveEnemy(*this, timeStep);
//}
//
//
//void Unit::move(float timeStep)
//{
//	if (!pathfound)
//	{
//		pathNode.clear();
//
//		Node player;
//		player.x = getUPosX() / X_STEP;
//		player.y = getUPosY() / Y_STEP;
//
//		Node destination;
//		destination.x = toX / X_STEP;
//		destination.y = toY / Y_STEP;
//
//		printf("\n");
//
//		for (Node node : Cordinate::aStar(player, destination)) {
//
//			pathNode.push_back(node);
//			printf("Node X: %d Node Y: %d\n", node.x, node.y);
//
//		}
//
//		pathfound = true;
//		stepTravel = 0;
//	}
//
//	if (stepTravel < pathNode.size() && pathNode.size() != 0)
//	{
//		//Not last Node
//		if (stepTravel != pathNode.size() - 1)
//		{
//			if (travel(pathNode[stepTravel].x * c.getTileWidth() + c.getTileWidth() / 2, pathNode[stepTravel].y * c.getTileHeight() + c.getTileHeight() / 2))
//			{
//				printf("Path node X Y : %i, %i\n", pathNode[stepTravel].x, pathNode[stepTravel].y);
//				toXUpdated = false;
//				toYUpdated = false;
//				stepTravel++;
//			}
//		}
//		else
//		{
//			if (travel(pathNode[stepTravel].x * c.getTileWidth(), pathNode[stepTravel].y * c.getTileHeight()))
//			{
//				printf("Path last node X Y : %i, %i\n", pathNode[stepTravel].x, pathNode[stepTravel].y);
//				toXUpdated = false;
//				toYUpdated = false;
//				pathNode.clear();
//				stepTravel++;
//			}
//		}
//
//	}
//
//}
//
//
//bool Unit::travel(float x, float y)
//{
//	if (getUPosX() != x + getUOffsetX())
//	{
//		if (!toXUpdated)
//		{
//			//printf("Befor Modif ToX : %f\n", toX);
//			//float tmpx = toX - ((int)(toX / c.getTileWidth()) * c.getTileWidth());
//			//int tmpx1 = (int)toX / c.getTileWidth();
//			//float tmpx2 = tmpx1 * c.getTileWidth();
//			//float tmpx3 = toX - tmpx1 * c.getTileWidth();
//			printf("Path X : %f \nOffSetX : %f\n",x, getUOffsetX());
//
//			if (toX != x + getUOffsetX())
//			{
//				toX = x + getUOffsetX();
//			}
//
//			toXUpdated = true;
//		}
//
//		//if (toX != x)
//		//{
//		//	toX = x;
//		//	printf("ToX : %f\n", toX);
//		//}
//
//		//isMovingX = true;
//
//		float xAng = toX - getUPosX() + getUOffsetX();
//		float yAng = toY - getUPosY() + getUOffsetY();
//		float tan = atan2(yAng, xAng);
//
//		//float gPx= getUPosX();
//		//setUPosX(gPx + c.getVelUnit() * cos(tan) / 10);
//		uPosX += c.getVelUnit() * cos(tan) / 10;
//
//		if (fabs(getUPosX() - toX - getUOffsetX()) <= 0.5f)
//		{
//			setUPosX(toX + getUOffsetX());
//		}
//
//		//printf("Position X final : %f\n", uPosX);
//	}
//	else
//	{
//		isMovingX = false;
//	}
//
//	shiftColliders();
//
//	if (uPosY != y + getUOffsetY())
//	{
//		if (!toYUpdated)
//		{
//			float tmpy = toY - ((toY / c.getTileHeight()) * c.getTileHeight());
//
//			if (toY != y + getUOffsetY())
//			{
//				toY = y + getUOffsetY();
//				printf("ToY : %f\nOffSetY : %f\n\n", toY, getUOffsetY());
//			}
//
//			toYUpdated = true;
//		}
//
//		//if (toY != y)
//		//{
//		//	toY = y ;
//		//	printf("ToY : %f\n\n", toY);
//		//}
//
//		float xAng = toX - getUPosX() + getUOffsetX();
//		float yAng = toY - getUPosY() + getUOffsetY();
//		float tan = atan2(yAng, xAng);
//
//		//isMovingY = true;
//		
//		uPosY += c.getVelUnit() * sin(tan) / 10;
//
//		if (fabs(getUPosY() - toY - getUOffsetY()) <= 0.5f)
//		{
//			setUPosY(toY + getUOffsetY());
//		}
//	}
//	else
//	{
//		isMovingY = false;
//	}
//
//	shiftColliders();
//
//	bool b = false;
//	if (getUPosY() == toY + getUOffsetY() && getUPosX() == toX + getUOffsetX())
//	{
//		b = true;
//	}
//
//	return b;
//}
//
//
//void Unit::moveEnemy(float timeStep)
//{
//	if (!isDead)
//	{
//		if (tilesA.isCollide(getCollider()))
//		{
//			float randX = randomFloat(0, c.getScreenWidth());
//			float randY = randomFloat(0, c.getScreenHeight());
//
//			setUPosToX(randX);
//			setUPosToY(randY);
//		}
//
//		if (uPosX != toX + getUOffsetX())
//		{
//			isMovingX = true;
//			//TODO
//			float xAng = toX - uPosX + getUOffsetX();
//			float yAng = toY - uPosY + getUOffsetY();
//			float tan = atan2(yAng, xAng);
//
//			uPosX += c.getVelUnit() * cos(tan) / 10;
//
//			if (fabs(uPosX - toX + getUOffsetX()) <= 0.5f)
//			{
//				uPosX = toX + getUOffsetX();
//			}
//		}
//		else
//		{
//
//			isMovingX = false;
//			setUPosToX(randomFloat(0, pathEnemyX));
//			pathEnemyX = pathEnemyX / 2;
//		}
//
//		shiftColliders();
//
//		if (uPosY != toY + getUOffsetY())
//		{
//			float xAng = toX - uPosX + getUOffsetX();
//			float yAng = toY - uPosY + getUOffsetY();
//			float tan = atan2(yAng, xAng);
//
//			isMovingY = true;
//
//			uPosY += c.getVelUnit() * sin(tan) / 10;
//
//			if (fabs(uPosY - toY + getUOffsetY()) <= 0.5f)
//			{
//				uPosY = toY + getUOffsetY();
//
//			}
//		}
//		else
//		{
//			isMovingY = false;
//			setUPosToY(randomFloat(0, pathEnemyY));
//			pathEnemyY = pathEnemyY / 2;
//		}
//
//		shiftColliders();
//	}
//}

int Unit::getNodeX(int i)
{
	return pathNode[i].x;
}

int Unit::getNodeY(int i)
{
	return pathNode[i].y;
}

void Unit::clearPath()
{
	pathNode.clear();
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

		lasso.x = getUPosX() - 1;
		lasso.y = getUPosY() - 1;
		lasso.w = c.getUnitWidth() + 2;
		lasso.h = c.getUnitHeight() + 2;

		//printf("Lasso : %f, %f, %f, %f\n", xStart, yStart, xEnd, yEnd);

		//Render rext
		SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
		SDL_RenderDrawRect(gRenderer, &lasso);
	}

	unitTexture.render((int)getUPosX(), (int)getUPosY(), gRenderer);
}

void Unit::reset()
{
	float randX = randomFloat(0, (float)c.getScreenWidth() / 2);
	float randY = randomFloat(0, (float)c.getScreenHeight() / 2);

	setUPosX(randX);
	setUPosY(randY);

	uMidX = uPosX + c.getUnitWidth() / 2;
	uMidY = uPosY + c.getUnitHeight() / 2;

	setUPosToX(randX);
	setUPosToY(randY);

	setUOffsetX(0);
	setUOffsetY(0);
}
