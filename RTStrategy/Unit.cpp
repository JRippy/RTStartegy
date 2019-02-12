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
		setUDestinationX(u.getUPosX() + u.getUOffsetX());
		setUDestinationY(u.getUPosY() + u.getUOffsetY());

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

	setUDestinationX(randX);
	setUDestinationY(randY);

	setUOffsetX(0);
	setUOffsetY(0);
}
