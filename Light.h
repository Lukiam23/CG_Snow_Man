#ifndef Light_H
#define Light_H
#include "Point.h"
#include "Vetor.h"

class Light {
public:
	Point center;
	Vetor color;
	Light();
	Light(Point, Vetor);

};

#endif