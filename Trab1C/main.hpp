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
		Point initialPos;
		int ang;
		int side;
		int arts;
		Leg(Point _initialPos,int _side,int _arts, int _ang){
			initialPos = _initialPos;
			side = _side;
			arts = _arts;
			ang = _ang;
			//side = 1: Direita
			//side = -1: Esquerda
		}
		Leg(){

		}
};

class Spider{
	public:
		Point position;
		Ellipse cephalotorax;
		Ellipse abdomen;
		Leg legs[8];
		Spider(Point initialPos){
			position = initialPos;
			cephalotorax = Ellipse(initialPos,20,30);
			abdomen = Ellipse(Point(initialPos.x,initialPos.y+80),40,50);
			for(int i = 0;i<4;i++){
				legs[i] = Leg(Point(initialPos.x+15,initialPos.y-20+i*10),1,3,0);
			}
			for(int i = 4;i<8;i++){
				legs[i] = Leg(Point(initialPos.x-15,initialPos.y-20+(i-4)*10),-1,3,0);
			}
			legs[0] = Leg(Point(initialPos.x+15,initialPos.y-20),1,3,-80);
			legs[1] = Leg(Point(initialPos.x+15,initialPos.y-10),1,3,-20);
			legs[2] = Leg(Point(initialPos.x+15,initialPos.y),1,3,20);
			legs[3] = Leg(Point(initialPos.x+15,initialPos.y+10),1,3,40);
			legs[4] = Leg(Point(initialPos.x-15,initialPos.y-20),-1,3,-80);
			legs[5] = Leg(Point(initialPos.x-15,initialPos.y-10),-1,3,-20);
			legs[6] = Leg(Point(initialPos.x-15,initialPos.y),-1,3,20);
			legs[7] = Leg(Point(initialPos.x-15,initialPos.y+10),-1,3,40);
		}
		void Move(Point destination);
		void Rotate(int ang){

		}
};
