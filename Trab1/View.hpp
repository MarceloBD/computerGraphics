#ifndef _GL
#define _GL
#include <GL/glut.h>
#endif 

class View
{
	public:
		View(int argc, char **argv);
		~View();
	private:
		static const GLint WINDOW_WIDTH = 800;
		static const GLint WINDOW_HEIGHT = 600;
		static const GLint POSITIONX = 0;
		static const GLint POSITIONY = 0;
		static const GLchar TITLE[30] = "This is a black spider";
		GLint screen_width, screen_height;
};

