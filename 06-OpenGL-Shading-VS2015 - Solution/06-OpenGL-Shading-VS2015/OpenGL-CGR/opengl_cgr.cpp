#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <time.h>
#include <math.h>
#include <windows.h>

//ROTATION_SPEED1 and ROTATION_SPEED2 can be used to change the rotation speed of the two small outer spheres
#define ROTATION_SPEED1 -150.0
#define ROTATION_SPEED2 -300.0

//materialSpecular and materialShininess can be used to change the initial settings of the light source
static const GLfloat materialSpecular[] = {1.0, 0.0, 0.0, 1.0};
static const GLfloat materialShininess = 200.0;

//the following colors can be used to set either the ambient or diffuse material color
static const GLfloat red[] = {1.0, 0.0, 0.0, 1.0};
static const GLfloat green[] = {0.0, 1.0, 0.0, 1.0};
static const GLfloat blue[] = {0.0, 0.0, 1.0, 1.0};
static const GLfloat white[] = {1.0, 1.0, 1.0, 1.0};
static const GLfloat darkGray[] = {0.05, 0.05, 0.05, 1.0};
static const GLfloat black[] = {0.0, 0.0, 0.0, 1.0};

//use scenePosition to change the observers initial position in the scene
static const GLfloat scenePosition[] = {0.0, 0.0, -10.0};

//the rotationMatrix should be used to manipulate the observers actual rotated position
static GLdouble rotationMatrix[] = {1.0, 0.0, 0.0, 0.0,
	0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	0.0, 0.0, 0.0, 1.0};

//use lightPosition to change the light position in the scene
static GLfloat lightPosition[] = {1.0, 1.0, 1.0, 0.0};

//pause is used to stop or resume the animation
static int pause = 1;

//observerSystem defines if the light source is relative to the obeserver coordinate system or the sphere coordinate system
static int observerSystem = 0;

//scene rotation parameters
static GLfloat angleX = 30; 
static GLfloat angleY = -150; 
static int moving, startx, starty;

//window size parameters
static int windowWidth = 320;
static int windowHeight = 240;

static int frames = 0;
static double elapsedTime = 0.0;

//setup all initial settings for OpenGL
static void init(void) 
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, materialShininess);
}

//renders a sphere with the given radius at the specified position
static void renderSphere(double radius, double x, double y, double z) 
{
	glPushMatrix();
		glTranslated(x, y, z);
		//glutSolidSphere(radius, 20, 16);
		glutSolidTeapot(radius * 2);
	glPopMatrix();
}

//helper function to set materials (diffuse and ambient color) in a little bit "nicer" way
void setMaterial(const GLfloat *materialDiffuse, const GLfloat *materialAmbient)
{
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialAmbient);
   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialDiffuse);
}

double calcElapsedTime() {
	static long time = clock();
	long oldTime = time;
	double diffTime;
	time = clock();
	diffTime = ((double)(time - oldTime)) /
		((double)CLOCKS_PER_SEC);
	return diffTime;
}

void animate(double diffTime) {
	angleX += diffTime * ROTATION_SPEED1;
	angleY += diffTime * ROTATION_SPEED2;
}

void calcFPS(double diffTime) {
	elapsedTime += diffTime;
	frames++;

	if (elapsedTime > 1) {
		char buffer[256];
		double fps = (double) frames / elapsedTime;
		sprintf(buffer, "%f", fps);
		glutSetWindowTitle(buffer);
	    elapsedTime = 0.0;
		frames = 0;

	}
}

//renders the whole scene conatining three spheres (two small and one larger sphere)
static void display(void) 
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	double diffTime = calcElapsedTime();
	animate(diffTime);

	calcFPS(diffTime);

	glTranslated(scenePosition[0], scenePosition[1], scenePosition[2]);

	//glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	setMaterial(blue, darkGray);
	renderSphere(1.0, 0, 0, 0.0);

	glPushMatrix();
	    glRotated(angleY, 0.0, 1.0, 0.0);
		setMaterial(red, darkGray);
		renderSphere(0.5, -3, 0.0, 0.0);
	glPopMatrix();

	glPushMatrix();
		glRotated(angleX, 1.0, 0.0, 0.0);
		setMaterial(green, darkGray);
		renderSphere(0.5, 0, 2, 0.0);
	glPopMatrix();
	
	glutSwapBuffers();
}



static void idle(void) {
	glutPostRedisplay();
}

static void reshape (int w, int h) 
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, ((GLdouble)w) / ((GLdouble)h), 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

static void keyboard(unsigned char key, int x, int y) 
{
	switch (key) 
	{
		case 27:
			exit(0);
			break;
	}
}

int main(int argc, char** argv) 
{
	glutInit(&argc, argv);

	//init display mode (double buffer, RGB, z-buffer support)
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	//initialize window
	glutInitWindowSize(windowWidth, windowHeight); 
	glutCreateWindow("LightExample");
	init();

	//register callback functions
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);

	glutMainLoop();
	return 0;
}