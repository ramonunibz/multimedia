#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <time.h>  

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

void drawMoon()
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

void drawStars()
{
	
	glBegin(GL_LINES);
		glColor3f(1, 1, 0);
		
		//star 1
		glVertex2f(0, 0);
		glVertex2f(0.2, 0.1);

		glVertex2f(0.2, 0);
		glVertex2f(0, 0.1);
		
		// star 2
		glVertex2f(0.8, 1.5);
		glVertex2f(1.1, 1.7);

		glVertex2f(1.1, 1.5);
		glVertex2f(0.8, 1.7);
		// star 3
		glVertex2f(0.8, 3.5);
		glVertex2f(1.1, 3.7);

		glVertex2f(1.1, 3.5);
		glVertex2f(0.8, 3.7);

		
	glEnd();
}

void drawWindowBuilding1()
{
	glBegin(GL_POLYGON);
		glColor3f(0.9608, 0.9608, 0.8627);
		glVertex3f(-0.6, 4.4, 0.0);
		glVertex3f(-0.1, 4.4, 0.0);
		glVertex3f(-0.1, 4.9, 0.0);
		glVertex3f(-0.6, 4.9, 0.0);
	glEnd();
}

void drawDoorBuilding1() {
	glBegin(GL_POLYGON);
		glColor3f(0.5412, 0.4, 0.2588);
		glVertex3f(-0.3, -5.0, 0);
		glVertex3f(0.3, -5.0, 0);
		glVertex3f(0.3, -4.5, 0);
		glVertex3f(-0.3, -4.5, 0);
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
	glPushMatrix();
		for (int i = 0; i < 12; i++) {
			drawWindowBuilding1();
			glTranslatef(0.7, 0, 0);
			drawWindowBuilding1();
			glTranslatef(0, -0.7, 0);
			drawWindowBuilding1();
			glTranslatef(-0.7, 0, 0);
			drawWindowBuilding1();
		}
		
	glPopMatrix();
	drawDoorBuilding1();
}

void drawWindowBuilding2()
{
	glBegin(GL_POLYGON);
		glColor3f(0.9608, 0.9608, 0.8627);
		glVertex3f(-12.1, 1.3, 0.0);
		glVertex3f(-11.4, 1.3, 0.0);
		glVertex3f(-11.4, 1.8, 0.0);
		glVertex3f(-12.1, 1.8, 0.0);
	glEnd();

}

void drawDoorBuilding2() {
	glBegin(GL_POLYGON);
	glColor3f(0.5412, 0.4, 0.2588);
	glVertex3f(-10, -5.0, 0);
	glVertex3f(-8.95, -5.0, 0);
	glVertex3f(-8.95, -4.3, 0);
	glVertex3f(-10, -4.3, 0);
	glEnd();
}

void drawBuildingType2()
{
	glBegin(GL_POLYGON);
		glColor3f(0.6, 0.5, 0.7);
		glVertex3f(-12.3, -5.0, 0.0);
		glVertex3f(-6.8, -5.0, 0.0);
		glVertex3f(-6.8, 2.0, 0.0);
		glVertex3f(-12.3, 2.0, 0.0);
	glEnd();
	glPushMatrix();
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 5; j++) {
			drawWindowBuilding2();
			glTranslatef(1.1, 0.0, 0.0);
		}
		glTranslatef(-5.5, -1.0, 0.0);
	}
	glPopMatrix();
	
	drawDoorBuilding2();
}

void drawWindowBuilding3()
{
	glBegin(GL_POLYGON);
		glColor3f(0.827, 0.827, 0.827);
		glVertex3f(-24.8, -3.6, 0.0);
		glVertex3f(-23.0, -3.6, 0.0);
		glVertex3f(-23.0, -2.7, 0.0);
		glVertex3f(-24.8, -2.7, 0.0);
	glEnd();
	glBegin(GL_LINES);
		glPushMatrix();
			glColor3f(0.0, 0.0, 0.0);

			glVertex3f(-23.9, -2.71, 0);
			glVertex3f(-23.9, -3.60, 0);

			glVertex3f(-24.79, -3.15, 0);
			glVertex3f(-22.99, -3.15, 0);

		glPopMatrix();
	glEnd();

}

void drawDoorBuilding3() {
	glBegin(GL_POLYGON);
		glColor3f(0.5412, 0.4, 0.2588);
		glVertex3f(-20.5, -5.0, 0);
		glVertex3f(-19.6, -5.0, 0);
		glVertex3f(-19.6, -4.3, 0);
		glVertex3f(-20.5, -4.3, 0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-20.05, -4.3, 0);
	glVertex3f(-20.05, -5.0, 0);
	glPopMatrix();
	glEnd();
}


void drawBuildingType3()
{
	glBegin(GL_POLYGON);
		glColor3f(0.3, 0.3, 0.3);
		glVertex3f(-25, -5.0, 0.0);
		glVertex3f(-15.1, -5.0, 0.0);
		glVertex3f(-15.1, -2.5, 0.0);
		glVertex3f(-25, -2.5, 0.0);
	glEnd();
	glPushMatrix();
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				drawWindowBuilding3();
				glTranslatef(0, -1.2, 0);
			}
			glTranslatef(2.4, 2.4, 0);
		}
		glTranslatef(0.5, 0, 0);
		
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				drawWindowBuilding3();
				glTranslatef(0, -1.2, 0);
			}
			glTranslatef(2.4, 2.4, 0);
		}
	glPopMatrix();
	drawDoorBuilding3();
}

void drawBuildingType4() {
	glPushMatrix();
		glScalef(1.3,1.3,0);
		glTranslatef(9, 1.15, 0);
		drawBuildingType1();
	glPopMatrix();
}

void drawWindowBuilding5()
{
	glBegin(GL_POLYGON);
		glColor3f(0.9608, 0.9608, 0.8627);
		glVertex3f(-6.8, 7.4, 0.0);
		glVertex3f(-6.4, 7.4, 0.0);
		glVertex3f(-6.4, 7.8, 0.0);
		glVertex3f(-6.8, 7.8, 0.0);
	glEnd();
}

void drawDoorBuilding5() {
	glBegin(GL_POLYGON);
		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(-4.2, -5.0, 0.0);
		glVertex3f(-3.8, -5.0, 0.0);
		glVertex3f(-3.8, -4.4, 0.0);
		glVertex3f(-4.2, -4.4, 0.0);
	glEnd();
}

void drawBuildingType5()
{
	glBegin(GL_POLYGON);
		glColor3f(0.6667, 0.6627, 0.6784);
		glVertex3f(-7, -5.0, 0.0);
		glVertex3f(-1, -5.0, 0.0);
		glVertex3f(-1, 8.0, 0.0);
		glVertex3f(-7, 8.0, 0.0);
	glEnd();
	glPushMatrix();
	drawWindowBuilding5();
		for (int i = 0; i < 23; i++) {
			for (int j = 0; j < 11; j++) {
				drawWindowBuilding5();
				glTranslatef(0.52, 0, 0);
			}
			glTranslatef(-5.72, -0.52, 0);
		}
	glPopMatrix();
	drawDoorBuilding5();
}

void drawBuildingType6() {
	glPushMatrix();
		glScalef(0.9, 0.7, 0);
		glTranslatef(-25, -2.15, 0);
		drawBuildingType5();
	glPopMatrix();
}

void drawBuildingType7() {
	glBegin(GL_POLYGON);
		glColor3f(0.2588, 0.1922, 0.5373);
		glVertex3f(15, -5.0, 0.0);
		glVertex3f(18, -5.0, 0.0);
		glVertex3f(18, 6.0, 0.0);
		glVertex3f(15, 6.0, 0.0);
	glEnd();
}

void drawBuildingType8() {
	glBegin(GL_POLYGON);
	glColor3f(0.1922, 0.0, 0.3843);
	glVertex3f(-2, -5.0, 0.0);
	glVertex3f(0, -5.0, 0.0);
	glVertex3f(0, 7.5, 0.0);
	glVertex3f(-2, 7.5, 0.0);
	glEnd();
}

//render method (callback-function)
void display()
{
	srand(time(NULL));
	double randomX;
	double randomY;
	//clear all pixels
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	//draw white polygon with corners
	glColor3f(0.0, 0.0, 0.0);
	drawRiver();
	drawSky();
	
	for (int i = 0; i < 100; i++) {
			glPushMatrix();
				randomX = rand() % 4000 / 100.0 - 20.0;
				randomY = rand() % 2000 / 100.0 - 3.0;
				glTranslatef(randomX, randomY, 0.0);
				drawStars();
			glPopMatrix();
	}

	
	glPushMatrix();
		glPushMatrix();
			drawBuildingType7();
			glTranslatef(-8, 0, 0);
			drawBuildingType7();
			glTranslatef(-6, 0, 0);
			drawBuildingType7();
			glTranslatef(-10, 0, 0);
			drawBuildingType7();
			glTranslatef(-10, 0, 0);
			drawBuildingType7();
		glPopMatrix();

		glPushMatrix();
			drawBuildingType8();
			glTranslatef(-7.0, 0, 0);
			drawBuildingType8();
			glTranslatef(-7.0, 0, 0);
			drawBuildingType8();
			glTranslatef(-7.0, 0, 0);
			drawBuildingType8();
			glTranslatef(25.0, 0, 0);
			drawBuildingType8();
			glTranslatef(7.0, 0, 0);
			drawBuildingType8();
			glTranslatef(8.0, 0, 0);
			drawBuildingType8();

		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(8.0, 0.0, 0.0);
			drawBuildingType6();
		glPopMatrix();
		drawBuildingType5();
		glPushMatrix();
			glTranslatef(11.0, 0.0, 0.0);
			drawBuildingType5();
		glPopMatrix();
		drawBuildingType4();
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
		drawBuildingType2();
		glTranslatef(-15.0, 0.0, 0.0);
		drawBuildingType2();
		glTranslatef(30.0, 0.0, 0.0);
		drawBuildingType2();
		drawBuildingType3();
		glTranslatef(-25.0, 0.0, 0.0);
		drawBuildingType3();
		
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-18, 8, 0);
		drawMoon();
	glPopMatrix();
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
	glutInitWindowPosition(40, 40);
	glutCreateWindow("OpenGL - CGR");

	//call initialization routine
	init();
	
	//register callback function to display graphics
	glutDisplayFunc(display); 
	
	//enter main loop and process events
	glutMainLoop();

	return 0;
}