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
			if (u.getSelected())
			{
				u.setUPosToX((float)x);
				u.setUPosToY((float)y);
			}

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

void UnitGroup::selectUnit(SDL_Rect rect)
{
	SDL_Rect r;
	int x, y, h, w;

	x = rect.x;
	y = rect.y;
	h = rect.h;
	w = rect.w;

	if ( w < 0 )
	{
		x = rect.x + rect.w;
		w = rect.w * -1;
	}

	if ( h < 0)
	{
		y = rect.y + rect.h;
		h = rect.h * -1;
	}

	r.x = x;
	r.y = y;
	r.h = h;
	r.w = w;

	for (size_t i = 0; i < c.getNumUnit(); i++)
	{
		Unit& u = vUnit[i];
		if (u.isInSelection(r) == true || u.getIsMoving() == true)
		{
			printf("Select or Move : %d, %d\n", u.isInSelection(r), u.getIsMoving());
			printf("Selection : %d, %d, %d, %d\n", r.x, r.y, r.h, r.w);
			u.setSelected(true);
		}
		else
		{
			u.setSelected(false);
		}
	}
}


