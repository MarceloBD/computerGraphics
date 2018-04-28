//TODO: ifndef
#ifndef _GL
#define _GL
#include <GL/glut.h>
#include <iostream>
#endif

class Model
{
	public:
		Model();
		~Model();
};

class Point{
	public:
		GLint x;
		GLint y;
		Point(GLint x, GLint y);
};


class Ellipse{
	public:
		Point center;
		GLfloat x_radius;
		GLfloat y_radius;
		Ellipse(Point center, GLfloat x_radius, GLfloat y_radius);
};


class Leg{
	public:
		Point *articulation_position;
		Leg(Point articulation_position);
};

class Spider{
	public:
		Ellipse cephalotorax;
		Ellipse abdomen;
		Leg legs[8];
		Spider();
		void Move(Point destination);
};