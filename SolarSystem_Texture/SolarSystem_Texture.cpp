#include <windows.h>
#include <gl/glut.h>
#include <math.h>
#include <gl/gltools.h>
#include <GL/GLAUX.H>

#define GL_PI 3.1415f
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

GLUquadricObj *sun, *earth, *moon;

GLfloat amb[] = { 0.3f, 0.3f, 0.3f, 1.0f };
GLfloat dif[] = { 0.9f, 0.9f, 0.9f, 1.0f };
GLfloat lightPos[] = { -50.0f, 50.0f, 100.0f, 1.0f };

AUX_RGBImageRec * texRec[3];
GLuint texID[3];

void SetupRC(void)
{
	glEnable(GL_DEPTH_TEST);

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
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, texID[0]);
	glColor3f(1.0f, 1.0f, 0.0f);
	gluSphere(sun, 10.0f, 15, 15);

	glPushMatrix();
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
	glTranslatef(30.0f, 0.0f, 0.0f);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, texID[1]);
	glColor3f(0.0f, 0.0f, 1.0f);
	gluSphere(earth, 6.0f, 15, 15);

	glRotatef(5 * fElect1, 0.0f, 1.0f, 0.0f);
	glTranslatef(-10.0f, 0.0f, 0.0f);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, texID[2]);
	glColor3f(0.4f, 0.4f, 0.4f);
	gluSphere(moon, 2.0f, 15, 15);
	glPopMatrix();

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);

	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glEnable(GL_LIGHT0);

	fElect1 += 5.0f;
	if (fElect1 > 360.0f)
		fElect1 = 0.0f;

	glutSwapBuffers();
}

void LoadTextures(void)
{
	sun = gluNewQuadric();
	earth = gluNewQuadric();
	moon = gluNewQuadric();

	gluQuadricTexture(sun, GL_TRUE);
	gluQuadricTexture(earth, GL_TRUE);
	gluQuadricTexture(moon, GL_TRUE);

	texRec[0] = auxDIBImageLoad("sun.bmp");
	texRec[1] = auxDIBImageLoad("earth.bmp");
	texRec[2] = auxDIBImageLoad("moon.bmp");
	glGenTextures(3, texID);

	for (int i = 0; i < 3; i++){
		glBindTexture(GL_TEXTURE_2D, texID[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, texRec[i]->sizeX, texRec[i]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texRec[i]->data);
		glEnable(GL_TEXTURE_2D);
	}

	for (int i = 0; i < 3; i++){
		if (texRec[i]->data)
			free(texRec[i]->data);
		free(texRec[i]);
	}
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
	glutCreateWindow("Solar System 2");

	glutReshapeFunc(ChangeSize);
	LoadTextures();
	glutTimerFunc(33, TimerFunc, 1);
	glutDisplayFunc(RenderScene);

	SetupRC();
	glutMainLoop();
}