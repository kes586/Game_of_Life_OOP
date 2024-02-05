#pragma once
#include <string>
#include<glut.h>
#include "Menu.h"
using namespace std;
class Button
{
	friend class Menu;
public:
	Button(initializer_list<float>button_location,initializer_list<float> Button_color, const char* text, initializer_list<float>text_location, initializer_list<float>text_color,double text_scale);
	~Button();
private:
	bool green, yellow;
	string name;
	float* bot_loc, * bot_col, * text_loc, * text_col;
	double sc;
	void Draw_Button();
	static void Quads(int x1, int y1, int x2, int y2);
};

