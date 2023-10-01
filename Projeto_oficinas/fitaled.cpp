#include "FitaLED.h"

FitaLED::FitaLED(int num) :
    num(num), tamanho(N_LEDS)
{
    led* l;
    for (int i = 0; i < tamanho; i++)
    {
        l = new led(num, sf::Vector2f(POSCOLUNA + num * DISTANCIA_LED, (i * DISTANCIA_LED) - 800.f));
        LEDs.push_back(l);
    }
}

FitaLED::~FitaLED()
{
    for (int i = 0; i < tamanho; i++)
    {
        delete LEDs[i];
    }
}

led* FitaLED::getleds(int index)
{
    return LEDs[index];
}