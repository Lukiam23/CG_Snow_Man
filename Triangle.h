#ifndef  TRIANGLE_H
#define TRIANGLE_H

#include "Objeto.h"
#include "Material.h"
#include "Point.h"
class Triangle:public Objeto{
public:
	Point p1, p2, p3;
	Material material;
	Triangle();
	Triangle(Point,Point,Point, const Material&);
	struct Data intersect(Point, Vetor, int, float);
	Vetor calcColor(Point O, Vetor V, Vetor Ienv, float t_int, Light* light, bool kill);
	void changeToCam(Camera cam);
	bool simpleIntersect(Point, Vetor);
	void print();
	Point getCenter();	
};

#endif

