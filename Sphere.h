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
	Vetor calcColor(Point O, Vetor V, Vetor Ienv, float t_int,Light* light,bool kill);
	void changeToCam(Camera cam);
	bool simpleIntersect(Point, Vetor);
	void print();
	Point getCenter();
};

#endif