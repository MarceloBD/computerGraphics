#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <iostream>
#include <GL/glut.h>
#include<unistd.h>
#define PI 3.14159265



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
		void Draw(){
		  float points = 3000.0;
		  for(float i = 0.0;i<points;i++){
		    float ang_sin = sin((i/points)*(360)*(PI/180));
		    float ang_cos = cos((i/points)*(360)*(PI/180));
		    float new_x = this->center.x + this->xRadius*ang_cos;
		    float new_y = this->center.y + this->yRadius*ang_sin;
		    glBegin(GL_POINTS);
		      glVertex2f(new_x,new_y);
		    glEnd();
		  }
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
		void Draw(){
		  float points = 3000.0;
		  float art_size = 50;
		  float ang = this->ang;
		  Point reference = this->initialPos;
		  for(int i=0;i<this->arts;i++){
		    DrawLine(reference,Point(reference.x+art_size*cos(ang*(PI/180))*this->side,reference.y+art_size*sin(ang*(PI/180))));
		    reference = Point(reference.x+art_size*cos(ang*(PI/180))*this->side,reference.y+art_size*sin(ang*(PI/180)));
		    art_size /= 2;
		    ang += 30;
		  }
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
		void Draw(){
		  glClear(GL_COLOR_BUFFER_BIT);
		  glColor3f(0.0,0.0,0.0);
		  glPointSize(3.0);
		  this->cephalotorax.Draw();
		  this->abdomen.Draw();
		  for(int i=0;i<8;i++){
		    this->legs[i].Draw();
		  }
		  glFlush();
		}
};
