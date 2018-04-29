#include "Model.hpp"
#define PI 3.14159265359

Model::Model(View *view) {
	this->view = view;

}

void Model::initSpider() {
// Set a new spider 
}

void Model::drawSpider() {
// Call view.drawSpider()
}

void Model::moveSpider(GLint x, GLint y) {
}

Point::Point (GLint x, GLint y){
	this->x = x;
	this->y = y;
}

Ellipse::Ellipse (Point center, GLfloat xRadius, GLfloat yRadius){
	this->center = center;
	this->xRadius = xRadius;
	this->yRadius = yRadius;
}

Leg::Leg (std::vector<Point> articulationPosition){
	this->articulationPosition = articulationPosition;
}

Spider::Spider(Point initialPos){
	//creatubg the spider from initial_pos
	Ellipse *cephalotorax = new Ellipse(initialPos, 10.0f, 12.5f); 
	this->cephalotorax = *cephalotorax;
	Point* p = new Point(initialPos.x, initialPos.y + 30.0f);
	Ellipse *abdomen = new Ellipse(*p, 15.0f, 20.0f);
	this->abdomen = *abdomen;
	GLfloat rx = this->cephalotorax.xRadius;
	GLfloat ry = this->cephalotorax.yRadius;
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