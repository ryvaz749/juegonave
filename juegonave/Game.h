#pragma once
#include <SFML/Graphics.hpp>
#include "asteroid.h"
#include "xplode.h"
#include "disparo.h"
using namespace std;
class Game
{
private:
	bool up, down, right, left,freno;
	float x, y, velx, vely, giro, giroinv,angulo,pi,radio,asteroidrotation,tiempo,timedis;
	int numast,numboom,numdis;
	void event();
	void update(sf::Time deltatime);
	void render();
	void shooti();
	void input(sf::Keyboard::Key, bool press);
	sf::RenderWindow window;
	sf::RectangleShape fondo,player;
	sf::FloatRect boundary;
	disparo municion[5];
	

	asteroid  assets[160],prueba;

	bool stop,pause;
	
public:
	sf::Texture nave, asteroide, xplocion,fond;
	void run();
	Game();
	~Game();
};

