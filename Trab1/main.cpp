#include "main.hpp"


int main(int argc, char **argv) {

	View *view = new View(argc, argv);
	Controller *controller = new Controller(view);

	return 1; 
}