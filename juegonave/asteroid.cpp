#pragma once
#include "asteroid.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <cmath>
using namespace std;
asteroid::asteroid()
{
	vel = .5;
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
	
	int lugar = rand() % 500 + 100;
	if (lugar > 350) {
		angular = -1;
	}
	switch (direccion)//el lugar en el que aparecera sera random y segun del lado que salga sera su direccion que tambien te tendra un angulo random
	{
	case 0:
		ast.setPosition(lugar, 00);
		break;
	case 1:
		ast.setPosition(lugar, 700);
		break;
	case 2:
		ast.setPosition(0, lugar);
		break;
	case 3:
		ast.setPosition(700, lugar);
		break;
	}
	ast.setOrigin(radio, radio);//el origen del giro lo pone en el sentro segun sea el tamaño del asteroide que tambien es random
}
void asteroid::update(sf::Time deltatime) {
	// si el asteroide explota inicia un contador de 5 segundos y luego deja de existir
	if (xplode == true) {
		tiempo += deltatime.asSeconds();
	}
	if (tiempo > 5) {
		exists = false;
	}
	//si el asteroide no esta explotado se movera segun su angulo a la velocidad vel
	if (xplode == false) {
		ast.setRotation(ast.getRotation() + .125f);
		switch (direccion)
		{
		case 0:
			ast.setPosition(ast.getPosition().x + vel *sin(angulo)*angular, ast.getPosition().y + vel *cos(angulo));
			break;
		case 1:
			ast.setPosition(ast.getPosition().x + vel *cos(angulo)*angular, ast.getPosition().y - vel *cos(angulo));
			break;
		case 2:
			ast.setPosition(ast.getPosition().x + vel *cos(angulo), ast.getPosition().y + vel *sin(angulo)*angular);
			break;
		case 3:
			ast.setPosition(ast.getPosition().x - vel *cos(angulo), ast.getPosition().y + vel *sin(angulo)*angular);
			break;
		}
	}
	
	
	
}
//esto es para que returne sieros valores pero no sean modificados, pues estan en el private
float asteroid::posix() {
	return  ast.getPosition().x;
}
float asteroid::posiy() {
	return  ast.getPosition().y;
}
float asteroid::radiof() {
	return  radio;
}

//para demostrar que si se destruyen
asteroid::~asteroid()
{
	cout << "sirvio" << endl;
}
