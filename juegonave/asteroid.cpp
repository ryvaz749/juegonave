#include "asteroid.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <cmath>
using namespace std;
asteroid::asteroid()
{
	tiempo = 0;
	exists = true;
	xplode = false;
	angular = 1;
	pi = 3.1415926535897932384626433;
	angulo = rand() % 90-30;
	angulo /= 180;
	angulo *= pi;
	direccion = rand() % 4;
	radio = rand() % 20 + 20;
	ast.setRadius(radio);
	boundary = ast.getGlobalBounds();
	if (boundary.intersects(boundary)) {
		ast.setFillColor(sf::Color::White);
	}
	int lugar = rand() % 500 + 100;
	if (lugar > 350) {
		angular = -1;
	}
	switch (direccion)
	{
	case 0:
		ast.setPosition(lugar, -30);
		break;
	case 1:
		ast.setPosition(lugar, 730);
		break;
	case 2:
		ast.setPosition(-30, lugar);
		break;
	case 3:
		ast.setPosition(730, lugar);
		break;
	}
	
	ast.setOrigin(radio, radio);
}
void asteroid::update(sf::Time deltatime) {
	tiempo += deltatime.asSeconds();
	if (xplode == true) {
		tiempo += deltatime.asSeconds();
	}
	if (tiempo > 1000) {
		exists = false;
	}
	ast.setRotation(ast.getRotation() + .125f);
	switch (direccion)
	{
	case 0:
		ast.setPosition(ast.getPosition().x+ .15f*sin(angulo)*angular, ast.getPosition().y + .15f*cos(angulo));
		break;
	case 1:
		ast.setPosition(ast.getPosition().x+.15f*cos(angulo)*angular, ast.getPosition().y - .15f*cos(angulo));
		break;
	case 2:
		ast.setPosition(ast.getPosition().x + .1f*cos(angulo), ast.getPosition().y + .1f*sin(angulo)*angular);
		break;
	case 3:
		ast.setPosition(ast.getPosition().x - .1f*cos(angulo), ast.getPosition().y + .1f*sin(angulo)*angular);
		break;
	}
	
	
}
float asteroid::posix() {
	return  ast.getPosition().x;
}
float asteroid::posiy() {
	return  ast.getPosition().y;
}
float asteroid::radiof() {
	return  radio;
}


asteroid::~asteroid()
{
}
