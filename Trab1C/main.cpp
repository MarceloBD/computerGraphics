#include "main.hpp"

const GLint WINDOW_WIDTH = 800;
const GLint WINDOW_HEIGHT = 600;
const GLchar TITLE[30] = "This is a black spider";
GLint screen_width, screen_height;
GLint positionx, positiony;
/*Point::Point (GLint x, GLint y){
	this->x = x;
	this->y = y;
}

Ellipse::Ellipse (Point center, GLfloat xRadius, GLfloat yRadius){
	this->center = center;
	this->xRadius = xRadius;
	this->yRadius = yRadius;
}

Leg::Leg (std::vector<Point> articulationPosition){
	this->articulationPosition = articulationPosition;
}

Spider::Spider(Point initialPos){
	//creatubg the spider from initial_pos
	Ellipse *cephalotorax = new Ellipse(initialPos, 10.0f, 12.5f); 
	this->cephalotorax = *cephalotorax;
	Point* p = new Point(initialPos.x, initialPos.y + 30.0f);
	Ellipse *abdomen = new Ellipse(*p, 15.0f, 20.0f);
	this->abdomen = *abdomen;
	GLfloat rx = this->cephalotorax.xRadius;
	GLfloat ry = this->cephalotorax.yRadius;
	GLfloat x = (GLfloat)this->cephalotorax.center.x;
	GLfloat y = (GLfloat)this->cephalotorax.center.y;
	//calculating the legs positions
	/*for (int i = 0; i < 8; i ++){
		std::vector<Point*> positions(4);
		positions[0] = new Point(x + rx*cos(2*PI*i/8), y + ry*cos(2*PI*i/8));
		positions[1] = new Point(x + rx*cos(PI/6));
		positions[2] = new Point(x + rx*cos(PI/4));
	}TODO: finish legs positions */
//}

void mouseListener(GLint button, GLint action, GLint x, GLint y) {
  switch (button) {
    case GLUT_LEFT_BUTTON: {
     	std::cout<<"Esquerda";
      //	Model *test = static_cast<Model*>(model);
      //	test->moveSpider(x, y);
  //    	init();


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

void init() {
  glClearColor(1.0, 1.0, 1.0, 1.0);     
  glMatrixMode(GL_PROJECTION);
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  glOrtho(0.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, 0.0f, 1.0f);
  glFlush();
}

void view(int argc, char **argv) {

	glutInit(&argc, argv);  
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);   

  screen_width  = glutGet(GLUT_SCREEN_WIDTH),
  screen_height = glutGet(GLUT_SCREEN_HEIGHT);  
  
  positionx = (screen_width-WINDOW_WIDTH)/2;
  positiony = (screen_height-WINDOW_HEIGHT)/2;

  glutInitWindowPosition(positionx, positiony);  //Utilizada para definir a posição inicial da janela, sendo que os parâmetros representam a posição do canto superior esquerdo
 	glutInitWindowSize(WINDOW_WIDTH, WINDOW_WIDTH);                                                 // Define a largura e altura da janela
  glutCreateWindow(TITLE);                             // Cria a janela, sendo que o parâmetro será o título dela
  
  init();                                                  
  
}




int main(int argc, char **argv) {
	view(argc, argv);
	glutMouseFunc(mouseListener);
	
	glutMainLoop();
	return 1; 
}