#include "Point.h"
#include <iostream>

using namespace std;

Point::Point() {};

Point::Point(float x, float y, float z, float h) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->h = h;
}
double Point::getX() {
	return this->x;
}

double Point::getY() {
	return this->y;
}

double Point::getZ() {
	return this->z;
}

double Point::getH() {
	return this->h;
}

Point::Point(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Point::Point(const Point& p){
	this->x = p.x;
	this->y = p.y;
	this->z = p.z;
}

Point Point::operator +(Vetor& v) {
	Point newPoint(this->x + v.getX(), this->y + v.getY() , this->z + v.getZ());
	return newPoint;
}
void Point::operator +=(Vetor& v) {
	this->x += v.getX();
	this->y += v.getY();
	this->z += v.getZ();
}

void Point::setX(float x) {
	this->x = x;
}

void Point::setY(float y) {
	this->y = y;
}

void Point::setZ(float z) {
	this->z = z;
}

void Point::setH(float h) {
	this->h = h;
}
void Point::print() {
	cout << this->x << " " << this->y << " " << this->z << endl;
}

void Point::printH() {
	cout << this->x << " " << this->y << " " << this->z << " " << this->h << endl;
}

void Point :: operator *=(double a) {
	x *= a;
	y *= a;
	z *= a;
}
