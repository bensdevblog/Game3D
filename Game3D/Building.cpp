#include "stdafx.h"
#include "models.h"

using namespace std;


Building::Building(float w, float h)
{
	width = w;
	height = h;

}

void Building::draw()
{
	glBegin(GL_QUADS);
	{
		glColor3f(0.3, 0.2, 0.0);

		glVertex3f(width, 0.0f, width);
		glVertex3f(width * 2, 0.0f, width);
		glVertex3f(width * 2, height, width);
		glVertex3f(width, height, width);

		glVertex3f(width, 0.0f, width * 2);
		glVertex3f(width * 2, 0.0f, width * 2);
		glVertex3f(width * 2, height, width * 2);
		glVertex3f(width, height, width * 2);

		glColor3f(0.4, 0.2, 0.0);

		glVertex3f(width, 0.0f, width * 2);
		glVertex3f(width, 0.0f, width);
		glVertex3f(width, height, width);
		glVertex3f(width, height, width * 2);

		glVertex3f(width * 2, 0.0f, width);
		glVertex3f(width * 2, 0.0f, width * 2);
		glVertex3f(width * 2, height, width * 2);
		glVertex3f(width * 2, height, width);

		glColor3f(0.2f, 0.2f, 0.2f);

		glVertex3f(width, height, width);
		glVertex3f(width * 2, height, width);
		glVertex3f(width * 2, height, width * 2);
		glVertex3f(width, height, width * 2);
	}
	glEnd();
}