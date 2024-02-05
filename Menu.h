#pragma once
#include <Windows.h>
#include <stb_easy_font.h>
#include <string>
#include <vector>
#include "Auto_Game.h"
#include "Figure_Game.h"
#include "User_Game.h"
#include "Button.h"
#include "Settings.h"
#include "Game.h"
#include<memory>
using namespace std;
class Menu
{
	friend class Button;
public :
	Settings settings;
	Game* game;
	Menu();
	void Start_Play();
	void Reshape(int w, int h);
	vector<Button>all_buttons;
private:
	bool flagok;
	char buffer[10000];
	int num_quads;
	void Cleanup();
	static void Button_color(int x,int y);
	static void Menu_Drawing();
	static void Choice(int btn, int state, int x, int y);
	static string Return_Button_Name(int x, int y);
	static string Return_Button_Type(int x);
};
extern "C" void Reshape_Menu_Window(int width, int height);

