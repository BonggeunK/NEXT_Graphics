#include <windows.h>
#include <gl/glut.h>
#include <math.h>
#include <gl/gltools.h>


#define GL_PI 3.1415f
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

void SetupRC(void)
{
	GLfloat ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat diffuseLight[] = { 0.9f, 0.9f, 0.9f, 1.0f };

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	glEnable(GL_LIGHTING);

	// Sun light
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);

	GLfloat lightPos[] = { 0.0f, 0.0f, -100.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glEnable(GL_LIGHT0);
	
	// supplementary light
	GLfloat ambientLight1[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat diffuseLight1[] = { 0.2f, 0.2f, 0.2f, 1.0f };

	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight1);

	GLfloat lightPos1[] = { 0.0f, 0.0f, -85.0f, 1.0f };
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
	glEnable(GL_LIGHT1);

	glEnable(GL_COLOR_MATERIAL);

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

}

void TimerFunc(int value)
{
	glutPostRedisplay();
	glutTimerFunc(33, TimerFunc, 1);
}


void RenderScene(void)
{
	static GLfloat fElect1 = 0.0f;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -100.0f);
	glColor3ub(255, 255, 0);
	glutSolidSphere(10.0f, 15, 15);

	glPushMatrix();
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
	glTranslatef(30.0f, 0.0f, 0.0f);
	glColor3ub(0, 0, 255);
	glutSolidSphere(6.0f, 15, 15);

	glRotatef(5*fElect1, 0.0f, 1.0f, 0.0f);
	glTranslatef(-10.0f, 0.0f, 0.0f);
	glColor3ub(130, 130, 130);
	glutSolidSphere(2.0f, 15, 15);
	glPopMatrix();

	fElect1 += 5.0f;
	if (fElect1 > 360.0f)
		fElect1 = 0.0f;

	glutSwapBuffers();
}

void KeyControl(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
		xRot -= 5.0f;

	if (key == GLUT_KEY_DOWN)
		xRot += 5.0f;

	if (key == GLUT_KEY_LEFT)
		yRot -= 5.0f;

	if (key == GLUT_KEY_RIGHT)
		yRot += 5.0f;

	glutPostRedisplay();
}


void ChangeSize(int w, int h)
{
	GLfloat fAspect;

	glViewport(0, 0, w, h);

	fAspect = (GLfloat)w / (GLfloat)h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0f, fAspect, 1.0f, 500.f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -200.0f);
}

void main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(512, 512);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Solar System 1");

	glutReshapeFunc(ChangeSize);
	glutTimerFunc(33, TimerFunc, 1);
	glutSpecialFunc(KeyControl);
	glutDisplayFunc(RenderScene);

	SetupRC();
	glutMainLoop();
}