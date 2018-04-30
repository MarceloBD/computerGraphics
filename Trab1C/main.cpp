#include "main.hpp"

Spider *spider;

void mouseListener(GLint button, GLint action, GLint x, GLint y) {
  switch (button) {
    case GLUT_LEFT_BUTTON: {
     	std::cout<<"Esquerda";
      Point dest = Point(x,y);
      float ang = 0;
      if(dest.x>=spider->position.x&&dest.y<=spider->position.y){
        ang = asin((spider->position.y-dest.y)/sqrt(pow(dest.x-spider->position.x,2)+pow(dest.y-spider->position.y,2)))*(180/M_PI);
      }
      else if(dest.x<spider->position.x&&dest.y<=spider->position.y){
        ang = 90+acos((spider->position.y-dest.y)/sqrt(pow(dest.x-spider->position.x,2)+pow(dest.y-spider->position.y,2)))*(180/M_PI);
      }
      else if(dest.x<spider->position.x&&dest.y>spider->position.y){
        ang = -270+acos((spider->position.y-dest.y)/sqrt(pow(dest.x-spider->position.x,2)+pow(dest.y-spider->position.y,2)))*(180/M_PI);
      }
      else if(dest.x>=spider->position.x&&dest.y>spider->position.y){
        ang = asin((spider->position.y-dest.y)/sqrt(pow(dest.x-spider->position.x,2)+pow(dest.y-spider->position.y,2)))*(180/M_PI);
      }

      if(isfinite(ang)){
        spider->Rotate(-ang+90-spider->angle);
        spider->Move(Point(x,y));
      }

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
    spider->Rotate(0.1);
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
 	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);                                                 // Define a largura e altura da janela
  glutCreateWindow(TITLE);                             // Cria a janela, sendo que o parâmetro será o título dela

  init();

}







void EmptyCallback(){

}






int main(int argc, char **argv) {
  spider = new Spider(Point(400,300));
	view(argc, argv);
	glutMouseFunc(mouseListener);
	glutDisplayFunc(EmptyCallback);
  glMatrixMode(GL_MODELVIEW);
  spider->Rotate(45);
  spider->Move(Point(100,200));
  spider->Rotate(45);
  spider->Move(Point(100,400));
	glutMainLoop();
	return 1;
}
