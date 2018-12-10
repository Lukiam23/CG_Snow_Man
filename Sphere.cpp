#include "Sphere.h"
#include <iostream>
#include <limits>

using namespace std;

Sphere::Sphere() {};

Sphere::Sphere(Point pcenter, float sradius, const Material& smaterial)
	: center(pcenter), material(smaterial.env_material, smaterial.dif_material, smaterial.spe_material) {
	radius = sradius;
};

struct Data Sphere::intersect(Point O, Vetor V, int k, float t_int) {
	float alpha = V.dot(V);
	
	Vetor CO(O.getX() - center.getX(), O.getY() - center.getY(),O.getZ() - center.getZ());
	float beta = 2 * V.dot(CO);

	float gamma = CO.dot(CO) - pow(radius, 2);

	// Calculating the delta from 'alpha', 'beta' and 'gamma';
	float delta = (beta * beta) - (4 * alpha * gamma);
	int indexSphere = -1;
	float deltaRay = -1;
	Data data;
	data.empty = 1;
	if (delta >= 0) {
		
		float t = std::min((-beta + sqrt(delta)) / (2 * alpha), (-beta - sqrt(delta)) / (2 * alpha));
		
		if (t < t_int) {
			t_int = t;
			indexSphere = k;
			deltaRay = delta;
			data.empty = 0;
			data.t_int = t_int;
			data.indexSphere = indexSphere;
			data.deltaRay = deltaRay;
		}
	}
	return data;
}

bool Sphere::simpleIntersect(Point O, Vetor V) {
	
	float alpha = V.dot(V);
	Vetor CO(O.getX() - center.getX(), O.getY() - center.getY(), O.getZ() - center.getZ());
	
	float beta = 2 * V.dot(CO);

	float gamma = CO.dot(CO) - pow(radius, 2);

	// Calculating the delta from 'alpha', 'beta' and 'gamma';
	float delta = (beta * beta) - (4 * alpha * gamma);
	if (delta < 0) {
		return false;
	}
	float t = std::min((-beta + sqrt(delta)) / (2 * alpha), (-beta - sqrt(delta)) / (2 * alpha));
	if (t >= 0) {
		return true;
	}
	return false;
}

Vetor Sphere::calcColor(Point O, Vetor V, Vetor Ienv, float t_int,Light* light,bool kill) {
	V *= t_int;
	Point P(O);
	P += V; //Ponto de interseção do raycast

	//vetor do centro da esfera para o ponto P
	Vetor N(P.getX() - center.getX(), P.getY() - center.getY(), P.getZ() - center.getZ());

	//Vetor normalizado
	Vetor n = N.normalize();
	
	//Vetor de P até a Luz
	Vetor L((*light).center.getX() - P.getX(), (*light).center.getY() - P.getY(), (*light).center.getZ() - P.getZ());
	//Vetor normalizado
	Vetor l = L.normalize();

	
	Vetor Kenv(material.env_material);//Componente ambiente
	Vetor Kdif(material.dif_material);//Componente difusa
	Vetor Kspe(material.spe_material);//Componente especular

	//Passa a cor da luz para o vetor If
	Vetor If((*light).color);
	
	Vetor Idif(If);
	Idif.at(Kdif);
	float Fdif = l.dot(n);
	Idif *= Fdif;
	

	// Calculating the specular rate
	Vetor Ispe(If);
	Ispe.at(Kspe);
	Vetor r(n);
	r *= (2 * l.dot(n));
	r -= (l);
	Vetor PO(-P.getX(), -P.getY(), -P.getZ());
	Vetor v = PO.normalize();
	float Fspe = pow(r.dot(v), 1);
	Ispe *= (Fspe);
	

	// Generating the final color for current pixel
	Vetor Color(Ienv);
	Color.at(Kenv);

	Color += (Idif);
	Color += (Ispe);
	if (kill) {
		Vetor shadowrate(0.3, 0.3, 0.3);
		Color.at(shadowrate);
	}
	return Color;
}

void Sphere::changeToCam(Camera cam) {
	cam.worldToCamera(&center);
}

void Sphere::print() {
	center.print();
	std::cout << "Raio: " << this->radius << std::endl;
}


Point Sphere::getCenter() {
	return this->center;
}


