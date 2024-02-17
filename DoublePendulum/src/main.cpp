// SFML
#include <SFML/Graphics.hpp>
// My headers
#include "Headers/MainLoop.hpp"
#include "Headers/Common.hpp"
#include "Headers/Pendulum.hpp"
#include "Headers/Useful.hpp"
#include "Headers/Trail.hpp"

sf::RenderWindow* window;

int main() {
	// window settings
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;

	// creating window
	sf::RenderWindow Mainwindow(sf::VideoMode(800, 600), "Double Pendulum", sf::Style::Close, settings);
	Mainwindow.setPosition(Mainwindow.getPosition() - sf::Vector2i(0, 50));
	Mainwindow.setVerticalSyncEnabled(true);
	window = &Mainwindow;

	hideConsole();

	// my main loop class
	Loop loop;

	Pendulum pendulum({ 100.0f, 100.0f }, 1);
	Trail trail;

	sf::CircleShape p0(5.0f), p1(10.0f), p2(10.0f);

	p0.setOrigin(p0.getRadius(), p0.getRadius()), p1.setOrigin(p1.getRadius(), p1.getRadius()), p2.setOrigin(p2.getRadius(), p2.getRadius());
	p0.setFillColor(sf::Color::White), p1.setFillColor(sf::Color::Blue), p2.setFillColor(sf::Color::Blue);

	p0.setPosition(sf::Vector2<float>(pendulum.origin));

	sf::VertexArray lines(sf::Lines, 4);

	sf::Clock clock;
	// main loop
	while (Mainwindow.isOpen())
	{
		// processing inputs
		loop.Input();

		// updating window
		loop.Update();
		pendulum.update(clock.restart().asSeconds());

		std::pair<sf::Vector2<float>, sf::Vector2<float>> pos = pendulum.getPos();

		p1.setPosition(pos.first);
		p2.setPosition(pos.second);

		lines[0].position = sf::Vector2<float>(pendulum.origin);
		lines[1].position = pos.first;
		lines[2].position = pos.first;
		lines[3].position = pos.second;

		trail.update(pos.second, pendulum.getVel().second);

		// rendering all objects
		window->draw(trail);
		window->draw(lines);
		window->draw(p0);
		window->draw(p1);
		window->draw(p2);
		loop.Render();
	}
	return 0;
}
