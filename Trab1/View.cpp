#include "View.hpp"

View::View(int argc, char **argv) {

	glutInit(&argc, argv);  
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);   

	screen_width  = glutGet(GLUT_SCREEN_WIDTH),
  	screen_height = glutGet(GLUT_SCREEN_HEIGHT);  
  
  	glutInitWindowPosition(POSITIONX, POSITIONY);  //Utilizada para definir a posição inicial da janela, sendo que os parâmetros representam a posição do canto superior esquerdo
 	glutInitWindowSize(WINDOW_WIDTH, WINDOW_WIDTH);                                                 // Define a largura e altura da janela
  	glutCreateWindow(TITLE);                             // Cria a janela, sendo que o parâmetro será o título dela
  
 // 	init();                                                  
  /*	glutDisplayFunc(draw_test);
  
  	glutMouseFunc(mouse_test);
 	glutPassiveMotionFunc(mouse_test2);
  	glutMotionFunc(mouse_test3);
  
  	glutKeyboardFunc(keybord_test);
  	glutSpecialFunc(keybord_test2);
  

  	test_create_menu();
  	*/glutMainLoop();

}

View::~View() {

}