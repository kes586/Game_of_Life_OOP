#pragma once
#include "Game.h"
class User_Game : public Game
{
public:
	User_Game(Settings settings);
	virtual void New_Game_Init();
};

