#ifndef Scenario_H
#define Scenario_H


#include "Objeto.h"
#include "Point.h"
#include "Vetor.h"
#include "Light.h"
#include "Camera.h"

class Scenario {
private:
	Objeto* objetos[2000];
	Light* lights[10];
	Camera* cams[10];

	int qtObjetos;
	int qtLights;
	int qtCam;

	Point O;
	Vetor Ienv;
public:
	Scenario();
	Scenario(Point O,Vetor Ienv);
	void addObjeto(Objeto *objeto);
	void addLuz(Light *luz);
	void addCam(Camera* cam);
	Objeto* getObjeto(int);
	Light* getLight(int);
	Camera* getCam(int);
	void changeObj(int);
	int getQtObj();
	void changePoint(int index, Point* p);
	int getQtLig();
	Point* getOrigin();
	Objeto** getAllObjects();
};
#endif // Scenario_H