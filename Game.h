#pragma once
//#include "Menu.h"
#include "Settings.h"
#include <glut.h>
#include <Windows.h>
class Game
{
public:
	int Xwindow, Ywindow;
	int speed, pixel_raz, pause, Xlen, Ylen, begin;
	bool* main_array;
	struct p {
		int life;
		int sum;
		int pos;
	};
	void Start_Play();
	void Reshape(int w, int h);
private:
	virtual void New_Game_Init()=0;
	static void Main_Drawing_Loop();
	static void Timer(int n);
	static void Mouse_Pressed(int button, int state, int x, int y);
	static void Mouse_Pressed_Move(int x, int y);
	static void SpecialKeybord(int key, int x, int y);
	static void StandartKeybord(unsigned char key, int x, int y);
};
extern "C" void Reshape_Game_Window(int width, int height);


