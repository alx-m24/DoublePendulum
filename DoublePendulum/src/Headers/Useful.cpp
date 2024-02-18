#include "Useful.hpp"

void setupfps(sf::Text* fpsText) {
	fpsText->setFont(arial);
	fpsText->setFillColor(sf::Color::Red);
	fpsText->setCharacterSize(24);
}
void fps(sf::Text* fpsText, sf::Clock* clock, unsigned int* Frame)
{
	if (clock->getElapsedTime().asSeconds() >= 1.f)
	{
		int FPS = *Frame;
		*Frame = 0;
		clock->restart();

		fpsText->setString("FPS: " + std::to_string(FPS));
	}
	++ * Frame;
	window->draw(*fpsText);
}

void hideConsole()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
}

void showConsole()
{
	ShowWindow(GetConsoleWindow(), SW_SHOW);
}