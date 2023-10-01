#pragma once

#include "stdafx.h"
#include "T_class.h"
#include "GerEventos.h"
#include "FitaLED.h"

namespace Estados
{
    class Fase : public T_class
    {
    private:
        float bpm;
        sf::CircleShape marcador;
        sf::Music musica;
        std::queue<int> fila_desenho;
        Gerenciadores::GerEventos ge;
        std::vector <FitaLED*> fitas;
        std::vector <std::queue<int>*> faixa;
        std::queue<char>* inputs;
        sf::RenderWindow janela;
    public:
        Fase();
        ~Fase();

        void executar();
        bool carregarFaixa(std::string endereco);
        void girarEsteira();
        void verificarInputs();
        void verificarAcerto(int fita);
        void desenhar();
        void tocar();
        void atualizarLeds(int index, int led);
    };
}
