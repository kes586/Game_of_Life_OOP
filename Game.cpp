#include "Game.h"
Game* game;
void Reshape_Game_Window(int width, int height) {
	game->Reshape(width, height);
}
void Game::Start_Play(){
	game = this;
	//delete menu;
	glutDestroyWindow(1);
	glutInitWindowSize(this->Xwindow, this->Ywindow);
	glutInitWindowPosition(0, 5);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutCreateWindow("Game of Life");
	this->New_Game_Init();
	glutDisplayFunc(Game::Main_Drawing_Loop);
	this->Timer(0);
	glutMouseFunc(Game::Mouse_Pressed);
	glutMotionFunc(Game::Mouse_Pressed_Move);
	glutKeyboardFunc(Game::StandartKeybord);
	glutSpecialFunc(Game::SpecialKeybord);
	glutReshapeFunc(Reshape_Game_Window);
	glutMainLoop();
}
void Game::Main_Drawing_Loop() {
	glPointSize(game->pixel_raz);
	bool* p = game->main_array;
	bool* pM = game->main_array + game->Xlen * game->Ylen;
	for (int i = 0; p < pM; p++, i++) {
		if (*p)
			glColor3f(rand() % 2, rand() % 2, rand() % 2);
		else
			glColor3f(0, 0, 0);
		glBegin(GL_POINTS);
		glVertex2f(i / game->Ylen * game->pixel_raz, i % game->Ylen * game->pixel_raz);
		glEnd();
	}
	int i, j;
	if (game->pixel_raz == 10) {
		i = 6;
		j = 6;
	}
	else if (game->pixel_raz == 5) {
		i = 3;
		j = 3;
	}
	
	if (game->pixel_raz == 5 || game->pixel_raz == 10) {
		glColor3f(0.2, 0.2, 0.2);
		glLineWidth(0.2);
		for (i; i <= game->Xwindow; i += game->pixel_raz) {
			glBegin(GL_LINES);
			glVertex2f(i, 0);
			glVertex2f(i, game->Ywindow);
			glEnd();
		}
		for (j; j <= game->Ywindow; j += game->pixel_raz) {
			glBegin(GL_LINES);
			glVertex2f(0, j);
			glVertex2f(game->Xwindow, j);
			glEnd();
		}
	}
	if (game->begin) {
		struct p* mass = new struct p[game->Xlen * game->Ylen * sizeof(struct p)];
		int t = 0;
		for (int i = 1; i < game->Ylen - 1; i++)
			for (int j = 1; j < game->Xlen - 1; j++)
			{
				int pos = j * game->Ylen + i;
				char sum = (char)(
					game->main_array[pos - game->Ylen - 1] + game->main_array[pos - game->Ylen] + game->main_array[pos - game->Ylen + 1] +
					game->main_array[pos - 1] + game->main_array[pos + 1] +
					game->main_array[pos + game->Ylen - 1] + game->main_array[pos + game->Ylen] + game->main_array[pos + game->Ylen + 1]);
				if (sum == 2 || sum == 3) {
					mass[t].life = game->main_array[pos];
					mass[t].sum = sum;
					mass[t].pos = pos;
					t++;
				}

			}
		memset(game->main_array, 0, game->Xlen * game->Ylen * sizeof(char));
		for (int i = 0; i < t; i++) {
			if (mass[i].life)
				game->main_array[mass[i].pos] = 1;
			else if (mass[i].sum == 3)
				game->main_array[mass[i].pos] = 1;
		}
		delete[]mass;
	}
	glutSwapBuffers();
}
void Game::Timer(int n) {
	game->Main_Drawing_Loop();
	glutTimerFunc(game->speed, Game::Timer, 0);
}
void Game::Reshape(int w, int h) {
	if (glutGet(GLUT_WINDOW_WIDTH) != game->Xwindow || glutGet(GLUT_WINDOW_HEIGHT) != game->Ywindow)
		glutReshapeWindow(game->Xwindow, game->Ywindow);
}
void Game::StandartKeybord(unsigned char key, int x, int y) {
	if (key == 32)
		Sleep(game->pause * 1000);
	if (key == 13) {
		if (!game->begin)
			game->begin = 1;
		else {
			Sleep(3000);
			delete[] game->main_array;
			exit(0);
		}
	}
}
void Game::SpecialKeybord(int key, int x, int y) {
	if (key == GLUT_KEY_UP && game->speed > 10)
		game->speed -= 10;
	if (key == GLUT_KEY_UP && game->speed < 10 && game->speed >= 2)
		game->speed--;
	if (key == GLUT_KEY_DOWN)
		game->speed += 10;
}

void Game::Mouse_Pressed_Move(int x, int y) {
	if (x / game->pixel_raz < 0 || y / game->pixel_raz < 0 || x / game->pixel_raz >= game->Xlen || y / game->pixel_raz >= game->Ylen)
		return;
	game->main_array[x / game->pixel_raz * game->Ylen + y / game->pixel_raz] = 1;
}

void Game::Mouse_Pressed(int button, int state, int x, int y) {
	if (x / game->pixel_raz < 0 || y / game->pixel_raz < 0 || x / game->pixel_raz >= game->Xlen || y / game->pixel_raz >= game->Ylen)
		return;
	if (button == GLUT_LEFT_BUTTON) {
		game->main_array[x / game->pixel_raz * game->Ylen + y / game->pixel_raz] = 1;
	}
}