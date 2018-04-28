//TODO: ifndef
#ifndef _GL

#define _GL
#include <GL/glut.h>
#include <iostream>

#endif

#include <vector>

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
		Point(){};
};


class Ellipse{
	public:
		Point center;
		GLfloat x_radius;
		GLfloat y_radius;
		Ellipse(Point center, GLfloat x_radius, GLfloat y_radius);
		Ellipse(){};
};


class Leg{
	public:
		std::vector<Point> articulation_position;
		Leg(std::vector<Point> articulation_position);
		Leg(){};
};

class Spider{
	public:
		Ellipse cephalotorax;
		Ellipse abdomen;
		std::vector<Leg> legs;
		Spider(Point initial_pos);
		void Move(Point destination);
};