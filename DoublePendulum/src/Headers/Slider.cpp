#include "Slider.hpp"

Slider::Slider(int Min, int Max, std::string Name, sf::Vector2<float> Pos, float* ValueToChange) : valueToChange(ValueToChange), name(Name), pos(Pos)
{
	min = std::min(Min, Max);
	max = std::max(Min, Max);

	handle.setRadius(5.0f);
	handle.setOrigin(5.0f, 5.0f);
	handle.setFillColor(sf::Color::White);
	float calcPos = (((*valueToChange - min) * size) / (max - min)) + pos.x;
	handle.setPosition(calcPos, pos.y);

	line.setPrimitiveType(sf::Lines);
	line.resize(2);
	line[0].color = { 163, 163, 163 };
	line[1].color = { 163, 163, 163 };
	line[0].position = pos;
	line[1].position = {pos.x + size, pos.y};

	text.setPosition(pos.x + (size / 4.0f), pos.y - 25.0f);
	text.setFont(arial);
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(12.0f);
}

void Slider::update()
{
	sf::Vector2<float> mousePos = sf::Vector2<float>(sf::Mouse::getPosition(*window));
	left = sf::Mouse::isButtonPressed(sf::Mouse::Left);

	if (handle.getGlobalBounds().contains(mousePos) && left) updating = true;
	else if (lastleft && !left && updating) updating = false;

	if (updating) {		
		handle.setPosition(mousePos.x, pos.y);
	}

	const float handlePos_X = handle.getPosition().x;
	if (handlePos_X < pos.x) handle.setPosition(pos.x, pos.y);
	else if (handlePos_X > pos.x + size) handle.setPosition(pos.x + size, pos.y);;

	lastleft = left;

	float val = getVal();
	*valueToChange = val;

	text.setString(name + ": " + std::to_string(val));
}

void Slider::draw()
{
	window->draw(line);
	window->draw(handle);
	window->draw(text);
}

void Slider::reset() {
	float calcPos = (((*valueToChange - min) * size) / (max - min)) + pos.x;
	handle.setPosition(calcPos, pos.y);
}

float Slider::getVal()
{
	// should be x_pos of handle - x_size of slider, relative to left of slider
	float val = handle.getPosition().x - pos.x;
	return map(val);
}

float Slider::map(float value)
{
	return value * (max - min) / size + min;
}
