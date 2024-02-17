#include "Trail.hpp"

#include <iostream>

sf::Color Trail::calculateColor(float vel)
{
	vel = fabs(vel);
	vel *= 100.0f;

	if (vel < 1.0f) return sf::Color(0, 15, 97);
	if (vel < 3.0f) return sf::Color::Blue;
	if (vel < 5.0f) return sf::Color::Cyan;
	if (vel < 7.0f) return sf::Color::Green;
	if (vel < 9.0f) return sf::Color::Yellow;
	else return sf::Color::Red;

	return sf::Color::Blue;
}

void Trail::update(sf::Vector2<float> pos, float vel)
{
	//this->append(sf::Vertex(pos, calculateColor(vel)));
	this->append(sf::Vertex(pos, sf::Color(163, 163, 163, 50)));
}
