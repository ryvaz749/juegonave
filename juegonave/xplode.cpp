#include "xplode.h"
xplode::xplode()
{
	exists = true;
	tiempo = 0;
}
void xplode::update(sf::Time deltatime) {
	tiempo += deltatime.asSeconds();
	if (tiempo > 3) {
		exists = false;
	}
}
xplode::~xplode() {

}



