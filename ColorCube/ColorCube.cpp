#include <windows.h>
#include <gl/glut.h>
#include <math.h>

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

void SetupRC(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_DEPTH_TEST);
}

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glShadeModel(GL_SMOOTH);

	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	// drwa four strip surfaces
	glBegin(GL_QUAD_STRIP);
	glColor3ub((GLubyte)0, (GLubyte)0, (GLubyte)0);
	glVertex3f(-100.0f, -100.0f, -100.0f);

	glColor3ub((GLubyte)0, (GLubyte)255, (GLubyte)0);
	glVertex3f(-100.0f, -100.0f, 100.0f);

	glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)0);
	glVertex3f(100.0f, -100.0f, -100.0f);

	glColor3ub((GLubyte)255, (GLubyte)255, (GLubyte)0);
	glVertex3f(100.0f, -100.0f, 100.0f);

	glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)255);
	glVertex3f(100.0f, 100.0f, -100.0f);

	glColor3ub((GLubyte)255, (GLubyte)255, (GLubyte)255);
	glVertex3f(100.0f, 100.0f, 100.0f);

	glColor3ub((GLubyte)0, (GLubyte)0, (GLubyte)255);
	glVertex3f(-100.0f, 100.0f, -100.0f);

	glColor3ub((GLubyte)0, (GLubyte)255, (GLubyte)255);
	glVertex3f(-100.0f, 100.0f, 100.0f);
	
	glColor3ub((GLubyte)0, (GLubyte)0, (GLubyte)0);
	glVertex3f(-100.0f, -100.0f, -100.0f);

	glColor3ub((GLubyte)0, (GLubyte)255, (GLubyte)0);
	glVertex3f(-100.0f, -100.0f, 100.0f);
	glEnd();

	// draw bottom surface
	glBegin(GL_QUADS);
	glColor3ub((GLubyte)0, (GLubyte)0, (GLubyte)0);
	glVertex3f(-100.0f, -100.0f, -100.0f);

	glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)0);
	glVertex3f(100.0f, -100.0f, -100.0f);

	glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)255);
	glVertex3f(100.0f, 100.0f, -100.0f);

	glColor3ub((GLubyte)0, (GLubyte)0, (GLubyte)255);
	glVertex3f(-100.0f, 100.0f, -100.0f);
	glEnd();

	// draw top surface
	glBegin(GL_QUADS);
	glColor3ub((GLubyte)0, (GLubyte)255, (GLubyte)0);
	glVertex3f(-100.0f, -100.0f, 100.0f);

	glColor3ub((GLubyte)255, (GLubyte)255, (GLubyte)0);
	glVertex3f(100.0f, -100.0f, 100.0f);

	glColor3ub((GLubyte)255, (GLubyte)255, (GLubyte)255);
	glVertex3f(100.0f, 100.0f, 100.0f);

	glColor3ub((GLubyte)0, (GLubyte)255, (GLubyte)255);
	glVertex3f(-100.0f, 100.0f, 100.0f);
	glEnd();


	glPopMatrix();

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
	GLfloat nRange = 300.0f;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);

	if (w <= h)
		glOrtho(-nRange, nRange, -nRange * h / w, nRange * h / w, -nRange, nRange);
	else
		glOrtho(-nRange * w / h, nRange * w / h, -nRange, nRange, -nRange, nRange);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(512, 512);
	glutCreateWindow("Color Cube");
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(KeyControl);
	glutDisplayFunc(RenderScene);

	SetupRC();
	glutMainLoop();
}