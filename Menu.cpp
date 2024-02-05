#include "Menu.h"
//#include "Auto_Game.h"
Menu* menu;
Menu::Menu() {
	this->game = new Auto_Game(this->settings);
	num_quads = 0;
	flagok = 0;
	memset(buffer, 0, 10000);
	this->all_buttons = { {{ -80, -62, -27, -38 }, { 1, 1, 0,1 }, "  Auto\nSettings", { -75,-60 }, { 1,0,0,0 }, 0.8},
		{{ 28, -62, 82, -38 }, { 0, 1, 1,1 }, "  User\nSettings", { 35,-60 }, { 1,0,0,0 },1},
		{{ -126, -32, -68, -21 }, { 0.5, 0.5, 0.5,0.5 }, " 1530x800", {-127.5,-30}, { 1,0,0,0 }, 0.6},
		{{ -126, -19, -68, -9 }, {  0.5, 0.5, 0.5,0.5 }, " 1000x760", { -127.5,-17.5 }, { 1,0,0,0 }, 1},
		{{ -126, -7, -68, 2 }, {  0.5, 0.5, 0.5,0.5 }, " 800x600", { -123.5,-5 }, { 1,0,0,0 }, 1},
		{{ -50, -32, 0, -21 }, {  0.5, 0.5, 0.5,0.5 }, "High", { -35,-30 }, { 1,0,0,0 }, 1},
		{{ -50, -19, 0, -9 }, {  0.5, 0.5, 0.5,0.5 }, "Average", { -45,-17.5 }, { 1,0,0,0 }, 1},
		{{ -50, -7, 0, 3 }, { 0.5, 0.5, 0.5,0.5}, "Low", { -35,-5 }, { 1,0,0,0 }, 1},
		{{ 15, -32, 65, -21 }, {  0.5, 0.5, 0.5,0.5 }, "Big", { 33,-30 }, { 1,0,0,0 }, 1},
		{{ 15, -19, 65, -9 }, {  0.5, 0.5, 0.5,0.5 }, "Average", { 20,-17.5 }, { 1,0,0,0 }, 1},
		{{ 15, -7, 65, 3 }, {  0.5, 0.5, 0.5,0.5 }, "Small", { 30,-5 }, { 1,0,0,0 }, 1},
		{{ 78, -32, 125, -21 }, { 0.5, 0.5, 0.5,0.5 }, "3 c", { 95,-30 }, { 1,0,0,0 }, 1},
		{{ 78, -19, 125, -9 }, {  0.5, 0.5, 0.5,0.5 }, "5 c", { 95,-17.5 }, { 1,0,0,0 }, 1},
		{{ 78, -7, 125, 3 }, {  0.5, 0.5, 0.5,0.5 }, "10 c", { 90.5,-5 }, { 1,0,0,0 }, 1},
		{{ -45, 17, 50, 29 }, { 0, 1, 1,1 }, "Start Auto Game", { -40,20 }, { 1,0,0,0 }, 2.2},
		{{ -45, 30, 50, 42 }, { 0, 1, 1,1 }, "Start User Game", { -40,32.5 }, { 1,0,0,0 }, 1},
		{{ -45, 43, 50, 55 }, { 0, 1, 1,1 }, "Examples", { -18.5,45 }, { 1,0,0,0 }, 1},
		{{ -45, 56, 50, 68 }, { 0, 1, 1,1 }, "Exit", { -6.5,57.5 }, { 1,0,0,0 }, 1} };
};
void Menu::Cleanup() {
	for (auto& x : menu->all_buttons) {
		delete[]x.bot_col;
		delete[]x.bot_loc;
		delete[]x.text_col;
		delete[]x.text_loc;
	}
	menu->all_buttons.clear();
}
void Reshape_Menu_Window(int width, int height) {
	menu->Reshape(width, height);
}
void Menu::Reshape(int w, int h) {
	if (glutGet(GLUT_WINDOW_WIDTH) != 500 || glutGet(GLUT_WINDOW_HEIGHT) != 500)
		glutReshapeWindow(500, 500);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-12.0, 12.0, -12.0, 12.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if (!this->flagok)
		glScalef(0.15, -0.15, 1);
	this->flagok = 1;
}
void Menu::Start_Play() {
	menu = this;
	int argc = 1;
	char* argv[1] = {(char*)""};
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(200, 200);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutCreateWindow("Game of Life");
	glutDisplayFunc(Menu::Menu_Drawing);
	glutReshapeFunc(Reshape_Menu_Window);
	glutPassiveMotionFunc(Menu::Button_color);
	glutMouseFunc(Menu::Choice);
	glutMainLoop();
}
void Menu::Menu_Drawing() {
	glPushMatrix();
	glColor3f(1, 1, 1);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 16, menu->buffer);
	glScalef(1, 1, 1);
	glColor3f(1, 1, 0);
	menu->num_quads = stb_easy_font_print(-35, -70, (char*)"GAME OF LIFE", NULL, menu->buffer, sizeof(menu->buffer));
	glDrawArrays(GL_QUADS, 0, menu->num_quads * 4);
	for (auto x : menu->all_buttons)
		x.Draw_Button();
	glScalef(0.8, 0.8, 0.8);
	menu->num_quads = stb_easy_font_print(-75, -30, (char*)"Window  Speed  Size  Pause", NULL, menu->buffer, sizeof(menu->buffer));
	glDrawArrays(GL_QUADS, 0, menu->num_quads * 4);
	glDisableClientState(GL_VERTEX_ARRAY);
	glPopMatrix();
	glutSwapBuffers();
}
void Menu::Button_color(int x, int y) {
	_asm {
		mov edx, x
		sub edx, 250
		mov x, edx
		mov edx, y
		sub edx, 250
		mov y, edx
	}
	if (Return_Button_Name(x, y) == "Auto Settings")
		menu->all_buttons[0].green = 1;
	else
		menu->all_buttons[0].green = 0;
	if (Return_Button_Name(x, y) == "User Settings")
		menu->all_buttons[1].green = 1;
	else
		menu->all_buttons[1].green = 0;
	if (Return_Button_Name(x, y) == "Auto Game")
		menu->all_buttons[14].green = 1;
	else
		menu->all_buttons[14].green = 0;
	if (Return_Button_Name(x, y) == "User Game")
		menu->all_buttons[15].green = 1;
	else
		menu->all_buttons[15].green = 0;
	if (Return_Button_Name(x, y) == "Examples")
		menu->all_buttons[16].green = 1;
	else
		menu->all_buttons[16].green = 0;
	if (Return_Button_Name(x, y) == "Exit")
		menu->all_buttons[17].green = 1;
	else
		menu->all_buttons[17].green = 0;
	glutPostRedisplay();

	if (menu->settings.user) {
		if (Return_Button_Name(x, y) == "1530x800")
			menu->all_buttons[2].green = 1;
		else
			menu->all_buttons[2].green = 0;
		if (Return_Button_Name(x, y) == "1000x760")
			menu->all_buttons[3].green = 1;
		else
			menu->all_buttons[3].green = 0;
		if (Return_Button_Name(x, y) == "800x600")
			menu->all_buttons[4].green = 1;
		else
			menu->all_buttons[4].green = 0;
		if (Return_Button_Name(x, y) == "speed10")
			menu->all_buttons[5].green = 1;
		else
			menu->all_buttons[5].green = 0;
		if (Return_Button_Name(x, y) == "speed50")
			menu->all_buttons[6].green = 1;
		else
			menu->all_buttons[6].green = 0;
		if (Return_Button_Name(x, y) == "speed200")
			menu->all_buttons[7].green = 1;
		else
			menu->all_buttons[7].green = 0;
		if (Return_Button_Name(x, y) == "pixel10")
			menu->all_buttons[8].green = 1;
		else
			menu->all_buttons[8].green = 0;
		if (Return_Button_Name(x, y) == "pixel5")
			menu->all_buttons[9].green = 1;
		else
			menu->all_buttons[9].green = 0;
		if (Return_Button_Name(x, y) == "pixel2")
			menu->all_buttons[10].green = 1;
		else
			menu->all_buttons[10].green = 0;
		if (Return_Button_Name(x, y) == "pause3")
			menu->all_buttons[11].green = 1;
		else
			menu->all_buttons[11].green = 0;
		if (Return_Button_Name(x, y) == "pause5")
			menu->all_buttons[12].green = 1;
		else
			menu->all_buttons[12].green = 0;
		if (Return_Button_Name(x, y) == "pause10")
			menu->all_buttons[13].green = 1;
		else
			menu->all_buttons[13].green = 0;
		glutPostRedisplay();
	}
}

void Menu::Choice(int btn, int state, int x, int y) {
	_asm {
		mov edx, x
		sub edx, 250
		mov x, edx
		mov edx, y
		sub edx, 250
		mov y, edx
	}

	if (state == GLUT_DOWN && btn == GLUT_LEFT_BUTTON) {
		if (Return_Button_Name(x, y) == "Auto Settings") {
			menu->settings.user = 0;
			menu->settings.Xwindow = 1280;
			menu->settings.Ywindow = 720;
			menu->settings.speed = 20;
			menu->settings.pixel_raz = 5;
			menu->settings.pause = 5;
			for (int i = 2; i < 14; i++) {
				menu->all_buttons[i].bot_col[0] = 0.5;
				menu->all_buttons[i].bot_col[1] = 0.5;
				menu->all_buttons[i].bot_col[2] = 0.5;
				menu->all_buttons[i].bot_col[3] = 0.5;
			}
			menu->all_buttons[16].bot_col[0] = 0;
			menu->all_buttons[16].bot_col[1] = 1;
			menu->all_buttons[16].bot_col[2] = 1;
			menu->all_buttons[16].bot_col[3] = 1;
		}
		if (Return_Button_Name(x, y) == "User Settings")
			menu->settings.user = 1;
		glutPostRedisplay();
		
		if (Return_Button_Name(x, y) == "Auto Game") {
			Auto_Game* auto_game = new Auto_Game(menu->settings);
			menu->game = auto_game;
			menu->settings.begin = 1;
		}
		if (Return_Button_Name(x, y) == "User Game") {
			User_Game* user_game = new User_Game(menu->settings);
			menu->game = user_game;
			menu->settings.begin = 1;
		}
		if (Return_Button_Name(x, y) == "Examples" && !menu->settings.user) {
			Figure_Game* figure_game = new Figure_Game(menu->settings);
			menu->game = figure_game;
			menu->settings.begin = 1;
		}
		if (menu->settings.begin) {
			menu->Cleanup();
			menu->game->Start_Play();
		}
		if (Return_Button_Name(x, y) == "Exit")
			exit(0);
		if (menu->settings.user) {
			for (int i = 2; i < 14; i++) {
				menu->all_buttons[i].bot_col[0] = 1;
				menu->all_buttons[i].bot_col[1] = 1;
				menu->all_buttons[i].bot_col[2] = 0;
				menu->all_buttons[i].bot_col[3] = 1;
			}
			menu->all_buttons[16].bot_col[0] = 0.5;
			menu->all_buttons[16].bot_col[1] = 0.5;
			menu->all_buttons[16].bot_col[2] = 0.5;
			menu->all_buttons[16].bot_col[3] = 0.5;
			if (Return_Button_Type(x) == "size button") {
				if (Return_Button_Name(x, y) == "1530x800") {
					menu->settings.Xwindow = 1530;
					menu->settings.Ywindow = 800;
					menu->all_buttons[2].yellow = 1;
				}
				else if (menu->all_buttons[3].yellow != 1|| menu->all_buttons[4].yellow != 1)
					menu->all_buttons[2].yellow = 0;
				if (Return_Button_Name(x, y) == "1000x760") {
					menu->settings.Xwindow = 1000;
					menu->settings.Ywindow = 760;
					menu->all_buttons[3].yellow = 1;
				}
				else if (menu->all_buttons[2].yellow != 1 || menu->all_buttons[4].yellow != 1)
					menu->all_buttons[3].yellow = 0;
				if (Return_Button_Name(x, y) == "800x600") {
					menu->settings.Xwindow = 800;
					menu->settings.Ywindow = 600;
					menu->all_buttons[4].yellow = 1;
				}
				else if (menu->all_buttons[2].yellow != 1 || menu->all_buttons[3].yellow != 1)
					menu->all_buttons[4].yellow = 0;
			}
			if (Return_Button_Type(x) == "speed button") {
				if (Return_Button_Name(x, y) == "speed10") {
					menu->settings.speed = 10;
					menu->all_buttons[5].yellow = 1;
				}
				else if (menu->all_buttons[6].yellow != 1 || menu->all_buttons[7].yellow != 1)
					menu->all_buttons[5].yellow = 0;
				if (Return_Button_Name(x, y) == "speed50") {
					menu->settings.speed = 50;
					menu->all_buttons[6].yellow = 1;
				}
				else if (menu->all_buttons[5].yellow != 1 || menu->all_buttons[7].yellow != 1)
					menu->all_buttons[6].yellow = 0;
				if (Return_Button_Name(x, y) == "speed200") {
					menu->settings.speed = 200;
					menu->all_buttons[7].yellow = 1;
				}
				else if (menu->all_buttons[5].yellow != 1 || menu->all_buttons[6].yellow != 1)
					menu->all_buttons[7].yellow = 0;
			}
			if (Return_Button_Type(x) == "pixel button") {
				if (Return_Button_Name(x, y) == "pixel10") {
					menu->settings.pixel_raz = 10;
					menu->all_buttons[8].yellow = 1;
				}
				else if (menu->all_buttons[9].yellow != 1 || menu->all_buttons[10].yellow != 1)
					menu->all_buttons[8].yellow = 0;
				if (Return_Button_Name(x, y) == "pixel5") {
					menu->settings.pixel_raz = 5;
					menu->all_buttons[9].yellow = 1;
				}
				else if (menu->all_buttons[8].yellow != 1 || menu->all_buttons[10].yellow != 1)
					menu->all_buttons[9].yellow = 0;
				if (Return_Button_Name(x, y) == "pixel2") {
					menu->game->pixel_raz = 2;
					menu->all_buttons[10].yellow = 1;
				}
				else if (menu->all_buttons[8].yellow != 1 || menu->all_buttons[9].yellow != 1)
					menu->all_buttons[10].yellow = 0;
			}
			if (Return_Button_Type(x) == "pause button") {
				if (Return_Button_Name(x, y) == "pause3") {
					menu->settings.pause = 3;
					menu->all_buttons[11].yellow = 1;
				}
				else if (menu->all_buttons[12].yellow != 1 || menu->all_buttons[13].yellow != 1)
					menu->all_buttons[11].yellow = 0;
				if (Return_Button_Name(x, y) == "pause5") {
					menu->settings.pause = 5;
					menu->all_buttons[12].yellow = 1;
				}
				else if (menu->all_buttons[11].yellow != 1 || menu->all_buttons[13].yellow != 1)
					menu->all_buttons[12].yellow = 0;
				if (Return_Button_Name(x, y) == "pause10") {
					menu->settings.pause = 10;
					menu->all_buttons[13].yellow = 1;
				}
				else if (menu->all_buttons[11].yellow != 1 || menu->all_buttons[12].yellow != 1)
					menu->all_buttons[13].yellow = 0;
			}
			if (menu->game !=NULL&& menu->settings.Xwindow && menu->settings.Ywindow && menu->settings.speed && menu->settings.pause && menu->settings.pixel_raz) {
				menu->settings.Xlen = menu->settings.Xwindow / menu->settings.pixel_raz;
				menu->settings.Ylen = menu->settings.Ywindow / menu->settings.pixel_raz;
			}
			glutPostRedisplay();
		}
	}
}

string Menu::Return_Button_Type(int x) {
	if (x > -190 && x < -102)
		return "size button";
	else if (x > 116 && x < 186)
		return "pause button";
	else if (x > 22 && x < 96)
		return "pixel button";
	else if(x > -75 && x < 0)
		return "speed button";
	return "";
}
string Menu::Return_Button_Name(int x, int y) {
	if (x > -203 && x<-70 && y>-155 && y < -95)
		return "Auto Settings";
	else if (x > 70 && x<205 && y>-155 && y < -95)
		return "User Settings";
	else if (x > -135 && x < 150 && y > 50 && y < 87)
		return "Auto Game";
	else if (x > -135 && x < 150 && y < 125 && y>90)
		return "User Game";
	else if (x > -135 && x < 150 && y < 158 && y>130)
		return "Examples";
	else if (x > -135 && x < 150 && y < 194 && y>165)
		return "Exit";
	else if (x > -190 && x<-102 && y>-50 && y < -33)
		return "1530x800";
	else if (x > -190 && x<-102 && y>-28 && y < -15)
		return "1000x760";
	else if (x > -190 && x<-102 && y>-12 && y < 3)
		return "800x600";
	else if (x > -75 && x <0 && y>-50 && y < -33)
		return "speed10";
	else if (x > -75 && x <0 && y>-28 && y < -15)
		return "speed50";
	else if (x > -75 && x <0 && y>-12 && y < 3)
		return "speed200";
	else if (x > 22 && x <96 && y>-50 && y < -33)
		return "pixel10";
	else if (x > 22 && x <96 && y>-28 && y < -15)
		return "pixel5";
	else if (x > 22 && x <96 && y>-12 && y < 3)
		return "pixel2";
	else if (x > 116 && x <186 && y>-50 && y < -33)
		return "pause3";
	else if (x > 116 && x <186 && y>-28 && y < -15)
		return "pause5";
	else if (x > 116 && x <186 && y>-12 && y < 3)
		return "pause10";
	return "";
}
