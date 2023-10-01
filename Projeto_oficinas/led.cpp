#include "led.h"

led::led(int cor, sf::Vector2f pos, bool ligado) :
	cor(cor), pos(pos), ligado(ligado)
{
	sf::CircleShape aux(RAIO_LED);
	switch (cor)
	{
	case(0):
		aux.setFillColor(sf::Color::Red);
		break;
	case(1):
		aux.setFillColor(sf::Color::Green);
		break;
	case(2):
		aux.setFillColor(sf::Color::Yellow);
		break;
	case(3):
		aux.setFillColor(sf::Color::Blue);
		break;
	}
	LED = aux;
	setpos(pos);
}

led::~led()
{
}

sf::CircleShape led::getfigura()
{
	return LED;
}

bool led::getligado()
{
	return ligado;
}

void led::setligado(bool on)
{
	ligado = on;
}

void led::setpos(sf::Vector2f posicao)
{
	pos = posicao;

	LED.setPosition(pos);
}

sf::Vector2f led::getpos()
{
	return pos;
}