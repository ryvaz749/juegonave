#pragma once
#include <SFML/Graphics.hpp>
class xplode
{
private:
	
public:
	float tiempo;
	bool exists;
	sf::CircleShape boom;
	xplode();
	~xplode();
	void update(sf::Time deltatime);
};

