#include "Controller.hpp"


Controller::Controller(View *view, Model *model) {
	this->view = view;
	this->model = model;
	/*	glutDisplayFunc(draw_test);
  */
  	glutMouseFunc(Controller::mouseListener);
// 	glutPassiveMotionFunc(mouse_test2);
 // 	glutMotionFunc(mouse_test3);
  
 // 	glutKeyboardFunc(keybord_test);
 // 	glutSpecialFunc(keybord_test2);
  

  //	test_create_menu();
  	std::cout<<"criando controller";
}

void Controller::init() {
	model->initSpider();
	model->drawSpider();
	glutMainLoop();
}
 


void Controller::mouseListener(GLint button, GLint action, GLint x, GLint y) {
  switch (button) {
    case GLUT_LEFT_BUTTON: {
     	std::cout<<"Esquerda";
      //	Model *test = static_cast<Model*>(model);
      //	test->moveSpider(x, y);
      	init();


      break;
    }
    case GLUT_MIDDLE_BUTTON: {
     	std::cout<<"Meio";
      break;
    }
    case GLUT_RIGHT_BUTTON: {
     	std::cout<<"Direita";
      break;
    }
	}
  	if (action == GLUT_DOWN) {
    	std::cout<<" preciona";
    }
    else {
    	std::cout<<"libera";

    }
    std::cout<<" em (x:"<<x<<", y:"<<y<<")\n";
}
