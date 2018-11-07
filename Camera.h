#ifndef Camera_H
#define Camera_H

#include "Point.h"
class Camera
{
private:
	double Mw_c[4][4];
public:
	Camera();
	Camera(Point O, Point lookat,Point viewup);
	void worldToCamera(Point* p);
	void printM();
};

#endif

