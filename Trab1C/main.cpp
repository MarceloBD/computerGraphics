#include "main.hpp"
#include <cstdlib>
#include <math.h>
#include <iostream>
#include <GL/glut.h>
#include<unistd.h>
#define PI 3.14159265

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

void DrawLine(Point start,Point end){
  float m = (start.y-end.y)/(start.x-end.x);
  if(m>1||m<-1){
    m = (start.x-end.x)/(start.y-end.y);
    for(float i = start.y;i<end.y;i++){
      glBegin(GL_POINTS);
        glVertex2f((i-start.y)*m+start.x,i);
      glEnd();
    }
    for(float i = start.y;i>end.y;i--){
      glBegin(GL_POINTS);
        glVertex2f((i-start.y)*m+start.x,i);
      glEnd();
    }
  }else{
    for(float i = start.x;i<end.x;i++){
      glBegin(GL_POINTS);
        glVertex2f(i,(i-start.x)*m+start.y);
      glEnd();
    }
    for(float i = start.x;i>end.x;i--){
      glBegin(GL_POINTS);
        glVertex2f(i,(i-start.x)*m+start.y);
      glEnd();
    }
  }
}

void DrawLeg(Leg leg){
  float points = 3000.0;
  float art_size = 50;
  float ang = leg.ang;
  Point reference = leg.initialPos;
  for(int i=0;i<leg.arts;i++){
    DrawLine(reference,Point(reference.x+art_size*cos(ang*(PI/180))*leg.side,reference.y+art_size*sin(ang*(PI/180))));
    reference = Point(reference.x+art_size*cos(ang*(PI/180))*leg.side,reference.y+art_size*sin(ang*(PI/180)));
    art_size /= 2;
    ang += 30;
  }
}

void DrawEllipse(Ellipse ellipse){
  float points = 3000.0;
  for(float i = 0.0;i<points;i++){
    float ang_sin = sin((i/points)*(360)*(PI/180));
    float ang_cos = cos((i/points)*(360)*(PI/180));
    float new_x = ellipse.center.x + ellipse.xRadius*ang_cos;
    float new_y = ellipse.center.y + ellipse.yRadius*ang_sin;
    glBegin(GL_POINTS);
      glVertex2f(new_x,new_y);
    glEnd();
  }
}

void EmptyCallback(){

}

void DrawSpider(Spider *spider){
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0,0.0,0.0);
  glPointSize(3.0);
  DrawEllipse(spider->cephalotorax);
  DrawEllipse(spider->abdomen);
  for(int i=0;i<8;i++){
    DrawLeg(spider->legs[i]);
  }
  glFlush();
}




int main(int argc, char **argv) {
  Spider *spider = new Spider(Point(0,0));
	view(argc, argv);
	glutMouseFunc(mouseListener);
	glutDisplayFunc(EmptyCallback);
  glMatrixMode(GL_MODELVIEW);

  for(int i=0;i<360;i++){
    glPushMatrix();
    //glTranslatef(-300.0, -300.0, 0.0);
    glRotatef(i,0.0,0.0,1.0);
    glTranslatef(300.0, 300.0, 0.0);
    DrawSpider(spider);
    glPopMatrix();
    usleep(50 * 1000);
  }




  //glTranslatef(-300.0, -300.0, 0.0);
  //glRotatef(45.0,0.0,0.0,1.0);
  //DrawSpider(spider);
  //glPopMatrix();





	glutMainLoop();
	return 1;
}
