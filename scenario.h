#include <cmath>
#include <iostream>

using namespace std;

class Vector;

float min(float x, float y) {
	if (x > y) {
		return y;
	}
	else {
		return x;
	}
};

class Point {
public:
	float x;
	float y;
	float z;
	Point(const Point&);
	Point(float, float, float);
	void plus(const Vector&);
	void changeCamera(float[4][4]);
};

void Point::changeCamera(float Mw_c[4][4]) {
	float v[4] = { x,y,z,1 };
	float newPosition[4] = { 0,0,0,0 };
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			newPosition[i] += v[j] * Mw_c[i][j];
		}
	}
	x = newPosition[0];
	y = newPosition[1];
	z = newPosition[2];
};

Point::Point(const Point& p) {
	x = p.x;
	y = p.y;
	z = p.z;
};

Point::Point(float cx, float cy, float cz) {
	x = cx;
	y = cy;
	z = cz;
};

class Vector {
public:
	float x;
	float y;
	float z;
	Vector(const Vector&);
	Vector(Point);
	Vector(Point, Point);
	Vector(float, float, float);
	float dot(Vector);
	void at(Vector);
	void plus(Vector);
	void less(Vector);
	void times(float);
	float norm();
	Vector normalize();
	Vector vectorialProduct(Vector);
};

//Vectorial product for matrix of length 3
Vector Vector::vectorialProduct(Vector v2) {
	Vector product(y * v2.z - z * v2.y, z * v2.x - x * v2.z, x * v2.y - y * v2.x);
	return product;
};

float Vector::norm() {
	return sqrt(x * x + y * y + z * z);
};

Vector Vector::normalize() {
	float norm = this->norm();
	if (norm != 0) {
		Vector normalized(x * 1 / norm, y * 1 / norm, z * 1 / norm);
		return normalized;
	}
	return Vector(x, y, z);

};

float Vector::dot(Vector v) {
	return x * v.x + y * v.y + z * v.z;
};

void Vector::at(Vector v) {
	x *= v.x;
	y *= v.y;
	z *= v.z;
};

void Vector::plus(Vector v) {
	x += v.x;
	y += v.y;
	z += v.z;
};

void Vector::less(Vector v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
};

void Vector::times(float t) {
	x *= t;
	y *= t;
	z *= t;
};

Vector::Vector(float cx, float cy, float cz) {
	x = cx;
	y = cy;
	z = cz;
};

Vector::Vector(Point p1, Point p2) {
	x = p2.x - p1.x;
	y = p2.y - p1.y;
	z = p2.z - p1.z;
};

Vector::Vector(Point p) {
	x = p.x;
	y = p.y;
	z = p.z;
};

Vector::Vector(const Vector& v) {
	x = v.x;
	y = v.y;
	z = v.z;
};

void Point::plus(const Vector& v) {
	x += v.x;
	y += v.y;
	z += v.z;
};


class Material {
public:
	Vector env_material;
	Vector dif_material;
	Vector spe_material;
	Material(Vector, Vector, Vector);
};

Material::Material(Vector envMaterial, Vector difMaterial, Vector speMaterial)
	: env_material(envMaterial), dif_material(difMaterial), spe_material(speMaterial) {}


class Sphere {
public:
	Point center;
	float radius;
	Material material;
	Sphere(Point, float, const Material&);
};

Sphere::Sphere(Point pcenter, float sradius, const Material& smaterial)
	: center(pcenter), material(smaterial.env_material, smaterial.dif_material, smaterial.spe_material) {
	radius = sradius;
};

class Light {
public:
	Point center;
	Vector color;
	Light(Point, Vector);
};

Light::Light(Point lcenter, Vector lcolor) : center(lcenter), color(lcolor) {}

class Camera {
public:
	Point lookat;
	Point viewUp;
	Point Origem;
	Camera(Point, Point, Point);
	void setCamera();
	void setMatrix();
};

Camera::Camera(Point l, Point v, Point o) : lookat(l), viewUp(v), Origem(o) {}

void Camera::setCamera() {

};