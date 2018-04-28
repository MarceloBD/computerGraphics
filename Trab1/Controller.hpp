#ifndef _GL
#define _GL
#include <GL/glut.h>
#include <iostream>
#endif 

#ifndef _View
#define _View
#include "View.hpp"
#endif
#ifndef _Model
#define _Model
#include "Model.hpp"
#endif

class Controller
{
	public:
		Controller(View *view, Model *model);
		static void mouseListener(GLint button, GLint action, GLint x, GLint y);
		~Controller();
	private:
		View *view;


};