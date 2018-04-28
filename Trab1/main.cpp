#include "main.hpp"


int main(int argc, char **argv) {

	Model *model = new Model();
	View *view = new View(argc, argv);
	Controller *controller = new Controller(view, model);


	glutMainLoop();

	return 1; 
}