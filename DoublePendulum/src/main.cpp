// SFML
#include <SFML/Graphics.hpp>
// Other
#include <iostream>
// My headers
#include "Headers/MainLoop.hpp"
#include "Headers/Common.hpp"
#include "Headers/Pendulum.hpp"
#include "Headers/Useful.hpp"
#include "Headers/Trail.hpp"
#include "Headers/Slider.hpp"

sf::RenderWindow* window;
sf::Font arial;

int main() {
	arial.loadFromFile("C:/Windows/Fonts/arial.ttf");

	// window settings
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;

	// creating window
	sf::RenderWindow Mainwindow(sf::VideoMode(800, 600), "Double Pendulum", sf::Style::Close, settings);
	Mainwindow.setPosition(Mainwindow.getPosition() - sf::Vector2i(0, 50));
	Mainwindow.setVerticalSyncEnabled(true);
	window = &Mainwindow;

	hideConsole();

	sf::Text fpsText;
	setupfps(&fpsText);

	// my main loop class
	Loop loop;

	Pendulum pendulum({ 100.0f, 100.0f }, 1);

	Trail trail;

	sf::CircleShape p0(5.0f), p1(10.0f), p2(10.0f);

	p0.setOrigin(p0.getRadius(), p0.getRadius()), p1.setOrigin(p1.getRadius(), p1.getRadius()), p2.setOrigin(p2.getRadius(), p2.getRadius());
	p0.setFillColor(sf::Color::White), p1.setFillColor(sf::Color::Blue), p2.setFillColor(sf::Color::Blue);

	p0.setPosition(sf::Vector2<float>(pendulum.origin));

	sf::VertexArray lines(sf::Lines, 4);

	std::vector<Slider*> sliders;
	sliders.push_back(new Slider(10, 200, "Lenght 1", {5.0f, 60.0f}, &pendulum.length.first));
	sliders.push_back(new Slider(10, 200, "Lenght 2", {5.0f, 90.0f}, &pendulum.length.second));
	sliders.push_back(new Slider(1, 10, "Mass 1", {5.0f, 120.0f}, &pendulum.mass.first));
	sliders.push_back(new Slider(1, 10, "Mass 2", {5.0f, 150.0f}, &pendulum.mass.second));
	sliders.push_back(new Slider(1, 2, "Friction", {5.0f, 190.0f}, &pendulum.friction));


	sf::Text desctiption("Ctrl+C to reset sliders\nCtrl+Shift+C to reset position and trail", arial, 16);
	desctiption.setPosition(sf::Vector2<float>(window->getSize()) + sf::Vector2<float>(-800, -40.0f));
	desctiption.setFillColor(sf::Color::White);

	sf::Clock clock, fpsClock;
	unsigned int Frame = 0;
	bool reset = false, lastReset = false;
	// main loop
	while (Mainwindow.isOpen())
	{
		fps(&fpsText, &fpsClock, &Frame);

		// processing inputs
		loop.Input();

		reset = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::C);
		if (reset && !lastReset) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::LShift)) {
				pendulum.angle = { PI / 2, PI / 2 };
				pendulum.prev_Angle = { PI / 2, PI / 2 };
				pendulum.angleVel = { 0.0f, 0.0f };
				pendulum.angleAcc = { 0.0f, 0.0f };
				trail.clear();
			}
			else {
				pendulum.reset();
				for (Slider* s : sliders) s->reset();
			}
		}
		lastReset = reset;

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

		for (Slider* s : sliders) {
			s->update();
			s->draw();
		}

		// rendering all objects
		window->draw(trail);
		window->draw(lines);
		window->draw(p0);
		window->draw(p1);
		window->draw(p2);
		window->draw(fpsText);
		window->draw(desctiption);
		loop.Render();
	}
	return 0;
}
