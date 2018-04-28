#include "View.hpp"

View::View(int argc, char **argv) {

	glutInit(&argc, argv);  
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);   

	screen_width  = glutGet(GLUT_SCREEN_WIDTH),
  screen_height = glutGet(GLUT_SCREEN_HEIGHT);  
  
  positionx = (screen_width-WINDOW_WIDTH)/2;
  positiony = (screen_height-WINDOW_HEIGHT)/2;

  glutInitWindowPosition(positionx, positiony);  //Utilizada para definir a posição inicial da janela, sendo que os parâmetros representam a posição do canto superior esquerdo
 	glutInitWindowSize(WINDOW_WIDTH, WINDOW_WIDTH);                                                 // Define a largura e altura da janela
  glutCreateWindow(TITLE);                             // Cria a janela, sendo que o parâmetro será o título dela
  
  this->init();                                                  
  
}

void View::init() {
  glClearColor(1.0, 1.0, 1.0, 1.0);     
  glMatrixMode(GL_PROJECTION);
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  glOrtho(0.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, 0.0f, 1.0f);
  glFlush();
}



View::~View() {

}