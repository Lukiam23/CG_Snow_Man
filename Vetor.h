#ifndef Vetor_H
#define Vetor_H


#include <cmath>

class Vetor {
private:
	double x, y, z;
public:
	Vetor();
	Vetor(double , double , double );
	Vetor(const Vetor& v);
	Vetor cross(Vetor& v);
	double dot(Vetor& v);
	Vetor operator +(Vetor& v);
	void operator +=(Vetor& v);
	Vetor operator -(Vetor& v);
	void operator -=(Vetor& v);
	Vetor operator *(double s);
	void at(Vetor s);
	void operator *=(double s);
	double norm();
	Vetor normalize();
	double getX();
	double getY();
	double getZ();
	void setX(double x);
	void setY(double Y);
	void setZ(double Z);
	void print();
};


#endif // Vetor_H