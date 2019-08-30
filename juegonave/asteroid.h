#pragma once

#include <SFML/Graphics.hpp>
class asteroid
{
private:
	
	float pi;
public:
	bool exists,xplode;
	sf::FloatRect boundary;
	float angulo;
	sf::Texture aste;
	int direccion,angular,radio;
	sf::CircleShape ast;
	void update(sf::Time deltatime);
	float posix(),posiy(),radiof(),tiempo;
	asteroid();
	~asteroid();
};

