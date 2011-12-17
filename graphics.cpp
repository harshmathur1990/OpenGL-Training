#include <stdlib.h>	// Note: declare stdlib.h BEFORE glut.h
#include <glut.h>
#include<stdio.h>
#include <fstream>
#include <windows.h>
#include <iostream>
#include<math.h>

using namespace std;

#define width	1366
#define height	768
#define minx	-30.0f
#define maxx	30.0f
#define miny	-30.0f
#define maxy	30.0f
#define cylinder 1
float offset = 0, dx=0,dy=0,dz=0,h1,h2,h3,h4,h5,h6,h7,h8,hm;
float spin_speed = 0;

float xpos = 0, ypos = 0, zpos = 0, xrot = 0, yrot = 0, angle=0.0;
int i;
float cRadius = 70.0f; // our radius distance from our character

float lastx, lasty;

#ifndef CALLBACK
#define CALLBACK
#endif

GLuint startList;

void CALLBACK errorCallback(GLenum errorCode)
{
   const GLubyte *estring;

   estring = gluErrorString(errorCode);
   fprintf(stderr, "Quadric Error: %s\n", estring);
   exit(0);
}

GLvoid *genImage()
{
	GLvoid *data;
	FILE *file;

	// open texture data
	file = fopen( "a.raw", "rb" );
	if ( file == NULL ) return data;

	// allocate buffer
	int w = 1408;
	int h = 256;
	data = malloc( w * h * 3 );

	// read texture data
	fread( data, w * h * 3, 1, file );
	fclose( file );
	return data;
}

GLuint textures[2];

void makeTexture()
{
	glGenTextures(2, &textures[0]); // tell openGL we want 2 textures, and give it the array.
	glBindTexture(GL_TEXTURE_2D, textures[0]); // tells openGL the first texture is a 2D one.

	GLvoid *tex1 = genImage();		// get our image in the form of a RGB pixel array.
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, 1408, 256, GL_RGB, GL_UNSIGNED_BYTE, tex1);
		// This creates a 2D texture from tex1.
		// GL_RGBA refers to the format for the texture created.
		// 256x256 are the dimensions.
		// GL_RGB is the format of the input binary (tex1)
		// GL_UNSIGNED_BYTE specifies that each color in tex1 is represented by 1 unsigned byte.
		// tex1, a GLvoid* that contains the data to display.

		// this not only creates a texture, but creates a MIPMAP

	// these set the behavior when the texture is mapped to a surface SMALLER or BIGGER than it.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	// gl_nearest finds the nearest texture pixel and directly applies it.
	// gl_linear tries to compute value so it scales 'linearly'
	// gl_nearest_mipmap_nearest finds nearest mipmap, THEN does nearest
	// gl_linear_mipmap_nearest finds nearest mipmap, then does linear.
	// gl_nearest_mipmap_linear finds 2 close mipmaps, does nearest on both and averages them.
	// gl_linear_mipmap_linear does?
	// tweak these to see how the texture looks when scaled.

	//glBindTexture(GL_TEXTURE_2D, textures[1]);, GLvoid, and so on to create other textures.
}


 void init() {
    GLUquadricObj *qobj;
   GLfloat mat_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat mat_shininess[] = { 50.0 };
   GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
   GLfloat model_ambient[] = { 0.5, 0.5, 0.5, 1.0 };

	//glEnable(GL_DEPTH_TEST);		// depth and blending don't go well together.
	//glDepthFunc(GL_LEQUAL);
	glEnable(GL_BLEND);					// Enables blending.
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);	// blends using ALPHA values.*/


	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	// sets the background color (RGBA)

     glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
      startList = glGenLists(1);
   qobj =  gluNewQuadric();
   gluQuadricCallback(qobj, GLU_ERROR,(void(__stdcall*)())errorCallback);

	gluQuadricDrawStyle(qobj, GLU_FILL); /* flat shaded */
   gluQuadricNormals(qobj, GLU_FLAT);
   glNewList(startList, GL_COMPILE);
      gluCylinder(qobj, 4, 4, 25, 15, 5);
   glEndList();

	glMatrixMode(GL_PROJECTION);
	// sets the matrix mode to projection

	gluPerspective(45.0f, (double)width/(double)height, 50.0f, 1000.0f);

	makeTexture();
    ///////////////////////////////////////////////////random heights/////////////////////////////////////////
    h1 = h2 = h3 = h4 = h5 = h6 = h7 = h8 = hm = 0;
    while(h1>30 && h2>30 && h3>30 && h4>30 && h5>30 && h6>30 && h7>30 && h8>30){
        h1 = rand()*100;
        if(hm < h1) hm = h1;
        h2 = rand()*100;
        if(hm < h2) hm = h2;
        h3 = rand()*100;
        if(hm < h3) hm = h3;
        h4 = rand()*100;
        if(hm < h4) hm = h4;
        h5 = rand()*100;
        if(hm < h5) hm = h5;
        h6 = rand()*100;
        if(hm < h6) hm = h6;
        h7 = rand()*100;
        if(hm < h7) hm = h7;
        h8 = rand()*100;
        if(hm < h8) hm = h8;
        }
}

void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//	GL_COLOR_BUFFER_BIT -- reset the frame buffer (otherwise, has colors from last draw!)
	//	GL_DEPTH_BUFFER_BIT -- reset the depth buffer to infinity.

	glMatrixMode(GL_MODELVIEW);
	// sets the matrix mode to model -- to modify the objects in space.

	glLoadIdentity();	// initialize model matrix to the identity matrix.

    glEnable(GL_LIGHTING);


        glShadeModel (GL_FLAT);

glTranslatef(0.0f, 0.0f, -cRadius);
    glRotatef(xrot,1.0,0.0,0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    glPushMatrix();

     glColor3f(1.0f,0.0f,0.0f);

    glCallList(startList);

    glPopMatrix();

 glRotatef(yrot,0.0,1.0,0.0);  //rotate our camera on the y-axis (up and down)
    glTranslated(-xpos,0.0f,-zpos); //translate the screen to the position of our camera
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, textures[0]);
    glTranslatef(0,0,-100);
    glRotatef(offset,0.0f,1.0f,0.0f);          // Rotate The Cube On X, Y & Z
    glTranslatef(0,0,100);

    glBegin(GL_QUADS);

     glTexCoord2f(0,0.27f);glVertex3f(minx,maxy+h1,-50.0f);          //top left
     glTexCoord2f(0,0);glVertex3f( minx, miny,-50.0f);          // bottom left
     glTexCoord2f(0.27f,0);glVertex3f(minx, miny,-110.0f);          // bottom right
     glTexCoord2f(0.27f,0.27f);glVertex3f(minx, maxy+h2, -110.0f);          // top right

   //glColor3f(1.0f,0.5f,0.0f);          // Set The Color To Orange
     glTexCoord2f(0.27f,0.27f);glVertex3f(minx, miny,-110.0f);              //bottom left
     glTexCoord2f(0.54f,0.27f);glVertex3f( maxx, miny,-110.0f);          // bottom right
     glTexCoord2f(0.54f,0.54f);glVertex3f(maxx, maxy+h3,-110.0f);          // top right
     glTexCoord2f(0.27f,0.54f);glVertex3f(minx, maxy+h4, -110.0f);          // top left

    //glColor3f(1.0f,0.0f,0.0f);          // Set The Color To Red
     glTexCoord2f(0.54f,0.54f);glVertex3f( maxx, miny, -110.0f);          // bottom left
     glTexCoord2f(0.54f,0.81f);glVertex3f(maxx, maxy+h5, -110.0f);          // Top Left
     glTexCoord2f(0.81f,0.81f);glVertex3f(maxx,maxy+h6, -50.0f);          // top right
     glTexCoord2f(0.81f,0.54f);glVertex3f( maxx,miny, -50.0f);          // Bottom Right

//glColor3f(1.0f,1.0f,0.0f);          // Set The Color To Yellow
     glTexCoord2f(1,1);glVertex3f( maxx, maxy+h7, -50.0f);          // Top Right Of The Quad (Front)
     glTexCoord2f(0.81f,1);glVertex3f(minx, maxy+h8, -50.0f);          // Top Left Of The Quad (Front)
     glTexCoord2f(0.81f,0.81f);glVertex3f(minx,miny, -50.0f);          // Bottom Left Of The Quad (Front)
     glTexCoord2f(1,0.81f);glVertex3f( maxx,miny, -50.0f);          // Bottom Right Of The Quad (Front)

    //glColor3f(0.0f,0.0f,1.0f);          // Set The Color To Blue
     glTexCoord2f(0.09f,0);glVertex3f(maxx, miny, -50.0f);          // bottom right
     glTexCoord2f(0,0);glVertex3f(minx, miny,-50.0f);          // bottom left
     glTexCoord2f(0,0.09f);glVertex3f(minx,miny,-110.0f);          // top left
     glTexCoord2f(0.09f,0.09f);glVertex3f(maxx,miny, -110.0f);          // top right

    glEnd();

    glBegin(GL_QUADS);
     glTexCoord2f(0.09f,0);glVertex3f(maxx, maxy+hm, -110.0f);          // bottom right
     glTexCoord2f(0.09f,0.09f);glVertex3f(maxx, maxy+hm,-50.0f);          // top right
     glTexCoord2f(0,0.09f);glVertex3f(minx,maxy+hm,-50.0f);          // top left
     glTexCoord2f(0,0);glVertex3f(minx,maxy+hm,-110.0f);          // bottom left

    glEnd();

 glTranslatef(0,0,-100);
    glRotatef(-offset,0.0f,1.0f,0.0f);          // Rotate The Cube On X, Y & Z
    glTranslatef(0,0,100);

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();



	//glFlush();	// required because of single-buffering to push things to the screen.
	glutSwapBuffers();	// for GLUT_DOUBLE, use glutSwapBuffers() to change frames.;

	angle++;
}

void keyboard (unsigned char key, int x, int y) {
    if (key=='q')
    {
    xrot += 1;
    if (xrot >360) xrot -= 360;
    }

    if (key=='z')
    {
    xrot -= 1;
    if (xrot < -360) xrot += 360;
    }

    if (key=='w')
    {
    float xrotrad, yrotrad;
    yrotrad = (yrot / 180 * 3.141592654f);
    xrotrad = (xrot / 180 * 3.141592654f);
    xpos += (float)(sin(yrotrad));
    zpos -= (float)(cos(yrotrad));
    ypos -= (float)(sin(xrotrad));
    }

    if (key=='s')
    {
    float xrotrad, yrotrad;
    yrotrad = (yrot / 180 * 3.141592654f);
    xrotrad = (xrot / 180 * 3.141592654f);
    xpos -= (float)(sin(yrotrad));
    zpos += (float)(cos(yrotrad));
    ypos += (float)(sin(xrotrad));
    }

    if (key=='d')
    {
    float yrotrad;
    yrotrad = (yrot / 180 * 3.141592654f);
    xpos += (float)(cos(yrotrad)) * 0.2;
    zpos += (float)(sin(yrotrad)) * 0.2;
    }

    if (key=='a')
    {
    float yrotrad;
    yrotrad = (yrot / 180 * 3.141592654f);
    xpos -= (float)(cos(yrotrad)) * 0.2;
    zpos -= (float)(sin(yrotrad)) * 0.2;
    }

    if (key==27)
    {
    exit(0);
    }
}

void mouseMovement(int x, int y) {
    int diffx=x-lastx; //check the difference between the current x and the last x position
    int diffy=y-lasty; //check the difference between the current y and the last y position
    lastx=x; //set lastx to the current x position
    lasty=y; //set lasty to the current y position
    xrot += (float) diffy; //set the xrot to xrot with the addition of the difference in the y position
    yrot += (float) diffx;    //set the xrot to yrot with the addition of the difference in the x position
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
   glutIdleFunc (render);
    //glutReshapeFunc (reshape);

    glutPassiveMotionFunc(mouseMovement); //check for mouse movement

    glutKeyboardFunc (keyboard);
	glutMainLoop();				// once this is called, glut takes over --
						// returns only when the window is closed.
	return 0;
}
