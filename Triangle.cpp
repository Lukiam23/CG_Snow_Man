#include "Triangle.h"]
#include <iostream>
Triangle::Triangle() {};

Triangle::Triangle(Point pOne, Point pTwo, Point pThree, const Material& smaterial)
	: p1(pOne), p2(pTwo), p3(pThree), material(smaterial.env_material, smaterial.dif_material, smaterial.spe_material) {

};

struct Data Triangle::intersect(Point O, Vetor V, int k, float t) {
	Vetor p1p3(p1.getX() - p3.getX(), p1.getY() - p3.getY(), p1.getZ() - p3.getZ());
	Vetor p1p2(p1.getX() - p2.getX(), p1.getY() - p2.getY(), p1.getZ() - p2.getZ());
	Vetor normalFace = p1p2.cross(p1p3); //vetor nomal a face
	Vetor normalizedFace = normalFace.normalize(); // vetor normal normalizado
	
	Vetor W_barrado(p1.getX(), p1.getY(), p1.getZ());
	float t_int = W_barrado.dot(normalizedFace) / V.dot(normalizedFace);

	Point P_int(V.getX() * t_int, V.getY() * t_int, V.getZ() * t_int);

	Vetor W1(p1.getX() - P_int.getX(), p1.getY() - P_int.getY(), p1.getZ() - P_int.getZ());
	Vetor W2(p2.getX() - P_int.getX(), p2.getY() - P_int.getY(), p2.getZ() - P_int.getZ());
	Vetor W3(p3.getX() - P_int.getX(), p3.getY() - P_int.getY(), p3.getZ() - P_int.getZ());

	float a = (W1.cross(W2)).dot(normalizedFace);
	float b = (W2.cross(W3)).dot(normalizedFace);
	float c = (W3.cross(W1)).dot(normalizedFace);

	Data data;
	data.empty = 1;

	if ((a>=0 && b>=0 && c>=0 || a < 0 && b < 0 && c < 0) && t_int<t){
		data.empty = 0;
		data.t_int = t_int;
		data.indexSphere = k;
		data.deltaRay = 1;
	}
	return data;
}

Vetor Triangle::calcColor(Point O, Vetor V, Vetor Ienv, float t_int, Light* light, bool kill) {
	V *= t_int;
	Point P(O);
	P += V;

	Vetor p1p3(p3.getX() - p1.getX(), p3.getY() - p1.getY(), p3.getZ() - p1.getZ());
	Vetor p1p2(p2.getX() - p1.getX(), p2.getY() - p1.getY(), p2.getZ() - p1.getZ());
	Vetor normalFace = p1p3.cross(p1p2);
	Vetor n = normalFace.normalize();

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

void Triangle::changeToCam(Camera cam) {
	cam.worldToCamera(&p1);
	cam.worldToCamera(&p2);
	cam.worldToCamera(&p3);
}

bool Triangle::simpleIntersect(Point O, Vetor V) {
	Vetor p1p3(p1.getX() - p3.getX(), p1.getY() - p3.getY(), p1.getZ() - p3.getZ());
	Vetor p1p2(p1.getX() - p2.getX(), p1.getY() - p2.getY(), p1.getZ() - p2.getZ());
	Vetor normalFace = p1p2.cross(p1p3); //vetor nomal a face
	Vetor normalizedFace = normalFace.normalize(); // vetor normal normalizado

	//float D = normalizedFace.getX()*p1.getX() + normalizedFace.getY()*p1.getY() + normalizedFace.getZ()*p1.getZ();

	Vetor W(p1.getX() - O.getX(), p1.getY() - O.getY(), p1.getZ() - O.getZ());
	float t_int = W.dot(normalizedFace) / V.dot(normalizedFace);

	Point P_int(V.getX() * t_int + O.getX(), V.getY() * t_int +O.getY(), V.getZ() * t_int + O.getZ());

	Vetor W1(p1.getX() - P_int.getX(), p1.getY() - P_int.getY(), p1.getZ() - P_int.getZ());
	Vetor W2(p2.getX() - P_int.getX(), p2.getY() - P_int.getY(), p2.getZ() - P_int.getZ());
	Vetor W3(p3.getX() - P_int.getX(), p3.getY() - P_int.getY(), p3.getZ() - P_int.getZ());

	float a = (W1.cross(W2)).dot(normalizedFace);
	float b = (W2.cross(W3)).dot(normalizedFace);
	float c = (W3.cross(W1)).dot(normalizedFace);
	bool result = false;
	if ((a >= 0 && b >= 0 && c >= 0 || a < 0 && b < 0 && c < 0) && t_int>=0) {
		result = true;
		return result;
	}
	return result;
}

void Triangle::print() {
	std::cout<< "P1:";
	p1.print();
	std::cout << "P2:";
	p2.print();
	std::cout << "P3:";
	p3.print();
}

Point Triangle::getCenter() {
	Point point;
	return point;
}
