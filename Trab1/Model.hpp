//TODO: ifndef
#include <GL/glut.h>

class Point{
	public:
		GLfloat x;
		GLfloat y;
		Point(x,y);
}


class Ellipse{
	public:
		Point center;
		GLfloat x_radius;
		GLfloat y_radius;
		Ellipse(Point center, GLfloat x_radius, GLfloat y_radius);
}


class Leg{
	public:
		Point articulation_position*;
		Leg(Point articulation_position);
}

class Spider{
	public:
		Ellipse cephalotorax;
		Ellipse abdomen;
		Leg legs[8];
		Spider();
		void Move(Point destination);
}