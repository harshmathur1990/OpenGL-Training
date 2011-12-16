#include <stdlib.h>	// Note: declare stdlib.h BEFORE glut.h
#include <glut.h>
#include <iostream>
using namespace std;

#define width	1366
#define height	768
#define minx	-50.0f
#define maxx	50.0f
#define miny	-50.0f
#define maxy	50.0f

float offset = 0, direction=1;
float spin_speed = 0;

 void init() {
	glEnable(GL_DEPTH_TEST);	// enables openGL's depth test (if you comment this out, objects won't 'overlap' correctly!
	glDepthFunc(GL_LEQUAL);		// the comparison function openGL uses for depth. (not necessary, just showing you this exists)

	glClearColor(0.1f, 0.0f, 0.1f, 1.0f);	// sets the background color (RGBA)

	glMatrixMode(GL_PROJECTION);
	// sets the matrix mode to projection -- to modify the 'view'

	// we are using a camera now, replaced glOrtho2D.
	// this sets a 'perspective' with a 45* angle of vision, aspect ratio width/height, and 'range' 1 to 1000.
	// (1 means REALLLY really close objects -- they will be zoomed in too much! objects further than 1000
	// though will disappear)
	// **Note: distances that you 'see' will have to be negative -- positive things will appear 'behind' you.
	gluPerspective(45.0f, (double)width/(double)height, 1.0f, 1000.0f);
}

void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//	GL_COLOR_BUFFER_BIT -- reset the frame buffer (otherwise, has colors from last draw!)
	//	GL_DEPTH_BUFFER_BIT -- reset the depth buffer to infinity.

	glMatrixMode(GL_MODELVIEW);
	// sets the matrix mode to model -- to modify the objects in space.

	glLoadIdentity();	// initialize model matrix to the identity matrix.

              // Move Right And Into The Screen
     glTranslatef(0,0,-400);
    glRotatef(offset,1.0f,1.0f,1.0f);          // Rotate The Cube On X, Y & Z
glTranslatef(0,0,400);

    glBegin(GL_QUADS);
    glColor3f(0.0f,1.0f,0.0f);                     // Set The Color To Green
    glVertex3f(minx,maxy,-350.0f);
    glVertex3f( minx, miny,-350.0f);          // Top Right Of The Quad (Top)
    glVertex3f(minx, miny,-450.0f);          // Top Left Of The Quad (Top)
    glVertex3f(minx, maxy, -450.0f);          // Bottom Left Of The Quad (Top)

   glColor3f(1.0f,0.5f,0.0f);          // Set The Color To Orange
glVertex3f(minx,miny,-450.0f);
    glVertex3f( maxx, miny,-450.0f);          // Top Right Of The Quad (Top)
    glVertex3f(maxx, maxy,-450.0f);          // Top Left Of The Quad (Top)
    glVertex3f(minx, maxy, -450.0f);          // Bottom Left Of The Quad (Top)

    glColor3f(1.0f,0.0f,0.0f);          // Set The Color To Red
glVertex3f( maxx, miny, -450.0f);          // Top Right Of The Quad (Front)
glVertex3f(maxx, maxy, -450.0f);          // Top Left Of The Quad (Front)
glVertex3f(maxx,maxy, -350.0f);          // Bottom Left Of The Quad (Front)
glVertex3f( maxx,miny, -350.0f);          // Bottom Right Of The Quad (Front)

glColor3f(1.0f,1.0f,0.0f);          // Set The Color To Yellow
glVertex3f( maxx, maxy, -350.0f);          // Top Right Of The Quad (Front)
glVertex3f(minx, maxy, -350.0f);          // Top Left Of The Quad (Front)
glVertex3f(minx,miny, -350.0f);          // Bottom Left Of The Quad (Front)
glVertex3f( maxx,miny, -350.0f);          // Bottom Right Of The Quad (Front)

glColor3f(0.0f,0.0f,1.0f);          // Set The Color To Blue
glVertex3f(maxx, miny, -350.0f);          // Top Right Of The Quad (Left)
glVertex3f(minx, miny,-350.0f);          // Top Left Of The Quad (Left)
glVertex3f(minx,miny,-450.0f);          // Bottom Left Of The Quad (Left)
glVertex3f(maxx,miny, -450.0f);          // Bottom Right Of The Quad (Left)

   glColor3f(1.0f,0.0f,1.0f);          // Set The Color To Violet
    glVertex3f(maxx, maxy, -450.0f);          // Top Right Of The Quad (Left)
glVertex3f(maxx, maxy,-350.0f);          // Top Left Of The Quad (Left)
glVertex3f(minx,maxy,-350.0f);          // Bottom Left Of The Quad (Left)
glVertex3f(minx,maxy,-450.0f);          // Bottom Right Of The Quad (Left)

    glEnd();

 glTranslatef(0,0,-400);
    glRotatef(-offset,1.0f,1.0f,1.0f);          // Rotate The Cube On X, Y & Z
    glTranslatef(0,0,400);

	//glFlush();	// required because of single-buffering to push things to the screen.
	glutSwapBuffers();	// for GLUT_DOUBLE, use glutSwapBuffers() to change frames.;
}

void update(){
    int time = glutGet(GLUT_ELAPSED_TIME);
    if(time % 100 == 0) {
     offset = offset - 10;
      }
    glutPostRedisplay();
    }

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);

	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //single buffering
	//glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); //double buffering

	//	GLUT_SINGLE or GLUT_DOUBLE -- single vs. double buffering.
	//	GLUT_RGB -- specifies color mode is RGB
	//	GLUT_DEPTH -- We need a depth-buffer (can add other similar buffers)


	glutInitWindowSize(width,height);	//width, height of the window.

	glutInitWindowPosition(0, 0);	// location on the screen the window appears

	(void)glutCreateWindow("Window Title");	// creates the window.

	init();		// things to do once.

	glutDisplayFunc(render);		// tells glut which function to call to render a screen.
    glutIdleFunc(update);
	glutMainLoop();				// once this is called, glut takes over --
						// returns only when the window is closed.
	return 0;
}
