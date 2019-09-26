#pragma once
#include <SFML/Graphics.hpp>
#include "asteroid.h"
#include "xplode.h"
#include "disparo.h"
#include <list>
#include "sharepointer.h"
using namespace std;
class Game
{
private:
	bool up, down, right, left,freno;
	float x, y, velx, vely, giro, giroinv,angulo,pi,radio,asteroidrotation,tiempo,timedis;
	int numboom,numdis;
	void event();
	void update(sf::Time deltatime);
	void render();
	void shooti();
	void input(sf::Keyboard::Key, bool press);
	sf::RenderWindow window;
	sf::RectangleShape fondo,player;
	sf::FloatRect boundary;
	list<sharepointer<asteroid*>>::iterator it,ite;
	list<sharepointer<asteroid*>> la;
	list<sharepointer<disparo*>> municion;
	list<sharepointer<disparo*>>::iterator iter;
	asteroid  prueba;

	bool stop,pause,restart;
	
public:
	int score = 0;
	sf::Text tscore,geimover;
	sf::Font fuente;
	sf::Texture nave, asteroide, xplocion,fond;
	void run();
	Game();
	~Game();
};

