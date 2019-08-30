#pragma once
#include <SFML/Graphics.hpp>
class disparo
{
public:
	float pi = 3.1415926535897932384626433;
	sf::RectangleShape shoot;
	void update();
	disparo();
	~disparo();
};

