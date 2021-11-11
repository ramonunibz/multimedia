#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

void drawRiver()
{
	glBegin(GL_POLYGON);
		glColor3f(0.2, 0.3, 0.3);
		glVertex3f(-20.0, -10.0, 0.0);
		glVertex3f(20.0, -10.0, 0.0);
		glVertex3f(20.0, -5.0, 0.0);
		glVertex3f(-20.0, -5.0, 0.0);
	glEnd();
}

void drawSky()
{
	glBegin(GL_POLYGON);
		glColor3f(0.8, 0.1, 0.5);
		glVertex3f(-20.0, -5.0, 0.0);
		glVertex3f(20.0, -5.0, 0.0);
		glColor3f(0.0, 0.0, 0.8);
		glVertex3f(20.0, 10.0, 0.0);
		glVertex3f(-20.0, 10.0, 0.0);
	glEnd();
}

void drawCircle()
{
	int triangleAmount = 180;
	glBegin(GL_TRIANGLE_FAN);
		glColor3f(0.95, 0.9, 0.55);
		glVertex3f(0.0, 0.0, 0.0);
		for (int i = 0; i <= triangleAmount+1;i++) {
			glVertex2f(
				(1.0 * cos(i * 6.28 / triangleAmount)),
				(1.0 * sin(i * 6.28 / triangleAmount))
			);
		}
	glEnd();
}

void drawBuildingType1()
{
	glBegin(GL_POLYGON);
		glColor3f(0.3, 0.5, 0.7);
		glVertex3f(-0.8, -5.0, 0.0);
		glVertex3f(0.8, -5.0, 0.0);
		glVertex3f(0.8, 5.0, 0.0);
		glVertex3f(-0.8, 5.0, 0.0);
	glEnd();
}

//render method (callback-function)
void display()
{
	//clear all pixels
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	//draw white polygon with corners
	glColor3f(0.0, 0.0, 0.0);
	drawRiver();
	drawSky();
	glPushMatrix();
		glTranslatef(-17.5, 0.0, 0.0);
		drawBuildingType1();
		glTranslatef(5.0, 0.0, 0.0);
		drawBuildingType1();
		glTranslatef(8.0, 0.0, 0.0);
		drawBuildingType1();
		glTranslatef(5.0, 0.0, 0.0);
		drawBuildingType1();
		glTranslatef(15.0, 0.0, 0.0);
		drawBuildingType1();
	glPopMatrix();
	drawCircle();
	//don't wait! process buffered OpenGL routines
	glFlush();	
}

//initialization of the application. only started once.
void init() 
{
	//select clearing color (color that is used as 'background')
	glClearColor(0.1, 0.1, 0.4, 0.0);

	//initialize view
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-20.0, 20.0, -10.0, 10.0, -1.0, 1.0);

	//set matrix-mode back to model-view for rendering
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	//initialize display mode (single buffer and RGBA)
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	//initialize window size and position. open window
	glutInitWindowSize(960, 480);
	glutInitWindowPosition(960, 405);
	glutCreateWindow("OpenGL - CGR");

	//call initialization routine
	init();
	
	//register callback function to display graphics
	glutDisplayFunc(display); 
	
	//enter main loop and process events
	glutMainLoop();

	return 0;
}