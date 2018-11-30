#include "Scenario.h"

Scenario::Scenario() {
	qtObjetos = 0;
	qtLights = 0;
	qtCam = 0;
};

Objeto** Scenario::getAllObjects() {
	return objetos;
}

int Scenario::getQtObj() {
	return this->qtObjetos;
}

int Scenario::getQtLig() {
	return this->qtLights;
}

Objeto* Scenario::getObjeto(int index) {
	if (index < this->qtObjetos) {
		return this->objetos[index];
	}
}

Light* Scenario::getLight(int index) {
	if (index < this->qtLights) {
		return this->lights[index];
	}
}

Camera* Scenario::getCam(int index) {
	if (index < this->qtCam) {
		return this->cams[index];
	}
}

Scenario::Scenario(Point O, Vetor Ienv) {
	this->O = O;
	this->Ienv = Ienv;
	qtObjetos = 0;
	qtLights = 0;
	qtCam = 0;
}

void Scenario::addObjeto(Objeto *objeto) {
	objetos[this->qtObjetos] = objeto;
	qtObjetos++;
}

void Scenario::addLuz(Light *luz) {
	lights[qtLights] = luz;
	qtLights++;
}

void Scenario::addCam(Camera* cam) {
	cams[qtCam] = cam;
	qtCam++;
}

void Scenario::changeObj(int index) {
	if (index < qtCam) {
		for (int i = 0; i < this->qtObjetos; i++) {
			objetos[i]->changeToCam(*cams[index]);
		}
	}
}

void Scenario::changePoint(int index, Point* p) {	
	if (index < qtCam) {
		this->cams[index]->worldToCamera(p);
	}
}

Point* Scenario::getOrigin() {
	return &O;
}