#include "Material.h"

Material::Material() {};

Material::Material(Vetor envMaterial, Vetor difMaterial, Vetor speMaterial)
	: env_material(envMaterial), dif_material(difMaterial), spe_material(speMaterial) {}