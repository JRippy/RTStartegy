#include "Unit.h"

#include <vector>

#pragma once
class UnitGroup
{
public:
	UnitGroup();
	UnitGroup(SDL_Renderer* gRenderer);

	Config c;

	std::vector<Unit> vUnit;

	void handleEvent(SDL_Event& e);

	void load(SDL_Renderer* gRenderer);

	void mousePress(SDL_MouseButtonEvent& b);

	void move(float timeStep);

	void selectUnit(SDL_Rect rect);

	void render(SDL_Renderer* gRenderer);

};

