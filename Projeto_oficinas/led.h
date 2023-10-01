#pragma once

#include "stdafx.h"

class led
{
private:
	sf::CircleShape LED;
	sf::Vector2f pos;
	int cor;
	bool ligado;
public:
	led(int cor, sf::Vector2f pos = sf::Vector2f(0.f, 0.f), bool ligado = false);
	~led();

	sf::CircleShape getfigura();
	bool getligado();
	void setligado(bool ligado);

	void setpos(sf::Vector2f pos);
	sf::Vector2f getpos();
};