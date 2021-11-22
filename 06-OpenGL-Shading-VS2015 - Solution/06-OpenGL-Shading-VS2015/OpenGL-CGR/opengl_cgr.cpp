#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <time.h>
#include <math.h>
#include <windows.h>
GLUquadricObj* quadratic = gluNewQuadric();

//ROTATION_SPEED1 and ROTATION_SPEED2 can be used to change the rotation speed of the two small outer spheres
static float ROTATION_SPEED1 = -50.0;
static float ROTATION_SPEED2 = -100.0;


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
static GLfloat lightPosition[] = {2.0, 2.0, 4.0, 0.0};

//pause is used to stop or resume the animation
//static int pause = 1;

//observerSystem defines if the light source is relative to the obeserver coordinate system or the sphere coordinate system
//static int observerSystem = 0;

//scene rotation parameters
static GLfloat angleX = 45;
static GLfloat angleY = -150; 
static float moving, startx, starty;
static float part1 = 0, part2 = -45, part3 = -45, part31 = 0, part4 = -45, part5 = -45;

//window size parameters
static int windowWidth = 320*3;
static int windowHeight = 240*3;

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
/*static void renderSphere(double radius, double x, double y, double z)
{
	glPushMatrix();
		glTranslated(x, y, z);
		//glutSolidSphere(radius, 20, 16);
		glutSolidTeapot(radius * 2);
	glPopMatrix();
}*/

static void renderRobot(){}

//helper function to set materials (diffuse and ambient color) in a little bit "nicer" way
void setMaterial(const GLfloat *materialDiffuse, const GLfloat *materialAmbient)
{
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialAmbient);
   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialDiffuse);
}

void drawCircle()
{
	int triangleAmount = 180;
	glBegin(GL_TRIANGLE_FAN);
	setMaterial(white, white);
	glVertex3f(0.0, 0.0, 0.0);
	for (int i = 0; i <= triangleAmount + 1; i++) {
		glVertex2f(
			(1.0 * cos(i * 6.28 / triangleAmount)),
			(1.0 * sin(i * 6.28 / triangleAmount))
		);
	}
	glEnd();
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

bool flag1 = TRUE;
bool flag2 = TRUE;

void reset() {
	flag1 = TRUE;
	flag2 = TRUE;
}

void animate(double diffTime) {
	if (flag1) {
		if (part4 < -100) {
			flag1 = FALSE;
		}
		part4 += diffTime * ROTATION_SPEED1;
		part31 += diffTime * ROTATION_SPEED2;

	}
	if (!flag1 && flag2) {
		if (part4 > -45) {
			flag2 = FALSE;
		}
		part4 -= diffTime * ROTATION_SPEED1;
		part31 -= diffTime * ROTATION_SPEED2;
	}
	if (!flag1 && !flag2) {
		reset();
	}
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

static void renderBase(double x, double y, double z) {
	//renders a cylinder at the specified position
	setMaterial(red, red);
	glPushMatrix();
		glScalef(5.0, -0.2, 1.0);
		glTranslated(x, y, z);
		glRotatef(90, 1, 0, 0);
		gluCylinder(quadratic, 0.3, 0.3, 2, 100, 100);
	glPopMatrix();
}

static void renderWheight(double x, double y, double z) {
	//renders a cylinder at the specified position
	setMaterial(white, white);
	glPushMatrix();
		glTranslated(x, y, z);
		glPushMatrix();
			glScalef(3, 0.5, 0.5);
			glRotatef(90, 0, 1, 0);
			gluCylinder(quadratic, 0.3, 0.3, 2, 100, 100);
		glPopMatrix();
		glPushMatrix();
			glTranslated(0.82,0,0);
			glPushMatrix();
				glScalef(0.2, 6, 2);
				glRotatef(90, 0, 1, 0);
				gluCylinder(quadratic, 0.3, 0.3, 2, 100, 100);
				glTranslated(0, 0, 20);
				gluCylinder(quadratic, 0.3, 0.3, 2, 100, 100);
				glPushMatrix();
					//big plate
					glScalef(0.3, 0.3, 1);
					glRotatef(90, 0, 0, 1);
					drawCircle();
					glTranslatef(0, 0, 1.5);
					drawCircle();
					//medium plate
					glScalef(0.5, 0.7, 1);
					drawCircle();
					glTranslatef(0, 0, 1.5);
					drawCircle();
					//small plate
					glScalef(1.2,1.2,1);
					drawCircle();
					glTranslatef(0, 0, 3);
					drawCircle();
					//other sides small plate
					glTranslatef(0, 0, -29.9);
					drawCircle();
					glTranslatef(0, 0, 1.5);
					drawCircle();
					//medium Plate
					glTranslatef(0, 0, 0.1);
					glScalef(1.3, 1.2, 1);
					drawCircle();
					glTranslatef(0, 0, 1.5);
					drawCircle();
					//big plate
					glTranslatef(0, 0, 1.0);
					glScalef(1.25, 1.0, 1);
					drawCircle();
					glTranslatef(0, 0, 1.5);
					drawCircle();
				glPopMatrix();
				glPushMatrix();
					glTranslatef(0, 0, 2);
					glScalef(1, 0.8, 1);
					gluCylinder(quadratic, 0.3, 0.3, 2, 100, 100);
					glTranslatef(0,0,-24);
					gluCylinder(quadratic, 0.3, 0.3, 2, 100, 100);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(0, 0, 4);
					glScalef(1, 0.6, 1);
					gluCylinder(quadratic, 0.3, 0.3, 2, 100, 100);
					glTranslatef(0, 0, -28);
					gluCylinder(quadratic, 0.3, 0.3, 2, 100, 100);
				glPopMatrix();
			glPopMatrix();
			drawCircle;
		glPopMatrix();
	glPopMatrix();
	
}

static void renderRobot(double x, double y, double z) {
	glPushMatrix();
		glTranslatef(0.0, -3.0, 0.0);
		renderBase(0, 0, 0);
		glTranslated(x, y, z);
		glPushMatrix();
			glTranslatef(0.0, 0.3, 0.0);
			glRotatef(90, 0.0, 0.0, 1.0);
			glTranslatef(1.0, 0.0, 0.0);
			glPushMatrix();
				glScalef(2.0, 0.4, 1.0);
				glutSolidCube(1.0);
			glPopMatrix();
			glTranslatef(1.0, 0.0, 0.0);
			glRotatef((GLfloat)part2, 0.0, 0.0, 1.0);
			glTranslatef(1.0, 0.0, 0.0);
			glPushMatrix();
				glScalef(2.0, 0.4, 1.0);
				glutSolidCube(1.0);
			glPopMatrix();
			glTranslatef(1.0, 0.0, 0.0);
			glRotatef((GLfloat)part3, 0.0, 0.0, 1.0);
			glRotatef((GLfloat)part31, 1.0, 0.0, 0.0);
			glTranslatef(1.0, 0.0, 0.0);
			glPushMatrix();
				glScalef(2.0, 0.4, 1.0);
				glutSolidCube(1.0);
			glPopMatrix();
			glTranslatef(1.0, 0.0, 0.0);
			glRotatef((GLfloat)part4, 0.0, 0.0, 1.0);
			glTranslatef(1.0, 0.0, 0.0);
			glPushMatrix();
				glScalef(2.0, 0.4, 1.0);
				glutSolidCube(1.0);
			glPopMatrix();
			glTranslatef(1.0, 0.0, 0.0);
			glRotatef((GLfloat)part5, 0.0, 0.0, 1.0);
			glTranslatef(1.0, 0.0, 0.0);
			glPushMatrix();
				glScalef(2.0, 0.4, 1.0);
				glutSolidCube(1.0);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(1.3, 0, 0);
				glScalef(0.6, 0.4, 0.3);
				glutSolidCube(1.0);
			glPopMatrix();
			glPushMatrix();
				glRotatef(90, 0, 0, 1);
				glTranslatef(0.2, -0.4, 0);
				glScalef(0.4, 0.4, 1);
				renderWheight(-3.5, -2.5, 0);
			glPopMatrix();
		glPopMatrix();
		

		
	glPopMatrix();
}

static void display(void) 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	double diffTime = calcElapsedTime();
	animate(diffTime);

	calcFPS(diffTime);
	
	glTranslated(scenePosition[0], scenePosition[1], scenePosition[2]);

	//glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	glClear(GL_COLOR_BUFFER_BIT);
	renderRobot(0.0, 0.0, 0.0);
	//renderWheight(0,0,0);
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
		case 'v':
			ROTATION_SPEED1 *= 2;
			ROTATION_SPEED2 *= 2;
			break;
		case 's':
			ROTATION_SPEED1 /= 2;
			ROTATION_SPEED2 /= 2;
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
