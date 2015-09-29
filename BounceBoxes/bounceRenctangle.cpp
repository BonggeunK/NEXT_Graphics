#include <windows.h>
#include <gl\glut.h>

GLfloat x1 = 0.0f;
GLfloat y1 = 0.0f;
GLfloat x2 = -100.0f;
GLfloat y2 = 0.0f;
GLfloat x3 = 0.0f;
GLfloat y3 = -100.0f;
GLfloat x4 = -100.0f;
GLfloat y4 = -100.0f;

GLsizei rsize = 50.0f;

GLfloat x1step = 1.0f;
GLfloat y1step = 1.0f;
GLfloat x2step = -2.0f;
GLfloat y2step = 1.0f;
GLfloat x3step = 1.0f;
GLfloat y3step = -2.0f;
GLfloat x4step = -3.0f;
GLfloat y4step = -1.0f;

GLfloat window_width;
GLfloat window_height;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f,0.0f,0.0f);
	glRectf(x1,y1,x1+rsize,y1+rsize);
	glColor3f(0.0f, 1.0f, 0.0f);
	glRectf(x2, y2, x2 + rsize, y2 + rsize);
	glColor3f(0.0f, 0.0f, 1.0f);
	glRectf(x3, y3, x3 + rsize, y3 + rsize);
	glColor3f(0.0f, 0.0f, 0.0f);
	glRectf(x4, y4, x4 + rsize, y4 + rsize);
	glutSwapBuffers();
}

void TimerFunction(int value)
{
	// square 1
	if(x1> window_width -rsize || x1 < -window_width)
		x1step = -x1step;

	if(y1>window_height -rsize || y1 < -window_height)
		y1step = -y1step;

	if(x1 > window_width-rsize)
		x1 = window_width-rsize-1;

	if(y1 >window_height-rsize)
		y1 = window_height-rsize-1;

	x1 +=x1step;
	y1 +=y1step;

	// squre 2
	if (x2> window_width - rsize || x2 < -window_width)
		x2step = -x2step;

	if (y2>window_height - rsize || y2 < -window_height)
		y2step = -y2step;

	if (x2 > window_width - rsize)
		x2 = window_width - rsize - 1;

	if (y2 >window_height - rsize)
		y2 = window_height - rsize - 1;

	x2 += x2step;
	y2 += y2step;

	// squre 3
	if (x3> window_width - rsize || x3 < -window_width)
		x3step = -x3step;

	if (y3>window_height - rsize || y3 < -window_height)
		y3step = -y3step;

	if (x3 > window_width - rsize)
		x3 = window_width - rsize - 1;

	if (y3 >window_height - rsize)
		y3 = window_height - rsize - 1;

	x3 += x3step;
	y3 += y3step;

	// squre 4
	if (x4> window_width - rsize || x4 < -window_width)
		x4step = -x4step;

	if (y4>window_height - rsize || y4 < -window_height)
		y4step = -y4step;

	if (x4 > window_width - rsize)
		x4 = window_width - rsize - 1;

	if (y4 >window_height - rsize)
		y4 = window_height - rsize - 1;

	x4 += x4step;
	y4 += y4step;

	glutPostRedisplay();
	glutTimerFunc(1,TimerFunction,1);
}

void SetupRC(void) 
{	glClearColor(1.0f,1.0f,1.0f,1.0f);  }

void ChangeSize(GLsizei w, GLsizei h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<=h)
	{
		window_width = 100.0f;
		window_height = 100.0f*h/w;
		glOrtho (-100.0f, 100.0f, -window_height, window_height, 1.0, -1.0);
	}
	else
	{
		window_width = 100.0f*w/h;
		window_height = 100.0f;
		glOrtho (-window_width, window_width, -100.0f, 100.0f, 1.0, -1.0);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); 
}

void main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 
	glutInitWindowSize(800,600);
	glutCreateWindow("Bounce Rectangle"); 
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize); 
	glutTimerFunc(300,TimerFunction,1); 
    SetupRC();
	glutMainLoop();  	
	
}