#include "pch.h"
#include "Game.h"


Game::Game()
{
}


Game::~Game()
{
}

bool Game::load(SDL_Renderer* gRenderer)
{
	textColor = { 255, 255, 255, 255 };

	newGame = true;
	endGame = false;

	tilesA = TilesArray();

	tilesA.load();

	//Calculate time step
	timeStep = stepTimer.getTicks() / 1000.f;

	l = Lasso();

	//ug = UnitGroup(gRenderer);
	ug = UnitGroup(gRenderer);
	ug.load(gRenderer);

	return true;
}

bool Game::input(SDL_Renderer* gRenderer, bool quit)
{
	if (!newGame)
	{
		while (SDL_PollEvent(&e) != 0)
		{

			if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
			{
				initGame();
			}
		}
	}
	else
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}

			//Debug
			/*car.handleEvent(e, timeStep);
			car2.handleEvent(e, timeStep);*/
			ug.handleEvent(e);
			ug.handleEventEnemy(e);
			l.handleEvent(e);

		}
	}
	return quit;
}

void Game::update()
{

	//Calculate time step
	timeStep = stepTimer.getTicks() / 1000.f;

	//Move for time step
	//car.move(timeStep);
	//car.isCollided(tilesA.isCollide(car.getCollider()));
	//car2.move(timeStep);
	//car2.isCollided(tilesA.isCollide(car2.getCollider()));0
	select = l.getSelection();
	ug.selectUnit(select);
	ug.selectUnitEnemy(select);
	ug.move(timeStep);

	if (ug.getNumDeadEnemy() == c.getNumUnitEnemy())
	{
		//printf("End Game : %d\n", ug.getNumDeadEnemy());
		endGame = true;
	}

	//Restart step timer
	stepTimer.start();
}

void Game::draw(SDL_Renderer* gRenderer)
{
	//car.render(gRenderer);
	//car2.render(gRenderer);
	//tilesA.render(gRenderer);
	ug.render(gRenderer);
	l.render(gRenderer);
	tilesA.render(gRenderer);

	if (endGame)
	{
		displayWinner(1, 0, textColor,gRenderer);
	}
}

void Game::initGame()
{
	newGame = true;
}

void Game::free()
{
	//Free loaded images
	//car.free();
	tilesA.free();
}

void Game::displayWinner(int p1, int p2, SDL_Color textColor, SDL_Renderer* gRenderer)
{
	std::string winnerText = "Player win";

	//if (p1 == c.getEndPartyGameScore())
	//{
	//	winnerText = "Player 1 Win!";
	//}
	//else
	//{
	//	winnerText = "Player 2 Win!";
	//}

	gInputTextTexture.loadFromRenderedText(winnerText.c_str(), textColor, gRenderer);
	gPromptTextTexture.render((c.getScreenWidth() - gPromptTextTexture.getWidth()) / 2, 0, gRenderer);
	gInputTextTexture.render((c.getScreenWidth() - gInputTextTexture.getWidth()) / 2, c.getScreenHeight() / 2, gRenderer);

	//gInputTextTexture.loadFromRenderedText("Press a key", textColor, gRenderer);
	//gPromptTextTexture.render((c.getScreenWidth() - gPromptTextTexture.getWidth()) / 2, 0, gRenderer);
	//gInputTextTexture.render((c.getScreenWidth() - gInputTextTexture.getWidth()) / 2, c.getScreenHeight() / 3 * 2, gRenderer);
}
