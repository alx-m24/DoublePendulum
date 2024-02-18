#pragma once
#include <SFML/Graphics.hpp>
#include "Common.hpp"

class Pendulum {
public:
	std::pair<sf::Vector2<float>, sf::Vector2<float>> pos = { {0.0f, 0.0f}, {0.0f, 1.0f} };
	std::pair<float, float> angleVel = { 0.0f, 0.0f };
	std::pair<float, float> angleAcc = { 0.0f, 0.0f };

	std::pair<float, float> length = { 1.0f, 1.0f };
	std::pair<float, float> initiallength = { 1.0f, 1.0f };
	std::pair<float, float> mass = { 2.0f, 2.0f };
	//std::pair<float, float> angle = { 0.0f, 0.0f };
	std::pair<float, float> angle = { PI / 2, PI / 2 };
	std::pair<float, float> prev_Angle = angle;

	void updateAcc();
	void updateAngle(float dt);
	void updatePos();

	unsigned int substeps = 1;
public:
	Pendulum(std::pair<float, float> Length, unsigned int SubSteps);

	void update(float dt);
	void reset();

	sf::Vector2<int> origin = { int(window->getSize().x / 2), int(window->getSize().y / 3) };

	std::pair<sf::Vector2<float>, sf::Vector2<float>> getPos();
	std::pair<float, float> getVel();
	std::pair<float, float> getMass();

	float friction = 1.0f;
};