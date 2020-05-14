#include "Player.h"
#include "utils.h"

Player::Player()
{
	angle = 0;
	x = 50;
	y = 50;
}

void Player::rotate(float angle)
{
	this->angle += angle;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	
	
}