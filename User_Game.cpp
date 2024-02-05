#include "User_Game.h"
void User_Game::New_Game_Init() {
	this->main_array = new bool[this->Xlen * this->Ylen * sizeof(bool)];
	memset(this->main_array, 0, this->Xlen * this->Ylen);
	if (this->main_array == NULL)
		exit(0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, this->Xwindow, this->Ywindow, 0);
}
User_Game::User_Game(Settings settings) {
	Xwindow = settings.Xwindow;
	Ywindow = settings.Ywindow;
	Xlen = settings.Xlen;
	Ylen = settings.Ylen;
	begin = settings.begin;
	pause = settings.pause;
	speed = settings.speed;
	pixel_raz = settings.pixel_raz;
};
