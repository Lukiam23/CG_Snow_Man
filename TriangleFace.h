#ifndef  TRIANGLE_H
#define TRIANGLE_H

#include "Objeto.h"
#include "Material.h"
#include "Point.h"
class TriangleFace:public Objeto{
public:
	Point x, y, z;
	Material material;
	TriangleFace();
	TriangleFace(Point,Point,Point, const Material&);
	struct Data intersect(Point, Vetor, int, float);
	Vetor calcColor(Point O, Vetor V, Vetor Ienv, float t_int, Light* light, bool kill);
	void changeToCam(Camera cam);
	bool simpleIntersect(Point, Vetor);
	void print();
	Point getCenter();	
};

#endif

