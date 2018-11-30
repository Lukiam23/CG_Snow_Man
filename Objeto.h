#ifndef  Object_H
#define Object_H
#include "Point.h"
#include "Vetor.h"
#include "Light.h"
#include "Camera.h"

struct Data {
	int empty;
	float t_int;
	int indexSphere;
	float deltaRay;
};


class Objeto
{
public:
	virtual struct Data intersect(Point O, Vetor V, int k, float t) = 0;
	virtual Vetor calcColor(Point O, Vetor V, Vetor Ienv, float t_int,Light* light,bool kill) = 0;
	virtual void changeToCam(Camera cam) = 0;
	virtual bool simpleIntersect(Point, Vetor) = 0;
	virtual void print() = 0;
};
#endif
