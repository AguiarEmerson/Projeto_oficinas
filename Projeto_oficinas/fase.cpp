#include "Fase.h"


namespace Estados
{
    Fase::Fase() :
        ge(), marcador(RAIO_LED), inputs(ge.getFila()), bpm(0), janela(sf::VideoMode(LARGURA_TELA, COMPRIMENTO_TELA), "Guitar Healer")
    {
        janela.setFramerateLimit(60);

        std::queue<int>* fila;
        for (int i = 0; i < N_FITAS; i++)
        {
            fila = new std::queue<int>;
            faixa.push_back(fila);
        }

        FitaLED* aux;
        for (int i = 0; i < N_FITAS; i++) {
            aux = new FitaLED(i);
            fitas.push_back(aux);
        }

        carregarFaixa("Faixa.txt");

        for (int i = 0; i < N_FITAS; i++) {
            atualizarLeds(0, i);
            atualizarLeds(1, i);
            atualizarLeds(2, i);
            atualizarLeds(3, i);
        }
    }

    Fase::~Fase()
    {
        for (int i = 0; i < N_FITAS; i++) {
            delete fitas[i];
            delete faixa[i];
        }
    }

    bool Fase::carregarFaixa(std::string endereco)
    {
        std::ifstream arquivo(endereco);

        if (!arquivo)
        {
            std::cout << "Arquivo nao encontrado" << std::endl;
            return false;
        }
        std::string linha;

        std::getline(arquivo, linha);
        bpm = (float)stoi(linha);

        for (int i = 0; i < N_FITAS; i++) {
            std::getline(arquivo, linha);
            for (int j = 0; linha[j] != '\0'; j++) {
                int aux = linha[j];
                faixa[i]->push(aux - 48);
            }
        }
        arquivo.close();
        return true;
    }

    void Fase::girarEsteira()
    {
        while (!terminar)
        {
            for (int i = 0; i < N_LEDS; i++) { // dessa forma n fica tão lagado
                fitas[0]->getleds(i)->setpos(fitas[0]->getleds(i)->getpos() + sf::Vector2f(0.f, bpm));
                if (fitas[0]->getleds(i)->getpos().y >= COMPRIMENTO_TELA)
                {
                    fitas[0]->getleds(i)->setpos(sf::Vector2f(fitas[0]->getleds(i)->getpos().x, -SOBRA));
                    atualizarLeds(0, i);

                    //se chega aqui ligado entao errou
                }
                fitas[1]->getleds(i)->setpos(fitas[1]->getleds(i)->getpos() + sf::Vector2f(0.f, bpm));
                if (fitas[1]->getleds(i)->getpos().y >= COMPRIMENTO_TELA)
                {
                    fitas[1]->getleds(i)->setpos(sf::Vector2f(fitas[1]->getleds(i)->getpos().x, -SOBRA));
                    atualizarLeds(1, i);
                    //se chega aqui ligado entao errou
                }
                fitas[2]->getleds(i)->setpos(fitas[2]->getleds(i)->getpos() + sf::Vector2f(0.f, bpm));
                if (fitas[2]->getleds(i)->getpos().y >= COMPRIMENTO_TELA)
                {
                    fitas[2]->getleds(i)->setpos(sf::Vector2f(fitas[2]->getleds(i)->getpos().x, -SOBRA));
                    atualizarLeds(2, i);
                    //se chega aqui ligado entao errou
                }
                fitas[3]->getleds(i)->setpos(fitas[3]->getleds(i)->getpos() + sf::Vector2f(0.f, bpm));
                if (fitas[3]->getleds(i)->getpos().y >= COMPRIMENTO_TELA)
                {
                    fitas[3]->getleds(i)->setpos(sf::Vector2f(fitas[3]->getleds(i)->getpos().x, -SOBRA));
                    atualizarLeds(3, i);
                    //se chega aqui ligado entao errou
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        }
    }

    void Fase::verificarInputs()
    {
        char rcpt;

        while (!terminar)
        {
            if (!(inputs->empty()))
            {
                rcpt = inputs->front();
                inputs->pop();
                switch (rcpt)
                {
                case '0':
                    fila_desenho.push(0);
                    verificarAcerto(0);
                    break;
                case '1':
                    fila_desenho.push(1);
                    verificarAcerto(1);
                    break;
                case '2':
                    fila_desenho.push(2);
                    verificarAcerto(2);
                    break;
                case '3':
                    fila_desenho.push(3);
                    verificarAcerto(3);
                    break;
                }
            }
        }
    }

    void Fase::verificarAcerto(int fita)
    {
        for (int i = 0; i < N_LEDS; i++) {
            if ((fitas[fita]->getleds(i)->getpos().y + RAIO_LED >= DISTANCIA_MARCADOR) && (fitas[fita]->getleds(i)->getpos().y + RAIO_LED <= DISTANCIA_MARCADOR + RAIO_LED))
            {
                fitas[fita]->getleds(i)->setligado(false);
                //marcar ponto
            }
        }
    }

    void Fase::desenhar()
    {
        sf::RectangleShape linha(sf::Vector2f(600.f, 1.f));
        linha.setPosition(sf::Vector2f(0.f, 500.f));
        janela.draw(linha);
        for (int i = 0; i < N_LEDS; i++) {
            if (fitas[0]->getleds(i)->getligado()) {
                janela.draw(fitas[0]->getleds(i)->getfigura());
            }
            if (fitas[1]->getleds(i)->getligado()) {
                janela.draw(fitas[1]->getleds(i)->getfigura());
            }
            if (fitas[2]->getleds(i)->getligado()) {
                janela.draw(fitas[2]->getleds(i)->getfigura());
            }
            if (fitas[3]->getleds(i)->getligado()) {
                janela.draw(fitas[3]->getleds(i)->getfigura());
            }
        }
        while (!fila_desenho.empty()) {
            int caso = fila_desenho.front();
            marcador.setPosition(sf::Vector2f(POSCOLUNA + caso * DISTANCIA_LED, DISTANCIA_MARCADOR));
            janela.draw(marcador);
            fila_desenho.pop();
        }
    }

    void Fase::atualizarLeds(int index, int led)
    {
        if (!faixa[index]->empty()) {
            fitas[index]->getleds(led)->setligado(faixa[index]->front());
            faixa[index]->pop();
        }
        else {
            std::cout << "ACABOU A FAIXA \n";
        }
    }

    void Fase::tocar()
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(11500));
        if (!musica.openFromFile("Super_Mario_Bros.ogg"))
        {
            std::cout << "ERRO AO CARREGAR A MUSICA" << std::endl;
        }
        musica.setVolume(VOLUME);
        musica.play();
    }

    void Fase::executar()
    {
        std::thread girar(&Fase::girarEsteira, this);
        std::thread atInpts(&Fase::verificarInputs, this);
        std::thread evInputs(&Gerenciadores::GerEventos::captarInputs, &ge);
        std::thread music(&Fase::tocar, this);
        while (janela.isOpen())
        {
            sf::Event event;
            while (janela.pollEvent(event))
                if (event.type == sf::Event::Closed)
                {
                    terminar = true;
                    girar.join();
                    atInpts.join();
                    evInputs.join();
                    music.join();
                    janela.close();
                }
            janela.clear();
            desenhar();
            janela.display();
        }
    }

}
