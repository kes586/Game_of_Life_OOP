#include "Auto_Game.h"

void Auto_Game::New_Game_Init() {
	srand(time(NULL));
	this->main_array = new bool[this->Xlen * this->Ylen * sizeof(bool)];
	if (this->main_array == NULL)
		exit(0);
	for (int i = 0; i < this->Xlen * this->Ylen; i++)
		this->main_array[i] = rand() % 2;
	this->begin = 1;
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, this->Xwindow, this->Ywindow, 0);
}

Auto_Game::Auto_Game(Settings settings) {
	Xwindow = settings.Xwindow;
	Ywindow = settings.Ywindow;
	Xlen = settings.Xlen;
	Ylen = settings.Ylen;
	begin = settings.begin;
	pause = settings.pause;
	speed = settings.speed;
	pixel_raz = settings.pixel_raz;
};