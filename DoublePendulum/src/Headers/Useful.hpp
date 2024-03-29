#pragma once
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "Common.hpp"

// Set up FPS display
void setupfps(sf::Text* fpsText);
// Updates the fps text and frame number
void fps(sf::Text* fpsText, sf::Clock* clock, unsigned int* Frame);
void hideConsole();
void showConsole();
