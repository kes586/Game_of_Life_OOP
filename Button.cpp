#include "Button.h"
extern Menu* menu;
Button::Button(initializer_list<float>button_location, initializer_list<float> Button_color, const char* text, initializer_list<float>text_location, initializer_list<float>text_color, double text_scale) {
	name = text;
	green = 0;
	yellow = 0;
	bot_loc = new float[4];
	bot_col = new float[4]; 
	text_loc = new float[2];
	text_col = new float[4];
	sc = text_scale;
	int i = 0;
	for (auto& x : button_location) {
		bot_loc[i] = x;
		i++;
	}
	i = 0;
	for (auto& x : Button_color) {
		bot_col[i] = x;
		i++;
	}
	i = 0;
	for (auto& x : text_location) {
		text_loc[i] = x;
		i++;
	}
	i = 0;
	for (auto& x : text_color) {
		text_col[i] = x;
		i++;
	}
}
Button::~Button() {

}
void Button::Quads(int x1, int y1, int x2, int y2) {
	glBegin(GL_QUADS);
	glVertex3f(x1, y1, 0);
	glVertex3f(x1, y2, 0);
	glVertex3f(x2, y2, 0);
	glVertex3f(x2, y1, 0);
	glEnd();
}
void Button::Draw_Button() {
	if (menu->settings.user && name == "  User\nSettings")
		glColor4f(bot_col[2], bot_col[1], bot_col[0], bot_col[3]);
	else if (menu->settings.user && name != "Start Auto Game" && name != "Start User Game" && name != "Exit") {
		glColor4f(bot_col[2], bot_col[1], bot_col[0], bot_col[3]);
		if (this->yellow)
			glColor4f(1, 1, 1, 1);
	}
	else
		glColor4f(bot_col[0], bot_col[1], bot_col[2], bot_col[3]);
	if (this->green)
		glColor3f(0, 1, 0);
	
	glScalef(sc,sc,sc);
	Quads(bot_loc[0], bot_loc[1], bot_loc[2], bot_loc[3]);
	glColor4f(text_col[0], text_col[1], text_col[2], text_col[3]);
	
	menu->num_quads = stb_easy_font_print(text_loc[0], text_loc[1], (char*)name.c_str(), NULL,menu->buffer, sizeof(menu->buffer));
	glDrawArrays(GL_QUADS, 0, menu->num_quads * 4);
}
