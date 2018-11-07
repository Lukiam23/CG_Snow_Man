#include "Vetor.h"
#include <cmath>
#include <iostream>

using namespace std;

Vetor::Vetor() {};

Vetor::Vetor(double x, double y, double z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vetor::Vetor(const Vetor& v){
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
}

Vetor Vetor::operator +(Vetor& v) {
	Vetor newVetor(v.getX() + this->x, v.getY() + this->y, v.getZ() + this->z);
	return newVetor;
}

void Vetor::operator +=(Vetor& v) {
	this->x += v.getX();
	this->y += v.getY();
	this->z += v.getZ();
}

Vetor Vetor::operator -(Vetor& v) {
	Vetor newVetor(v.getX() - this->x, v.getY() - this->y, v.getZ() - this->z);
	return newVetor;
}

void Vetor::operator -=(Vetor& v) {
	this->x -= v.getX();
	this->y -= v.getY();
	this->z -= v.getZ();
}

Vetor Vetor::operator *(double s) {
	Vetor newVetor(x * s, y * s, z * s);
	return newVetor;
}

void Vetor::operator *=(double s) {
	this->x *= s;
	this->y *= s;
	this->z *= s;
}

double Vetor::norm(){
	return sqrt(x * x + y * y + z * z);
}

Vetor Vetor::normalize() {
	
	Vetor vetorNomalized(x, y, z);
	double n = this->norm();
	if (n > 0) {
		double r = 1 / n;
		vetorNomalized *= (r);
		return vetorNomalized;
	}
	return vetorNomalized;
}

double Vetor::getX() {
	return this->x;
}

double Vetor::getY() {
	return this->y;
}

double Vetor::getZ() {
	return this->z;
}

void Vetor::setX(double x) {
	this->x = x;
}

void Vetor::setY(double y) {
	this->y = y;
}

void Vetor::setZ(double z) {
	this->z = z;
}

double Vetor::dot(Vetor& v) {
	return((this->x * v.getX() + this->y * v.getY() + this->z * v.getZ()));
}

Vetor Vetor::cross(Vetor& v) {
	Vetor product(this->y * v.getZ() - this->z * v.getY(), this->z * v.getX() - this->x * v.getZ(), this->x * v.getY() - this->y * v.getX());
	return product;
}

void Vetor::at(Vetor v) {
	this->x *= v.getX();
	this->y *= v.getY();
	this->z *= v.getZ();
}
void Vetor::print() {
	cout << this->x << " " << this->y << " " << this->z<<endl;
}