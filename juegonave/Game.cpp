#pragma once
#include "asteroid.h"
#include "Game.h"
#include <cmath>
#include <list>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <list>
#include "disparo.h"
#include "sharepointer.h"
using namespace std;

Game::Game()
	:window(sf::VideoMode(700, 700), "app"), player() // se crea la pantaya cuadrada de 700 pixeles de lado y se construye el player y todo lo inicial del juego
{
	restart = false;
	srand(time(NULL));
	timedis = 1;
	numdis = 0;
	numboom = 0;
	pause = false;
	stop = false;
	tiempo = 0;
	asteroidrotation = 0;
	radio = 20;
	score = 0;
	pi = 3.1415926535897932384626433;
	angulo = 0;
	geimover.setString("TEMORRISTE");  
	geimover.setPosition(150, 300);
	geimover.setCharacterSize(50);
	fuente.loadFromFile("space age.ttf");
	geimover.setFont(fuente);
	tscore.setString(to_string(score));
	fondo.setPosition(-50, -50);
	fondo.setSize(sf::Vector2f(800, 800)); 
	tscore.setPosition(600, 20);
	tscore.setCharacterSize(30);
	tscore.setFont(fuente);
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
	while (window.isOpen()) {//mientras la ventana este abierta y no este en pausa se actualizara y luego se renderizara 
		sf::Time deltatime = clock.restart();
		event();
		if (pause == false) {
			update(deltatime);
			render();
		}
		
		
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

void Game::input(sf::Keyboard::Key key, bool press) {//aqui se controla el imput de cuando se precionan las teclas
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
	case sf::Keyboard::R:
		restart = press;
		break;
	}
	
}




void Game::update(sf::Time deltatime)
{
	if (stop == true && restart == true) {
		restart = false;
		srand(time(NULL));
		timedis = 1;
		numdis = 0;
		numboom = 0;
		pause = false;
		stop = false;
		tiempo = 0;
		asteroidrotation = 0;
		radio = 20;
		score = 0;
		pi = 3.1415926535897932384626433;
		angulo = 0;
		geimover.setString("TEMORRISTE");
		geimover.setPosition(150, 300);
		geimover.setCharacterSize(50);
		fuente.loadFromFile("space age.ttf");
		geimover.setFont(fuente);
		tscore.setString(to_string(score));
		fondo.setPosition(-50, -50);
		fondo.setSize(sf::Vector2f(800, 800));
		tscore.setPosition(600, 20);
		tscore.setCharacterSize(30);
		tscore.setFont(fuente);
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
	tiempo += deltatime.asSeconds();
	timedis += deltatime.asSeconds();
	if (tiempo > .4f && stop == false) {//cada .4 segundos se crea un asteroide con un share pointer y se pone al principio de la lista
		tiempo = 0;
		la.push_front(sharepointer<asteroid*>(new asteroid()));
		it = la.begin();
		((*(*it).a)).ast.setTexture(&asteroide);
	}
	//aqui se controla el movimiento del personaje
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
	it = la.begin();
	for (it = la.begin(); it != la.end(); it++) {// aqui se checa de asteroide por asteroide a ver si uno choco con el jugador con las distancias de uno y otro
		(*((*it).a)).update(deltatime);
		if (abs(player.getPosition().x - (*((*it).a)).posix()) < (*((*it).a)).radiof() && abs(player.getPosition().y - (*((*it).a)).posiy()) < (*((*it).a)).radiof()) {
			player.setTexture(&xplocion);// si si choco el personaje explota
			player.setSize(sf::Vector2f(160, 160));
			player.setOrigin(40 ,40);
			stop = true;
			
		}
		ite = it;
		ite++;
		for (ite; ite != la.end(); ite++) {// aqui se checa la bala le dio a uno de los asteroides 
			float p1x = (*((*it).a)).posix(), p1y = (*((*it).a)).posiy(), p2x = (*((*ite).a)).posix(), p2y = (*((*ite).a)).posiy();
			for (iter = municion.begin(); iter != municion.end(); iter++) {
				if (abs((*((*it).a)).posix() - ((*((*iter).a))).shoot.getPosition().x) < (*((*it).a)).radiof() - 10 && abs((*((*it).a)).posiy() - ((*((*iter).a))).shoot.getPosition().y) < (*((*it).a)).radiof() - 10) {
					if ((*((*it).a)).xplode == false) {
						score += 1; //si le das el score se te aumenta un punto y el texto de score se cambia
						tscore.setString(to_string(score));
					}
					(*((*it).a)) = asteroid(); //lo ago de nuevo porque si no susedeun error con las texturas y la explocion parecen unos platanos
					(*((*it).a)).ast.setTexture(&xplocion);//el asteroide explota
					(*((*it).a)).ast.setPosition(p1x, p1y);
					(*((*it).a)).xplode = true;
				}
			}
			
			//aqui el asteroide revisara si a chocado con algun otro asteroide, sin que este esté en forma de explocion, porque eso causa reacciones en cadena
			if (abs((*((*ite).a)).posix() - (*((*it).a)).posix()) < -20 + (*((*ite).a)).radiof() + (*((*it).a)).radiof() && abs((*((*ite).a)).posiy() - (*((*it).a)).posiy()) < -20 + (*((*ite).a)).radiof() + (*((*it).a)).radiof()) {
				if ((*((*it).a)).xplode == false) {
					(*((*it).a)) = asteroid();
					(*((*it).a)).ast.setTexture(&xplocion);
					(*((*it).a)).ast.setPosition(p1x, p1y);
					(*((*it).a)).xplode = true;
				}
				if ((*((*it).a)).xplode == false) {
					(*((*ite).a)) = asteroid();
					(*((*ite).a)).ast.setTexture(&xplocion);
					(*((*ite).a)).ast.setPosition(p2x, p2y);
					(*((*ite).a)).xplode = true;
				}
				
				
			}
		}
		if (it == la.end()) {
			break;
		}
	}
	if (stop == false) {
		player.setPosition(200 + x, 200 + y);
		player.setRotation(angulo);
	}
		for(it = la.begin(); it != la.end(); it++){//checa si un asteroide ya no existe o se a salido de la pantalla y lo saca de la lista, se borra por medio del smart pointer
			if ((*((*it).a)).exists == false || (*((*it).a)).posix() < -100 || (*((*it).a)).posiy() < -100 || (*((*it).a)).posix() > 800 || (*((*it).a)).posiy() > 800) {
				
				it = la.erase(it);
				
			}
			if (it == la.end())
			{
				break;
			}
			
		}
		for (iter = municion.begin(); iter != municion.end(); iter++) {
			(*((*iter).a)).update();
		}
	
}
void Game::shooti() {//cuando disparas con la barra espaciadora crea la bala con la posision y angulo de la nave
	if (timedis >= .8f){
		municion.push_front(sharepointer<disparo*>(new disparo()));
		iter = municion.begin();
		((*((*iter).a))).shoot.setPosition(player.getPosition().x, player.getPosition().y);
		((*((*iter).a))).shoot.setRotation(player.getRotation());
	}
	
}
void Game::render()
{// se borra todo lo que habiaen la pantalla y se vuelve a dibujar con sus nuevas posisiones
	window.clear();
	window.draw(fondo);
	window.draw(player);
	for (it = la.begin(); it != la.end(); it++)
	{
		window.draw((*((*it).a)).ast);
	}

	for (iter = municion.begin(); iter != municion.end(); iter++) {
		window.draw(((*((*iter).a))).shoot);
	}
	window.draw(tscore);
	if (stop == true) {
		window.draw(geimover); //si ya perdio se muestra el texto de gameover
	}
	window.display();
}
Game::~Game()
{
}
