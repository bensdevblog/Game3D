// Game3D.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define MOVE_FWD 'w'
#define MOVE_LEFT 'a'
#define MOVE_BACK 's'
#define MOVE_RIGHT 'd'

#define EXIT_KEY 27
#define JUMP_KEY 32

using namespace std;

int getRand(int first, int last);

/* Global Variables */

// angle of rotation for the camera direction
float cam_angle = 0.0f;

// actual vector representing the camera's direction
float cam_x_vec = 0.0f;
float cam_y_vec = 0.0f;
float cam_z_vec = -1.0f;

// XYZ position of the camera
float cam_x = 0.0f;
float cam_y = 1.0f;
float cam_z = 5.0f;

// View states, will be 0 when no key is pressed
float deltaAngle = 0.0f;
float deltaMove = 0.0f;
int xOrigin = -1;
int yOrigin = -1;

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

void drawSnowMan() 
{

	glColor3f(1.0f, 1.0f, 1.0f);

	// Draw Body
	glTranslatef(0.0f, 0.75f, 0.0f);
	glutSolidSphere(0.75f, 20, 20);

	// Draw Head
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.25f, 20, 20);

	// Draw Eyes
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f, 10, 10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f, 10, 10);
	glPopMatrix();

	// Draw Nose
	glColor3f(1.0f, 0.5f, 0.5f);
	glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
	glutSolidCone(0.08f, 0.5f, 10, 2);
}

void drawBuilding(float height, float width)
{
	glBegin(GL_QUADS);
	{
		glColor3f(0.6, 0.3, 0.0);

		glVertex3f(width, 0.0f, width);
		glVertex3f(width * 2, 0.0f, width);
		glVertex3f(width * 2, height, width);
		glVertex3f(width, height, width);

		glVertex3f(width, 0.0f, width * 2);
		glVertex3f(width * 2, 0.0f, width * 2);
		glVertex3f(width * 2, height, width * 2);
		glVertex3f(width, height, width * 2);

		glColor3f(0.3, 0.4, 0.0);

		glVertex3f(width, 0.0f, width * 2);
		glVertex3f(width, 0.0f, width);
		glVertex3f(width, height, width);
		glVertex3f(width, height, width * 2);

		glVertex3f(width * 2, 0.0f, width);
		glVertex3f(width * 2, 0.0f, width * 2);
		glVertex3f(width * 2, height, width * 2);
		glVertex3f(width * 2, height, width);
	}
	glEnd();
}

void computePos(float deltaMove) 
{

	cam_x += deltaMove * cam_x_vec * 0.1f;
	cam_z += deltaMove * cam_z_vec * 0.1f;
}

void computeDir(float deltaAngle) 
{

	cam_angle += deltaAngle;
	cam_x_vec = sin(cam_angle);
	cam_z_vec = -cos(cam_angle);
}

void renderScene(void) 
{

	if (deltaMove)
		computePos(deltaMove);
	
	if (deltaAngle)
		computeDir(deltaAngle);

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	// Set the camera
	gluLookAt(cam_x, cam_y + cam_y_vec, cam_z,
			 cam_x + cam_x_vec, cam_y + cam_y_vec, cam_z + cam_z_vec,
			 0.0f, 1.0f, 0.0f);

	// Draw ground
	glBegin(GL_QUADS);
	{
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-500.0f, 0.0f, -500.0f);
		glVertex3f(-500.0f, 0.0f, 500.0f);
		glColor3f(0.1f, 1.0f, 0.1f);
		glVertex3f(500.0f, 0.0f, 500.0f);
		glVertex3f(500.0f, 0.0f, -500.0f);
	}
	glEnd();

	// Draw 36 SnowMen
	/*
	for (int i = -3; i < 3; i++) 
	{
		for (int j = -3; j < 3; j++) 
		{
			glPushMatrix();
			glTranslatef(i*10.0, 0, j * 10.0);
			drawSnowMan();
			glPopMatrix();
		}
	} */

	//Draw 36 buildings
	float spacing = 20.0f;
	float bldg_height = 30.0f;
	float bldg_width = 10.0f;
	float h_offset = 0.0f;
	float w_offset = 0.0f;

	int iterations = 0;

	for (int i = -15; i < 15; i++)
	{
		for (int j = -6; j < 6; j++)
		{
			glPushMatrix();
			glTranslatef(i * spacing, 0, j * spacing);
			if (iterations % 20 == 0 && iterations % 40 == 0)
			{
				h_offset = 15.0f;
				w_offset = 0.0f;
				drawBuilding(bldg_height + h_offset, bldg_width + w_offset);
			}
			else if (iterations % 10 == 0 && iterations % 20 == 0)
			{
				h_offset = -15.0f;
				w_offset = 1.5f;
				drawBuilding(bldg_height + h_offset, bldg_width + w_offset);
			}
			else if (iterations % 5 == 0 && iterations % 10)
			{
				h_offset = 10.0f;
				w_offset = 1.0f;
				drawBuilding(bldg_height + h_offset, bldg_width + w_offset);
			}
			else if (iterations % 2 == 0 && iterations % 8)
			{
				h_offset = -10.0f;
				w_offset = 1.5f;
				drawBuilding(bldg_height + h_offset, bldg_width + w_offset);
			}
			else if (iterations % 4 == 0)
			{
				h_offset = 5.0f;
				w_offset = 0.0f;
				drawBuilding(bldg_height + h_offset, bldg_width + w_offset);
			}
			else if (iterations % 2 == 0)
			{
				h_offset = -5.0f;
				w_offset = 0.0f;
				drawBuilding(bldg_height + h_offset, bldg_width + w_offset);
			}
			else
			{
				drawBuilding(bldg_height, bldg_width);
			}
			glPopMatrix();

			iterations++;
			h_offset = 0.0f;
			w_offset = 0.0f;
		}
	}
	glutSwapBuffers();
}
/* Handle key press events */
void keyPress(unsigned char key, int xx, int yy) 
{

	switch (key)
	{
		case MOVE_FWD:
			deltaMove = 0.5f;
			break;
		case MOVE_LEFT:
			deltaAngle = -0.01f;
			break;
		case MOVE_BACK:
			deltaMove = -0.5f;
			break;
		case MOVE_RIGHT:
			deltaAngle = 0.01f;
			break;
		case JUMP_KEY:
			jumping = true;
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
			deltaMove = 0.0f;
			break;
		case MOVE_LEFT:
			deltaAngle = 0.0f;
			break;
		case MOVE_BACK:
			deltaMove = 0.0f;
			break;
		case MOVE_RIGHT:
			deltaAngle = 0.0f;
			break;
		case JUMP_KEY:
			//cam_y_vec = 0.0f;
			break;
	}
}

/* Special key presses, UP, DOWN, LEFT, RIGHT F12, etc.. */
void specialKeyPress(int key, int xx, int yy) 
{
	switch (key) {
	case GLUT_KEY_LEFT: deltaAngle = -0.01f; break;
	case GLUT_KEY_RIGHT: deltaAngle = 0.01f; break;
	case GLUT_KEY_UP: deltaMove = 0.5f; break;
	case GLUT_KEY_DOWN: deltaMove = -0.5f; break;
	}
}

/* Special key releases */
void specialKeyRelease(int key, int x, int y) 
{

	switch (key) {
	case GLUT_KEY_LEFT :
	case GLUT_KEY_RIGHT : deltaAngle = 0.0f;break;
	case GLUT_KEY_UP:
	case GLUT_KEY_DOWN: deltaMove = 0; break;
	}
}

void mouseMove(int x, int y) 
{
	
	// this will only be true when the left button is down
	if (xOrigin >= 0 && yOrigin >= 0) {

		// update deltaAngle
		deltaAngle = (x - xOrigin) * 0.00001f;
		// update camera's direction
		cam_x_vec = sin(cam_angle + deltaAngle);
		cam_z_vec = -cos(cam_angle + deltaAngle);
	} 

}

void mouseButton(int button, int state, int x, int y) 
{
	// only start motion if the left button is pressed
	if (button == GLUT_LEFT_BUTTON) 
	{

		// when the button is released
		if (state == GLUT_UP) 
		{
			deltaAngle = 0;
			xOrigin = -1; //Reset xOrigin on button release
		}
		else  
		{// state = GLUT_DOWN
			yOrigin = y;
			xOrigin = x;
		}
	} 
}

void timer(int val)
{
	int interval = 15;
	if (jumping && cam_y_vec < 2.25f)
	{
		cam_y_vec += 0.15f;
		printf("CAM Y VECTOR: %.2f\n", cam_y_vec);
		if (cam_y_vec == 2.25f)
		{
			jumping = false;
		}
	}
	
	if (!jumping && cam_y_vec >= 0)
	{
		cam_y_vec -= 0.15f;
	}
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

int main(int argc, char **argv) 
{

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Lighthouse3D - GLUT Tutorial");
	glutFullScreen(); //lolfullscreenz

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

