// Game3D.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "models.h"
#include "camera.h"

#define MOVE_FWD 'w'
#define MOVE_LEFT 'a'
#define MOVE_BACK 's'
#define MOVE_RIGHT 'd'
#define DEVELOPER_VIEW 'k'

#define EXIT_KEY 27
#define JUMP_KEY 32

using namespace std;

int getRand(int first, int last);

Camera camera;
boolean jumping = false;

void changeSize(int w, int h) 
{
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 500.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void renderScene(void) 
{
	if (camera.getDeltaMove())
		camera.computePos(camera.getDeltaMove());

	if (camera.getDeltaAngle())
		camera.computeDir(camera.getDeltaAngle());

	if (camera.getDeltaHeight())
		camera.computeHeight(camera.getDeltaHeight());

	if (camera.getPitch())
		camera.computePitch(camera.getPitch());

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	// Set the camera
	gluLookAt(camera.getCamX(), 
		camera.getCamY() + camera.getYvector(), 
		camera.getCamZ(),
		camera.getCamX() + camera.getXvector(), 
		camera.getCamY() + camera.getYvector() + camera.getPitch(), 
		camera.getCamZ() + camera.getZvector(),
		0.0f, 1.0f, 0.0f);

	// Draw ground
	glBegin(GL_QUADS);
	{
		glColor3f(0.5f, 0.5f, 0.5f);
		glVertex3f(-500.0f, 0.0f, -500.0f);
		glVertex3f(-500.0f, 0.0f, 500.0f);
		glColor3f(0.3f, 0.3f, 0.3f);
		glVertex3f(500.0f, 0.0f, 500.0f);
		glVertex3f(500.0f, 0.0f, -500.0f);
	}
	glEnd();

	//Draw 36 buildings
	float spacing = 20.0f;
	float bldg_height = 30.0f;
	float bldg_width = 10.0f;

	int iterations = 0;

	for (int i = -15; i < 15; i++)
	{
		for (int j = -6; j < 6; j++)
		{
			glPushMatrix();
			glTranslatef(i * spacing, 0, j * spacing);

			Building building(bldg_width, bldg_height);
			building.draw();
			glPopMatrix();
		}
	}

	/* Display coordinates if camera is in developer mode.*/
	if (camera.isDevView())
		camera.drawCameraInfo();

	glutSwapBuffers();
}
/* Handle key press events */
void keyPress(unsigned char key, int xx, int yy) 
{

	switch (key)
	{
		case MOVE_FWD:
			camera.setDeltaMove(0.1f);
			break;
		case MOVE_LEFT:
			camera.setDeltaAngle(-0.005f);
			break;
		case MOVE_BACK:
			camera.setDeltaMove(-0.1f);
			break;
		case MOVE_RIGHT:
			camera.setDeltaAngle(0.005f);
			break;
		case JUMP_KEY:
			camera.jumpState(true); //Jump
			break;
		case DEVELOPER_VIEW:
			if (!camera.isDevView())
				camera.devState(true);
			else
				camera.devState(false);
				camera.setCamY(1.0f);
			break;
		case EXIT_KEY:
			exit(0);
	}
}

/* Handle key release events */
void keyRelease(unsigned char key, int xx, int yy)
{
	switch (key)
	{
		case MOVE_FWD:
			camera.setDeltaMove(0.0f);
			break;
		case MOVE_LEFT:
			camera.setDeltaAngle(0.0f);
			break;
		case MOVE_BACK:
			camera.setDeltaMove(0.0f);
			break;
		case MOVE_RIGHT:
			camera.setDeltaAngle(0.0f);
			break;
		case JUMP_KEY:
			//Do nothing.
			break;
	}
}

/* Special key presses, UP, DOWN, LEFT, RIGHT F12, etc.. */
void specialKeyPress(int key, int x, int y) 
{
	switch (key)
	{
		case GLUT_KEY_UP:
			camera.setDeltaHeight(0.1f);
			break;
		case GLUT_KEY_DOWN:
			camera.setDeltaHeight(-0.1f);
			break;
	}
}

/* Special key releases */
void specialKeyRelease(int key, int x, int y) 
{
	switch (key)
	{
		case GLUT_KEY_UP:
			camera.setDeltaHeight(0.0f);
			break;
		case GLUT_KEY_DOWN:
			camera.setDeltaHeight(0.0f);
			break;
	}
}

void mouseMove(int x, int y) 
{
	/*
	if (x < camera.getXorigin())
	{
		camera.setDeltaAngle(-0.001f);
	}

	if (x > camera.getXorigin())
	{
		camera.setDeltaAngle(0.001f);
	} 

	*/

	if (y < camera.getYorigin())
	{
		camera.setPitch(0.3f);
	}

	if (y > camera.getYorigin())
	{
		camera.setPitch(-0.3f);
	}

}

void mouseButton(int button, int state, int x, int y) 
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			//camera.setXorigin((float)x);
			camera.setYorigin((float)y);
		}

		if (state == GLUT_UP)
		{
			//camera.setDeltaAngle(0.0f);
			camera.setPitch(0.0f);
		}
	}
}

/* Animation timer */
void timer(int val)
{
	int interval = 15;

	//Listen for jump events
	camera.jump();

	glutTimerFunc(interval, timer, val);
}

int getRand(int first, int last)
{
	static int firstTime = 1;
	int amountOfNumbers;

	if (firstTime == 1)
	{
		//first time in this function, seed the random number generator
		firstTime = 0;
		srand(time(NULL));
	}

	amountOfNumbers = last - first + 1;
	return(rand() % amountOfNumbers + first);
}

void initCamera()
{
	camera.setAngleOfRot(0.0f);

	camera.setCamX(0.0f);
	camera.setCamY(1.0f);
	camera.setCamZ(5.0f);

	camera.setXvector(0.0f);
	camera.setYvector(0.0f);
	camera.setZvector(-1.0f);

	camera.setDeltaAngle(0.0f);
	camera.setDeltaMove(0.0f);

	camera.devState(false);
}

int main(int argc, char **argv) 
{

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Ben's 3D.. thing.");
	glutFullScreen(); //lolfullscreenz

	initCamera(); //Initialize camera.

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(keyPress);
	glutKeyboardUpFunc(keyRelease);
	glutSpecialFunc(specialKeyPress);
	glutSpecialUpFunc(specialKeyRelease);

	glutTimerFunc(0, timer, 0);

	// here are the two new functions
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}

