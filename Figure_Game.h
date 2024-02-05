#pragma once
#include "Game.h"
class Figure_Game:public Game
{
public:
	Figure_Game(Settings settings);
	virtual void New_Game_Init();
};

