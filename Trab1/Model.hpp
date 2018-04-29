//TODO: ifndef
#ifndef _GL

#define _GL
#include <GL/glut.h>
#include <iostream>
#endif

#ifndef _View
#define _View
#include "View.hpp"
#endif


#include <vector>

class Model
{
	public:
		Model(View *view);
		~Model();
		void drawSpider();
		void initSpider();
		void moveSpider(GLint x, GLint y);
	private:
		View *view;

};

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