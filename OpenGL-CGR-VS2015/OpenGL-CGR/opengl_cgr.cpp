#include <stdlib.h>
#include <GL/glut.h>
#include <cmath>

void drawObject()
{
	glBegin(GL_POLYGON);
		glVertex3f(-0.5, -0.5, 0.0);
		glVertex3f(-0.5, 0.5, 0.0);
		glVertex3f(0.5, 0.5, 0.0);
		glVertex3f(0.5, -0.5, 0.0);
	glEnd();
}

//render method (callback-function)
void display()
{
	//clear all pixels
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	//draw white polygon with corners
	glColor3f(1.0, 1.0, 1.0);
	drawObject();
	glPushMatrix();
		glTranslatef(0,1,0);
		glColor3f(0, 0, 1);
		drawObject();
	glPopMatrix();
	glPushMatrix();
		glColor3f(1, 0, 0);
		glTranslatef(-1, 0, 0);
		drawObject();
	glPopMatrix();
		glPushMatrix();
		glColor3f(0, 1, 0);
		glTranslatef(0, -1, 0);
		drawObject();
	glPopMatrix();
	glPushMatrix();
		glColor3f(1, 1, 0);
		glTranslatef(sqrt(1.5), -1, 0);
		glRotatef(45, 0, 0, 1);
		drawObject();
	glPopMatrix();
	//don't wait! process buffered OpenGL routines
	glFlush();	
}

//initialization of the application. only started once.
void init() 
{
	//select clearing color (color that is used as 'background')
	glClearColor(0.0, 0.0, 0.0, 0.0);

	//initialize view
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5.0, 5.0, -5.0, 5.0, -1.0, 1.0);

	//set matrix-mode back to model-view for rendering
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	//initialize display mode (single buffer and RGBA)
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	//initialize window size and position. open window
	glutInitWindowSize(250, 250); 
	glutInitWindowPosition(100, 100);
	glutCreateWindow("OpenGL - CGR");

	//call initialization routine
	init();
	
	//register callback function to display graphics
	glutDisplayFunc(display); 
	
	//enter main loop and process events
	glutMainLoop();

	return 0;
}