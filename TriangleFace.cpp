#include "TriangleFace.h"

TriangleFace::TriangleFace()
{
}

TriangleFace::TriangleFace(Point x, Point y, Point z, const Material& material) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->material = material;
}

struct Data TriangleFace::intersect(Point, Vetor, int, float) {
	Data data;
	data.empty = 0;
	return data;
}

Vetor TriangleFace::calcColor(Point O, Vetor V, Vetor Ienv, float t_int, Light* light, bool kill) {
	Vetor vetor;
	return vetor;
}

void TriangleFace::changeToCam(Camera cam){}

bool TriangleFace::simpleIntersect(Point, Vetor) {
	return false;
}

void TriangleFace::print() {

}

Point TriangleFace::getCenter() {
	Point point;
	return point;
}
