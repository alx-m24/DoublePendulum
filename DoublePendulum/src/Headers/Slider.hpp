#pragma once
#include <SFML/Graphics.hpp>
#include "Common.hpp"


class Slider {
private:
	sf::Text text;
	sf::CircleShape handle;
	sf::VertexArray line;
	sf::Vector2<float> pos;
private:
	float* valueToChange;
	float size = 225.0f;
	int min, max;
	bool updating = false;
	bool left = false, lastleft = false;

	std::string name;

	float map(float value);
public:
	Slider(int Min, int Max, std::string Name, sf::Vector2<float> Pos, float* ValueToChange);

	void update();
	void draw();
	void reset();

	float getVal();
};
