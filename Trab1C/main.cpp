#include "main.hpp"

Spider *spider;

GLint main(GLint argc, char **argv) {
  spider = new Spider(Point(400,300));
  
  view(argc, argv);
  glutMouseFunc(mouseListener);
  glutDisplayFunc(emptyCallback);
  glMatrixMode(GL_MODELVIEW);
  
  spider->Rotate(45);
  spider->Move(Point(100,200));
  spider->Rotate(45);
  spider->Move(Point(100,400));
  
  glutMainLoop();
  return 1;
}

void view(GLint argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

  screen_width  = glutGet(GLUT_SCREEN_WIDTH),
  screen_height = glutGet(GLUT_SCREEN_HEIGHT);
  positionx = (screen_width-WINDOW_WIDTH)/2;
  positiony = (screen_height-WINDOW_HEIGHT)/2;

  glutInitWindowPosition(positionx, positiony);  
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT); 
  glutCreateWindow(TITLE);                        
  init();
}

void init() {
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glMatrixMode(GL_PROJECTION);
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  glOrtho(0.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, 0.0f, 1.0f);
  glFlush();
}

void mouseListener(GLint button, GLint action, GLint x, GLint y) {
  GLfloat ang;
  Point dest;
  switch (button) {
    case GLUT_LEFT_BUTTON: {
      dest = Point(x,y);
      ang = 0;
      if (dest.x >= spider->position.x){
        ang = asin((spider->position.y - dest.y)/sqrt(pow(dest.x - spider->position.x,2)
          + pow(dest.y - spider->position.y,2)))*(180/M_PI);
      } 
      else if(dest.x < spider->position.x && dest.y <= spider->position.y){
        ang = 90 + acos((spider->position.y - dest.y)/sqrt(pow(dest.x - spider->position.x,2)
          + pow(dest.y - spider->position.y,2)))*(180/M_PI);
      }
      else if(dest.x < spider->position.x && dest.y > spider->position.y){
        ang = -270 + acos((spider->position.y - dest.y)/sqrt(pow(dest.x - spider->position.x,2)
          + pow(dest.y - spider->position.y,2)))*(180/M_PI);
      }
      if(isfinite(ang)){
        spider->Rotate(-ang + 90 - spider->angle);
        spider->Move(Point(x,y));
      }
      break;
    }
	}
    spider->Rotate(0.1);
}

void emptyCallback(){}

Point::Point(GLint _x, GLint _y){
  x = _x;
  y = _y;
}

Ellipse::Ellipse(Point _center, GLfloat _xRadius, GLfloat _yRadius){
  center = _center;
  xRadius = _xRadius;
  yRadius = _yRadius;
}

void Ellipse::Draw(){
  GLfloat points = 3000.0;
  for(GLfloat i = 0.0;i<points;i++){
    GLfloat ang_sin = sin((i/points)*(360)*(M_PI/180));
    GLfloat ang_cos = cos((i/points)*(360)*(M_PI/180));
    GLfloat new_x = this->center.x + this->xRadius*ang_cos;
    GLfloat new_y = this->center.y + this->yRadius*ang_sin;
    glBegin(GL_POINTS);
      glVertex2f(new_x,new_y);
    glEnd();
  }
}

Leg::Leg(Point _initialPos,GLint _side,GLint _arts, GLint _ang, GLint _direction){
  initialPos = _initialPos;
  side = _side;
  arts = _arts;
  ang = _ang;
  start_ang = ang;
  direction = _direction;
}

void Leg::DrawLine(Point start, Point end){
  GLfloat m = (start.y - end.y)/(start.x - end.x);
  if(m > 1 || m < -1){
    m = (start.x - end.x)/(start.y - end.y);
    for(GLfloat i = start.y; i < end.y; i++){
      DrawLinePointX(start, i, m);
    }
    for(GLfloat i = start.y; i > end.y; i--){
       DrawLinePointX(start, i, m);
    }
  }else{
    for(GLfloat i = start.x; i<end.x; i++){
       DrawLinePointY(start, i, m);
    }
    for(GLfloat i = start.x; i > end.x; i--){
       DrawLinePointY(start, i, m);
    }
  }
}

void Leg::DrawLinePointX(Point start, GLint i, GLfloat m){
  glBegin(GL_POINTS);
    glVertex2f((i - start.y)*m + start.x, i);
  glEnd();
}

void Leg::DrawLinePointY(Point start, GLint i, GLfloat m){
  glBegin(GL_POINTS);
    glVertex2f(i, (i - start.x)*m + start.y);
  glEnd();
}

void Leg::Draw(){
  GLfloat points = 3000.0;
  GLfloat art_size = 50;
  GLfloat ang = this->ang;
  Point reference = this->initialPos;
  Point aux;
  for(GLint i = 0; i < this->arts; i++){
    aux = Point(reference.x + art_size*cos(ang*(M_PI/180))
      *this->side, reference.y + art_size*sin(ang*(M_PI/180)));
    DrawLine(reference, aux);
    reference = aux; 
    art_size /= 2;
    ang += 30;
  }
}

void Leg::Move(){
  //@param i = index of the leg
  if     (this->ang < this->start_ang + 15 && this->direction == 1)
    this->ang += 1;  //move up
  else if(this->ang > this->start_ang - 15 && this->direction == -1)
    this->ang -= 1;  //move down 
  else{ //change direction
    if(this->direction == 1)
      this->direction = -1;
    else
      this->direction = 1;
  } 

}

Spider::Spider(Point initialCoords){
  Point initialPos;
  position = initialCoords;
  initialPos = Point(0,0);
  cephalotorax = Ellipse(initialPos, 20, 30);
  abdomen = Ellipse(Point(initialPos.x,initialPos.y + 80), 40, 50);
  
  legs[0] = Leg(Point(initialPos.x + 15, initialPos.y - 20), 1, 3,-80, 1);
  legs[1] = Leg(Point(initialPos.x + 15, initialPos.y - 10), 1, 3,-20,-1);
  legs[2] = Leg(Point(initialPos.x + 15, initialPos.y     ), 1, 3, 20, 1);
  legs[3] = Leg(Point(initialPos.x + 15, initialPos.y + 10), 1, 3, 40,-1);
  legs[4] = Leg(Point(initialPos.x - 15, initialPos.y - 20),-1, 3,-80,-1);
  legs[5] = Leg(Point(initialPos.x - 15, initialPos.y - 10),-1, 3,-20, 1);
  legs[6] = Leg(Point(initialPos.x - 15, initialPos.y     ),-1, 3, 20,-1);
  legs[7] = Leg(Point(initialPos.x - 15, initialPos.y + 10),-1, 3, 40, 1);
}

void Spider::Draw(){
  glColor3f(0.0,0.0,0.0);
  glPointSize(3.0);
  this->cephalotorax.Draw();
  this->abdomen.Draw();
  for(GLint i=0;i<8;i++){
    this->legs[i].Draw();
  }
  glFlush();
}

void Spider::Move(Point dest){
  if(!pow(position.x - dest.x, 2) && !pow(position.y-dest.y,2)){
    return;
  }
  Point oldPosition = Point(position.x,position.y);
  if(pow(position.x - dest.x, 2) > pow(position.y - dest.y, 2)){
    for(GLint i = 0; i < abs(oldPosition.x - dest.x); i++){
      if(dest.x - oldPosition.x > 0){
        this->position.x += 1;
        this->position.y += (dest.y - oldPosition.y)/abs(dest.x - oldPosition.x);
      }else{
        this->position.x += -1;
        this->position.y += (dest.y - oldPosition.y)/abs(dest.x - oldPosition.x);
      }
      glClear(GL_COLOR_BUFFER_BIT);
      glPushMatrix();
      glRotatef(this->angle, 0.0, 0.0, 1.0);
      glTranslatef(this->position.x*cos(this->angle*(M_PI/180)) + this->position.y*sin(this->angle*(M_PI/180)),
            - this->position.x*sin(this->angle*(M_PI/180)) + this->position.y*cos(this->angle*(M_PI/180)),
             0.0);
      for(GLint j = 0; j < 8; j++){
        this->legs[j].Move();
      }
      this->Draw();
      glPopMatrix();
      usleep(100 /(moveSpeed) * 1000);
    }
  }else{
    for(GLint i = 0; i < abs(oldPosition.y - dest.y); i++){
      if(dest.y - oldPosition.y > 0){
        this->position.y += 1;
        this->position.x += (dest.x - oldPosition.x)/abs(dest.y - oldPosition.y);
      }else{
        this->position.y += -1;
        this->position.x += (dest.x - oldPosition.x)/abs(dest.y - oldPosition.y);
      }
      glClear(GL_COLOR_BUFFER_BIT);
      glPushMatrix();
      glRotatef(this->angle, 0.0, 0.0, 1.0);
      glTranslatef(this->position.x*cos(this->angle*(M_PI/180)) + this->position.y*sin(this->angle*(M_PI/180)),
            - this->position.x*sin(this->angle*(M_PI/180)) + this->position.y*cos(this->angle*(M_PI/180)),
             0.0);
      for(GLint j = 0; j < 8; j++){
        this->legs[j].Move();
      }
      this->Draw();
      glPopMatrix();
      usleep(100 /(moveSpeed) * 1000);
    }
  }
  this->position = dest;
}

void Spider::Rotate(GLfloat _angle){
  if(_angle > 0){
    for(GLint i = (this->angle)*5; i < (this->angle + _angle)*5; i++){
      this->RotateStep(i);
    }
  }else{
    for(GLint i = (this->angle)*5; i > (this->angle + _angle)*5; i--){
      this->RotateStep(i);
    }
  }
  angle += _angle;
}

void Spider::RotateStep(GLint i) {
  glClear(GL_COLOR_BUFFER_BIT);
  glPushMatrix();
    glRotatef(0.2*i, 0.0, 0.0, 1.0);
    glTranslatef(this->position.x*cos(0.2*i*(M_PI/180))
      + this->position.y*sin(0.2*i*(M_PI/180)), - this->position.x*sin(0.2*i*(M_PI/180))
      + this->position.y*cos(0.2*i*(M_PI/180)), 0.0);
    this->Draw();
  glPopMatrix();
  usleep(100 / (rotateSpeed) * 1000);
}