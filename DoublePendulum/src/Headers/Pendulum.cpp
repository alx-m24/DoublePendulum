#include "Pendulum.hpp"

Pendulum::Pendulum(std::pair<float, float> Length, unsigned int SubSteps) : length(Length), substeps(SubSteps)
{
	/*
	length.first *= -1.0f;
	length.second *= -1.0f;*/

	updatePos();
}

void Pendulum::update(float dt)
{
	float sub_dt = dt / substeps;
	
	for (int i = 0; i < substeps; ++i) {
		updateAcc();
		updateAngle(sub_dt);
		updatePos();
	}
}

void Pendulum::reset()
{
	angle = { PI / 2, PI / 2 };
	prev_Angle = angle;
	angleVel = { 0.0f, 0.0f };
	angleAcc = { 0.0f, 0.0f };

	updatePos();
}

void Pendulum::updatePos()
{
	pos.first.x = origin.x + length.first * sin(angle.first);
	pos.first.y = origin.y + length.first * cos(angle.first);

	pos.second.x = pos.first.x + (length.second * sin(angle.second));
	pos.second.y = pos.first.y + (length.second * cos(angle.second));
}

void Pendulum::updateAcc()
{
	float num1 = -G * (2.0f * mass.second + mass.first) * sin(angle.first);
	float num2 = mass.second * G * sin(angle.first - (2.0f * angle.second));
	float num3 = 2.0f * sin(angle.first - angle.second);
	float num4 = mass.second * ((angleVel.second * angleVel.second * length.second) + (angleVel.first * angleVel.first * length.first * cos(angle.first - angle.second)));

	float numT = num1 - num2 - (num3 * num4);
	float den = length.first * ((2.0f * mass.first) + mass.second - mass.second * cos(2.0f * angle.first - 2.0f * angle.second));

	angleAcc.first = numT / den;

	
	num1 = 2.0f * sin(angle.first - angle.second);
	num2 = (angleVel.first * angleVel.first) * length.first * (mass.first + mass.second);
	num3 = G * (mass.first + mass.second) * cos(angle.first);
	num4 = (angleVel.second * angleVel.second) * length.second * mass.second * cos(angle.first - angle.second);

	numT = num1 * (num2 + num3 + num4);
	den = length.second * ((2.0f * mass.first) + mass.second - mass.second * cos(2.0f * angle.first - 2.0f * angle.second));

	angleAcc.second = numT / den;
}

void Pendulum::updateAngle(float dt)
{
	// Verlet
	std::pair<float, float> temp = angle;

	angleVel.first = (angle.first - prev_Angle.first) / friction;
	angleVel.second = (angle.second - prev_Angle.second) / friction;

	angle.first = angle.first + angleVel.first + (angleAcc.first) * dt * dt;
	angle.second = angle.second + angleVel.second + (angleAcc.second) * dt * dt;

	prev_Angle = temp;
}

std::pair<sf::Vector2<float>, sf::Vector2<float>> Pendulum::getPos()
{
	return pos;
}

std::pair<float, float> Pendulum::getVel()
{
	return angleVel;
}

std::pair<float, float> Pendulum::getMass()
{
	return mass;
}
