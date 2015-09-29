#include <windows.h>
#include <gl\glut.h>

GLfloat x1 = 0.0f;
GLfloat y1 = 0.0f;
GLfloat z1 = -20.0f;
GLfloat x2 = -10.0f;
GLfloat y2 = 0.0f;
GLfloat z2 = -30.0f;
GLfloat x3 = 0.0f;
GLfloat y3 = -10.0f;
GLfloat z3 = -40.0f;

GLsizei rsize = 5.0f;

GLfloat x1step = 0.1f;
GLfloat y1step = 0.1f;
GLfloat z1step = 0.1f;
GLfloat x2step = -0.2f;
GLfloat y2step = 0.1f;
GLfloat z2step = -0.2f;
GLfloat x3step = 0.1f;
GLfloat y3step = -0.3f;
GLfloat z3step = 0.2f;

GLfloat window_width;
GLfloat window_height;
GLfloat window_far;
GLfloat window_near;

void DrawCube(int lx, int ly, int lz, int rx, int ry, int rz)
{
	// draw 4 surfaces strip
	glBegin(GL_QUAD_STRIP);

	glVertex3f(lx, ly, lz);
	glVertex3f(lx, ly, rz);
	glVertex3f(rx, ly, lz);
	glVertex3f(rx, ly, rz);
	glVertex3f(rx, ry, lz);
	glVertex3f(rx, ry, rz);
	glVertex3f(lx, ry, lz);
	glVertex3f(lx, ry, rz);
	glVertex3f(lx, ly, lz);
	glVertex3f(lx, ly, rz);

	glEnd();

	// draw bottom surface
	glBegin(GL_QUADS);

	glVertex3f(lx, ly, lz);
	glVertex3f(rx, ly, lz);
	glVertex3f(rx, ry, lz);
	glVertex3f(lx, ry, lz);

	glEnd();

	// draw top surface
	glBegin(GL_QUADS);

	glVertex3f(lx, ly, rz);
	glVertex3f(rx, ly, rz);
	glVertex3f(rx, ry, rz);
	glVertex3f(lx, ry, rz);

	glEnd();
}

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(1.0f, 0.0f, 0.0f);
	DrawCube(x1, y1, z1, x1 + rsize, y1 + rsize, z1 + rsize);

	glColor3f(0.0f, 1.0f, 0.0f);
	DrawCube(x2, y2, z2, x2 + rsize, y2 + rsize, z2 + rsize);

	glColor3f(0.0f, 0.0f, 1.0f);
	DrawCube(x3, y3, z3, x3 + rsize, y3 + rsize, z3 + rsize);

	glutSwapBuffers();
}

void TimerFunction(int value)
{
	// cube 1
	if (x1 > window_width - rsize || x1 < -window_width)
		x1step = -x1step;

	if (y1 > window_height - rsize || y1 < -window_height)
		y1step = -y1step;

	if (z1 > window_near - rsize || z1 < window_far + rsize)
		z1step = -z1step;

	if (x1 > window_width - rsize)
		x1 = window_width - rsize - 1;

	if (y1 > window_height - rsize)
		y1 = window_height - rsize - 1;

	x1 += x1step;
	y1 += y1step;
	z1 += z1step;

	// cube 2
	if (x2 > window_width - rsize || x2 < -window_width)
		x2step = -x2step;

	if (y2 > window_height - rsize || y2 < -window_height)
		y2step = -y2step;

	if (z2 > window_near - rsize || z2 < window_far + rsize)
		z2step = -z2step;

	if (x2 > window_width - rsize)
		x2 = window_width - rsize - 1;

	if (y2 > window_height - rsize)
		y2 = window_height - rsize - 1;

	x2 += x2step;
	y2 += y2step;
	z2 += z2step;

	// cube 3
	if (x3 > window_width - rsize || x3 < -window_width)
		x3step = -x3step;

	if (y3 > window_height - rsize || y3 < -window_height)
		y3step = -y3step;

	if (z3 > window_near - rsize || z3 < window_far + rsize)
		z3step = -z3step;

	if (x3 > window_width - rsize)
		x3 = window_width - rsize - 1;

	if (y3 > window_height - rsize)
		y3 = window_height - rsize - 1;

	x3 += x3step;
	y3 += y3step;
	z3 += z3step;

	glutPostRedisplay();
	glutTimerFunc(1, TimerFunction, 1);
}

void SetupRC(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void ChangeSize(GLsizei w, GLsizei h)
{
	GLfloat fAspect;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);

	fAspect = (GLfloat)w / (GLfloat)h;
	window_far = -50.0f;
	window_near = 1.0f;

	gluPerspective(90.0f, fAspect, window_near, window_far);

	if (w <= h)
	{
		window_width = 10.0f;
		window_height = 10.0f*h / w;
	}
	else
	{
		window_width = 10.0f*w / h;
		window_height = 10.0f;
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Bounce Cube");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(33, TimerFunction, 1);
	SetupRC();
	glutMainLoop();
}