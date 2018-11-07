#ifndef Point_H
#define Point_H
#include "Vetor.h"

class Point
{
private:
	float x, y, z, h;
public:
	Point();
	Point(const Point&);
	Point(float, float, float);
	Point(float, float, float,float);
	Point operator +(Vetor&);
	void operator +=(Vetor&);
	void operator *=(double);
	double getX();
	double getY();
	double getZ();
	double getH();
	void setX(float);
	void setY(float);
	void setZ(float);
	void setH(float);
	void print();
	void printH();

};

#endif