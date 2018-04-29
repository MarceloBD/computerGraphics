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
		int moveSpeed;
		int rotateSpeed;
		float angle;
		Spider(Point initialCoords){
			angle = 0;
			moveSpeed = 50;
			rotateSpeed = 100;
			position = initialCoords;
			Point initialPos = Point(0,0);
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
		void Draw(){
		  glColor3f(0.0,0.0,0.0);
		  glPointSize(3.0);
		  this->cephalotorax.Draw();
		  this->abdomen.Draw();
		  for(int i=0;i<8;i++){
		    this->legs[i].Draw();
		  }
		  glFlush();
		}

		void Move(Point dest){
			if(pow(position.x-dest.x,2)==0&&pow(position.y-dest.y,2)==0){
				return;
			}
			Point oldPosition = Point(position.x,position.y);
			if(pow(position.x-dest.x,2)>pow(position.y-dest.y,2)){
				for(int i = 0;i<abs(oldPosition.x-dest.x);i++){
					if(dest.x-oldPosition.x>0){
						this->position.x += 1;
						this->position.y += (dest.y-oldPosition.y)/abs(dest.x-oldPosition.x);
					}else{
						this->position.x += -1;
						this->position.y += (dest.y-oldPosition.y)/abs(dest.x-oldPosition.x);
					}
					glClear(GL_COLOR_BUFFER_BIT);
					glPushMatrix();
					glRotatef(this->angle,0.0,0.0,1.0);
					glTranslatef(this->position.x*cos(this->angle*(PI/180))+this->position.y*sin(this->angle*(PI/180)),-this->position.x*sin(this->angle*(PI/180))+this->position.y*cos(this->angle*(PI/180)), 0.0);
					this->Draw();
					glPopMatrix();
					usleep(100 /(moveSpeed) * 1000);
				}
			}else{
				for(int i = 0;i<abs(oldPosition.y-dest.y);i++){
					if(dest.y-oldPosition.y>0){
						this->position.y += 1;
						this->position.x += (dest.x-oldPosition.x)/abs(dest.y-oldPosition.y);
					}else{
						this->position.y += -1;
						this->position.x += (dest.x-oldPosition.x)/abs(dest.y-oldPosition.y);
					}
					glClear(GL_COLOR_BUFFER_BIT);
					glPushMatrix();
					glRotatef(this->angle,0.0,0.0,1.0);
					glTranslatef(this->position.x*cos(this->angle*(PI/180))+this->position.y*sin(this->angle*(PI/180)),-this->position.x*sin(this->angle*(PI/180))+this->position.y*cos(this->angle*(PI/180)), 0.0);
					this->Draw();
					glPopMatrix();
					usleep(100 /(moveSpeed) * 1000);
				}
			}
			this->position = dest;
		}

//O *5 serve apenas para deixar o movimento mais suave (smooth) em angulos pequenos
		void Rotate(float _angle){
			if(_angle>0){
				for(int i=(this->angle)*5;i<(this->angle+_angle)*5;i++){
					glClear(GL_COLOR_BUFFER_BIT);
					glPushMatrix();
					glRotatef(0.2*i,0.0,0.0,1.0);
					glTranslatef(this->position.x*cos(0.2*i*(PI/180))+this->position.y*sin(0.2*i*(PI/180)),-this->position.x*sin(0.2*i*(PI/180))+this->position.y*cos(0.2*i*(PI/180)), 0.0);
					this->Draw();
					glPopMatrix();
			    usleep(100 / (rotateSpeed) * 1000);
			  }
			}else{
				for(int i=(this->angle)*5;i>(this->angle+_angle)*5;i--){
					glClear(GL_COLOR_BUFFER_BIT);
					glPushMatrix();
					glRotatef(0.2*i,0.0,0.0,1.0);
					glTranslatef(this->position.x*cos(0.2*i*(PI/180))+this->position.y*sin(0.2*i*(PI/180)),-this->position.x*sin(0.2*i*(PI/180))+this->position.y*cos(0.2*i*(PI/180)), 0.0);
					this->Draw();
					glPopMatrix();
			    usleep(100 / (rotateSpeed) * 1000);
			  }
			}
			angle += _angle;
		}
};
