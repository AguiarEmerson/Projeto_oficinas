#pragma once
// Classe base para as classe que ter�o threads concorrentes

class T_class
{
protected:
    static bool terminar;
public:
    T_class() {}
    ~T_class()
    {
        terminar = true;
    }
};
