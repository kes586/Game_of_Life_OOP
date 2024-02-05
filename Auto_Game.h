#pragma once
#include "Game.h"
#include <time.h>
class Auto_Game: public Game
{
public:
	Auto_Game(Settings settings);
	virtual void New_Game_Init();
};

