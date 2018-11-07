#ifndef  SPHERE_H
#define SPHERE_H
#include <algorithm> 

#include "Objeto.h"
#include "Material.h"
#include "Point.h"



class Sphere : public Objeto {
public:
	Point center;
	float radius;
	Material material;
	Sphere();
	Sphere(Point, float, const Material&);
	struct Data intersect(Point, Vetor , int , float);
	int shadowIntersection(Objeto* obj,Light* light);
	Vetor calcColor(Point O, Vetor V, Vetor Ienv, float t_int,Light* light);
	void changeToCam(Camera cam);
	void print();
};

#endif