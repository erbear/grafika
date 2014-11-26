#pragma once

#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
typedef GLfloat point2[2];

class Kwadrat
{
private:
	point2 p1,p2;
	int v;
public:
	Kwadrat(point2, point2);
	~Kwadrat(void);
};
