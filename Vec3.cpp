#include "Vec3.h"


Vec3::Vec3()
{

}


Vec3::Vec3(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

float Vec3::getX() {
	return x;
}

float Vec3::getY() {
	return y;
}

float Vec3::getZ() {
	return z;
}

void Vec3::setX(double x) {
	this->x = x;
}

void Vec3::setY(double y) {
	this->y = y;
}

void Vec3::setZ(double z) {
	this->z = z;
}
