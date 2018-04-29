#include <GL/glut.h>
#include <iostream>
#include <vector>

class Point{
	public:
		GLint x;
		GLint y;
		Point(GLint x, GLint y);
		Point();
};


class Ellipse{
	public:
		Point center;
		GLfloat xRadius;
		GLfloat yRadius;
		Ellipse(Point center, GLfloat xRadius, GLfloat yRadius);
		Ellipse();
};


class Leg{
	public:
		std::vector<Point> articulationPosition;
		Leg(std::vector<Point> articulationPosition);
		Leg();
};

class Spider{
	public:
		Ellipse cephalotorax;
		Ellipse abdomen;
		std::vector<Leg> legs;
		Spider(Point initialPos);
		void Move(Point destination);
};