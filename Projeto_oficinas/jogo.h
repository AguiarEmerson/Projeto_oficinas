#pragma once

#include <SFML/Graphics.hpp>
#include "Fase.h"

class Jogo
{
private:
    Estados::Fase fase;
public:
    Jogo();
    ~Jogo();
    void executar();
};