#pragma once

#include "stdafx.h"
#include "led.h"

class FitaLED
{
private:
	std::vector <led*> LEDs;
	int tamanho;
	int num;
public:
	FitaLED(int num);
	~FitaLED();
	led* getleds(int index);
};