#include <cmath>
#include <iostream>

class Vector;

float min(float x, float y) {
    if (x > y) {
        return y;
    }else{
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
};

Point::Point (const Point& p) {
    x = p.x;
    y = p.y;
    z = p.z;
};

Point::Point (float cx, float cy, float cz) {
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
};

float Vector::norm ()  {
    return sqrt(x * x + y * y + z * z);
};

Vector Vector::normalize ()  {
    float norm = this->norm();
    Vector normalized(x * 1 / norm, y * 1 / norm, z * 1 / norm);
    return normalized;
};

float Vector::dot (Vector v) {
    return x * v.x + y * v.y + z * v.z;
};

void Vector::at (Vector v) {
    x *= v.x;
    y *= v.y;
    z *= v.z;
};

void Vector::plus (Vector v) {
    x += v.x;
    y += v.y;
    z += v.z;
};

void Vector::less (Vector v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
};

void Vector::times (float t) {
    x *= t;
    y *= t;
    z *= t;
};

Vector::Vector (float cx, float cy, float cz) {
    x = cx;
    y = cy;
    z = cz;
};

Vector::Vector (Point p1, Point p2) {
    x = p2.x - p1.x;
    y = p2.y - p1.y;
    z = p2.z - p1.z;
};

Vector::Vector (Point p) {
    x = p.x;
    y = p.y;
    z = p.z;
};

Vector::Vector (const Vector& v) {
    x = v.x;
    y = v.y;
    z = v.z;
};

void Point::plus (const Vector& v) {
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
