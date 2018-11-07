#include "Camera.h"
#include "Vetor.h"
#include <iostream>

Camera::Camera() {
}

Camera::Camera(Point O, Point lookat, Point viewUp)
{
	Vetor lookatO(O.getX() - lookat.getX(), O.getY() - lookat.getY(), O.getZ() - lookat.getZ()); //Vecto lookat->O is created
	Vetor kc = lookatO.normalize();//Vector lookat->O normalized (0,-1,0)
	Vetor Vup(viewUp.getX() - O.getX(), viewUp.getY() - O.getY(), viewUp.getZ() - O.getZ()); //(0,30,0)
	

	Vetor I = Vup.cross(kc); 
	Vetor ic = I.normalize();
	Vetor jc = kc.cross(ic);
	Vetor P0(O.getX(),O.getY(),O.getZ());

	this->Mw_c[0][0] = ic.getX();
	this->Mw_c[0][1] = ic.getY();
	this->Mw_c[0][2] = ic.getZ();
	this->Mw_c[0][3] = -(ic.dot(P0));
	
	this->Mw_c[1][0] = jc.getX(); 
	this->Mw_c[1][1] = jc.getY();
	this->Mw_c[1][2] = jc.getZ();
	this->Mw_c[1][3] = -(jc.dot(P0));


	this->Mw_c[2][0] = kc.getX();
	this->Mw_c[2][1] = kc.getY();
	this->Mw_c[2][2] = kc.getZ();
	this->Mw_c[2][3] = -(kc.dot(P0));

	this->Mw_c[3][0] = 0;
	this->Mw_c[3][1] = 0;
	this->Mw_c[3][2] = 0;
	this->Mw_c[3][3] = 1;


};

void Camera::worldToCamera(Point* point) {
	Point P(point->getX(), point->getY(), point->getZ(),1);

	float x = Mw_c[0][0] * P.getX() + Mw_c[0][1] * P.getY() + Mw_c[0][2] * P.getZ() + Mw_c[0][3] * P.getH();
	float y = Mw_c[1][0] * P.getX() + Mw_c[1][1] * P.getY() + Mw_c[1][2] * P.getZ() + Mw_c[1][3] * P.getH();
	float z = Mw_c[2][0] * P.getX() + Mw_c[2][1] * P.getY() + Mw_c[2][2] * P.getZ() + Mw_c[2][3] * P.getH();
	float h = Mw_c[3][0] * P.getX() + Mw_c[3][1] * P.getY() + Mw_c[3][2] * P.getZ() + Mw_c[3][3] * P.getH();
	
	point->setX(x);
	point->setY(y);
	point->setZ(z);
	point->setH(h);
}

void Camera::printM() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			std::cout << Mw_c[i][j]<<" ";
		}
		std::cout<<"\n";
	}
}

