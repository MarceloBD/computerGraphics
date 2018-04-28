#include "Model.hpp"
#define PI 3.14159265359

Model::Model() {


}

Point :: Point (GLint x, GLint y){
	this->x = x;
	this->y = y;
}

Ellipse :: Ellipse (Point center, GLfloat x_radius, GLfloat y_radius){
	this->center = center;
	this->x_radius = x_radius;
	this->y_radius = y_radius;
}

Leg :: Leg (std::vector<Point> articulation_position){
	this->articulation_position = articulation_position;
}

Spider :: Spider(Point initial_pos){
	//creatubg the spider from initial_pos
	Ellipse *cephalotorax = new Ellipse(initial_pos, 10.0f, 12.5f); 
	this->cephalotorax = *cephalotorax;
	Point* p = new Point(initial_pos.x, initial_pos.y + 30.0f);
	Ellipse *abdomen = new Ellipse(*p, 15.0f, 20.0f);
	this->abdomen = *abdomen;
	GLfloat rx = this->cephalotorax.x_radius;
	GLfloat ry = this->cephalotorax.y_radius;
	GLfloat x = (GLfloat)this->cephalotorax.center.x;
	GLfloat y = (GLfloat)this->cephalotorax.center.y;
	//calculating the legs positions
	/*for (int i = 0; i < 8; i ++){
		std::vector<Point*> positions(4);
		positions[0] = new Point(x + rx*cos(2*PI*i/8), y + ry*cos(2*PI*i/8));
		positions[1] = new Point(x + rx*cos(PI/6));
		positions[2] = new Point(x + rx*cos(PI/4));
	}TODO: finish legs positions */
}