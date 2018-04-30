#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <iostream>
#include <GL/glut.h>
#include <unistd.h>

const GLint WINDOW_WIDTH = 800;
const GLint WINDOW_HEIGHT = 600;
const GLchar TITLE[30] = "This is a black spider";
GLint screen_width, screen_height;
GLint positionx, positiony;

void mouseListener(GLint button, GLint action, GLint x, GLint y);
void init();
void view(GLint argc, char **argv);
void emptyCallback();

class Point{
  public:
    GLfloat x,y;
    Point(GLint _x, GLint _y);
    Point(){}
};

class Ellipse{
	public:
		Point center;
		GLfloat xRadius;
		GLfloat yRadius;
		Ellipse(Point _center, GLfloat _xRadius, GLfloat _yRadius);
		Ellipse(){}
		void Draw();
};

class Leg{
	private:
		GLint start_ang;
	public:
		Point initialPos;
		GLint ang;
		GLint side;
		GLint arts;
		GLint direction;// direction = 1 for up, -1 for down
		Leg(Point _initialPos,GLint _side,GLint _arts, GLint _ang, GLint _direction);
		Leg(){}
		void DrawLine(Point start,Point end);
		void DrawLinePointX(Point start, GLint i, GLfloat m);
		void DrawLinePointY(Point start, GLint i, GLfloat m);
		void Draw();
		void Move();
};

class Spider{
	public:
		Point position;
		Ellipse cephalotorax;
		Ellipse abdomen;
		Leg legs[8];
		const GLint moveSpeed = 50;
		const GLint rotateSpeed = 100;
		GLfloat angle = 0;
		Spider(Point initialCoords);
		void Draw();
		void Move(Point dest);
//O *5 serve apenas para deixar o movimento mais suave (smooth) em angulos pequenos
		void Rotate(GLfloat _angle);
		void RotateStep(GLint i);
};