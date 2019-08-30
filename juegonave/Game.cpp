#include "asteroid.h"
#include "Game.h"
#include <cmath>
#include <list>
#include <stdlib.h>
#include <iostream>
#include "disparo.h"
using namespace std;
/* xplocion desaparesca*/
Game::Game()
	:window(sf::VideoMode(700, 700), "app"), player()
{
	timedis = 1;
	numdis = 0;
	numboom = 0;
	pause = false;
	stop = false;
	numast = 0;
	tiempo = 0;
	asteroidrotation = 0;
	radio = 20;
	pi = 3.1415926535897932384626433;
	angulo = 0;
	fondo.setPosition(-50, -50);
	fondo.setSize(sf::Vector2f(800, 800)); 
	
	player.setSize(sf::Vector2f(20, 20));
	player.setPosition(200, 200);
	nave.loadFromFile("nave.png");
	asteroide.loadFromFile("asteroide.png");
	xplocion.loadFromFile("xplocion.png");
	fond.loadFromFile("fondo.jpg");
	fondo.setTexture(&fond);
	player.setTexture(&nave);
	player.setOrigin(10, 10);
	velx = 0;
	vely = 0;
	x = 0;
	y = 0;

}
void Game::run() {
	sf::Clock clock;
	while (window.isOpen()) {
		sf::Time deltatime = clock.restart();
		event();
		if (pause == false) {
			update(deltatime);
		}
		
		render();
	}
}
void Game::event() {
	sf::Event event;
	while (window.pollEvent(event)) {
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			input(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			input(event.key.code, false);
			break;
		case sf::Event::Closed:
			window.close();
			break;
		}

	}
}

void Game::input(sf::Keyboard::Key key, bool press) {
	switch (key) {
	case sf::Keyboard::W:
		up = press;
		break;
	case sf::Keyboard::S:
		down = press;
		break;
	case sf::Keyboard::A:
		left = press;
		break;
	case sf::Keyboard::D:
		right = press;
		break;
	case sf::Keyboard::Q:
		giro = press;
		break;
	case sf::Keyboard::E:
		giroinv = press;
		break;
	case sf::Keyboard::P:
		pause = true;
		break;
	case sf::Keyboard::O:
		pause = false;
		break;
	case sf::Keyboard::Space:
		shooti();
		break;
	}
	
}




void Game::update(sf::Time deltatime)
{
	tiempo += deltatime.asSeconds();
	timedis += deltatime.asSeconds();
	if (tiempo > .7f && stop == false) {
		tiempo = 0;
		assets[numast] = asteroid();
		assets[numast].ast.setTexture(&asteroide);
		numast += 1;
	}
	if (right == true) {
		velx += .001f;
	}
	if (left == true) {
		velx -= .001f;
	}
	if (up == true) {
		vely -= .001f;
	}
	if (down == true) {
		vely += .001f;
	}
	if (freno == true) {
		vely = 0;
		velx = 0;
	}
	if (giro == true) {
		angulo -= .5f;
	}
	if (giroinv == true) {
		angulo += .5f;
	}
	x += velx;
	y += vely;
	if (x < -200) {
		x = 500;
		
	}
	if (y < -200) {
		y = 500;
	}
	if (x > 500) {
		x = -200;
	}
	if (y > 500) {
		
		y = -200;
	}
	asteroidrotation += .125f;

	for (int a = 0; a < numast; a += 1) {
		assets[a].update(deltatime);
		
		if (abs(player.getPosition().x - assets[a].posix()) <   assets[a].radiof() && abs(player.getPosition().y - assets[a].posiy()) <  assets[a].radiof()) {
			player.setTexture(&xplocion);
			player.setSize(sf::Vector2f(160, 160));
			player.setOrigin(40 ,40);
			stop = true;
		}
		for (int e = 1; e <= numast - a - 1; e += 1) {
			if (abs(assets[a + e].posix() - assets[a].posix()) < -20 + assets[a + e ].radiof() + assets[a].radiof() && abs(assets[a + e ].posiy() - assets[a].posiy()) < -20 + assets[a + e ].radiof() + assets[a].radiof()) {
				float p1x = assets[a].posix(), p1y = assets[a].posiy(), p2x = assets[a+e].posix(), p2y = assets[a+e].posiy();
				assets[a] = asteroid();
				assets[a].ast.setTexture(&xplocion);
				assets[a].ast.setPosition(p1x, p1y);
				assets[a].xplode = true;
				assets[a+e] = asteroid();
				assets[a + e].ast.setTexture(&xplocion);
				assets[a + e].ast.setPosition(p2x, p2y);
				assets[a + e].xplode = true;
				/*booms[a].boom.setTexture(&xplocion);
				booms[a+e].boom.setTexture(&xplocion);
				booms[a].boom.setPosition(assets[a].posix(), assets[a].posiy());
				booms[a+e].boom.setPosition(assets[a+e].posix(), assets[a+e].posiy());
				assets[a].exists = false;
				assets[a + e ].exists = false;
				numboom += 1;*/
			}
		}
		
		
	}
	if (stop == false) {
		player.setPosition(200 + x, 200 + y);
		player.setRotation(angulo);
	}
		for (int a = 0; a < 150; a += 1) {
			if (assets[a].exists == false || assets[a].posix() < -100 || assets[a].posiy() < -100 || assets[a].posix() > 800 || assets[a].posiy() > 800) {
				numast -= 1;
				for (int e = a; e < 150; e += 1) {
					assets[e] = assets[e + 1];
				}
			}
		}
	for (int a = 0; a < numdis; a += 1) {
		municion[a].update();
	}
	if (numdis == 2) {
		for (int a = 0; a < 1; a += 1) {
			municion[a] = municion[a + 1];
		}
	}
}
void Game::shooti() {
	if (timedis >= .8f){
		municion[numdis] = disparo();
		municion[numdis].shoot.setPosition(player.getPosition().x, player.getPosition().y);
		municion[numdis].shoot.setRotation(player.getRotation());
		numdis += 1;
		timedis = 0;
	}
	
}
void Game::render()
{
	window.clear();
	window.draw(fondo);
	window.draw(player);
	for (int a = 0; a < numast; a += 1) {
			window.draw(assets[a].ast);
		
	}
	for (int a = 0; a < numdis; a += 1) {
		window.draw(municion[a].shoot);
	}
	window.display();
}
Game::~Game()
{
}
