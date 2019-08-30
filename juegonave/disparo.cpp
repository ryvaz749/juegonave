#include "disparo.h"



disparo::disparo()
{
	shoot.setSize(sf::Vector2f(1, 15));
	shoot.setOrigin(.5f, 10);
	shoot.setFillColor(sf::Color::White);
}
void disparo::update() {
	shoot.setPosition(shoot.getPosition().x + sin(shoot.getRotation()/180*pi), shoot.getPosition().y - cos(shoot.getRotation() / 180 * pi));
}

disparo::~disparo()
{
}
