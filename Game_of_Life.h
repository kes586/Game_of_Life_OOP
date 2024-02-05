#pragma once
#include <glut.h>
class Game_of_Life
{
public:
	virtual void Start_Play()= 0;
	virtual void Reshape(int w, int h) = 0;
	
};
extern "C" void Reshape_Window(int width, int height);


