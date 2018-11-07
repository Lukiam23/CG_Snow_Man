#ifndef Material_H
#define Material_H
#include "Vetor.h"
class Material {
public:
	Vetor env_material;
	Vetor dif_material;
	Vetor spe_material;
	Material();
	Material(Vetor, Vetor, Vetor);
};
#endif
