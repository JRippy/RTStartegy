#include "pch.h"
#include "UnitGroup.h"


UnitGroup::UnitGroup()
{

}


UnitGroup::UnitGroup(SDL_Renderer* gRenderer)
{	
	vUnit.reserve(c.getNumUnit());
}

void UnitGroup::handleEvent(SDL_Event & e)
{
	//If a key was pressed
	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		mousePress(e.button);
	}
}

void UnitGroup::load(SDL_Renderer* gRenderer)
{
	for (size_t i = 0; i < c.getNumUnit(); i++)
	{
		Unit u = Unit(gRenderer);
		vUnit.push_back(u);
	}
}

void UnitGroup::render(SDL_Renderer * gRenderer)
{
	for (size_t i = 0; i < c.getNumUnit(); i++)
	{
		Unit u = vUnit[i];
		u.render(gRenderer);
	}
}

void UnitGroup::mousePress(SDL_MouseButtonEvent& b) {
	
	if (b.button == SDL_BUTTON_LEFT) {
		//handle a left-click
		int x, y;
		SDL_GetMouseState(&x, &y);

		if (x <= 0)
		{
			x = 0;
		}
		//else if (mPosX > c.getScreenWidth() - (c.getRacketWidth() / 2) || x > c.getScreenWidth() - (c.getRacketWidth() / 2))
		//{
		//	mPosX = (float)c.getScreenWidth() - (float)c.getRacketWidth() / 2;
		//}
		else if (x < c.getScreenWidth() && x > 0)
		{
			//Adjust position
			x = (float)x - c.getUnitWidth() / 2;
			//move(timeStep);
		}

		if (y <= 0)
		{
			y = 0;
		}
		//else if (mPosy > c.getScreenWidth() - (c.getRacketWidth() / 2) || y > c.getScreenWidth() - (c.getRacketWidth() / 2))
		//{
		//	mPosy = (float)c.getScreenWidth() - (float)c.getRacketWidth() / 2;
		//}
		else if (y < c.getScreenHeight() && y > 0)
		{
			//Adjust position
			y = (float)y - c.getUnitHeight() / 2;
			//move(timeStep);
		}

		for (size_t i = 0; i < c.getNumUnit(); i++)
		{
			Unit& u = vUnit[i];
			u.setUPosToX((float)x);
			u.setUPosToY((float)y);

		}

	}
}

void UnitGroup::move(float timeStep)
{
	for (size_t i = 0; i < c.getNumUnit(); i++)
	{
		Unit& u = vUnit[i];
		u.move(timeStep);
	}
}


