#include "main.hpp"


int main(int argc, char **argv) {

	View *view = new View(argc, argv);
	Model *model = new Model(view);
	Controller *controller = new Controller(view, model);
	controller->init();

	glutMainLoop();

	return 1; 
}