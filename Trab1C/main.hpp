#include <GL/glut.h>
#include <iostream>
#include <vector>

class Point{
  public:
    GLfloat x,y;
    Point(GLint _x, GLint _y){
      x = _x;
      y = _y;
    }
    Point(){

    }
};


class Ellipse{
	public:
		Point center;
		GLfloat xRadius;
		GLfloat yRadius;
		Ellipse(Point _center, GLfloat _xRadius, GLfloat _yRadius){
			center = _center;
			xRadius = _xRadius;
			yRadius = _yRadius;
		}
		Ellipse(){

		}
};


class Leg{
	public:
		std::vector<Point> articulationPosition;
		Leg(std::vector<Point> articulationPosition);
		Leg();
};

class Spider{
	public:
		Point position;
		Ellipse cephalotorax;
		Ellipse abdomen;
		std::vector<Leg> legs;
		Spider(Point initialPos){
			position = initialPos;
		}
		void Move(Point destination);
};
