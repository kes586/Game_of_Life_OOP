#include "Menu.h"
int main(int argc, char** argv) {
	std::unique_ptr<Menu>menu(new Menu);
	menu->Start_Play();
}