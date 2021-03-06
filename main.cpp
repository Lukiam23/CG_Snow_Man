# include <GL/glew.h>
# include <GL/freeglut.h>

#include <cmath>
#include <iostream>
#include <limits>
#include <vector>
#include <stdio.h>
#include <stdlib.h>


#include "Point.h"
#include "Scenario.h"
#include "Vetor.h"
#include "Objeto.h"
#include "Sphere.h"
#include "Light.h"
#include "Material.h"
#include "Camera.h"
#include "Triangle.h"
#include "Vec2.h"
#include "Vec3.h"

using namespace std;


int W_Npixels = 500;
int H_Npixels = 500;

double H = 500;
double W = 500;

Scenario scenario;
Point O(20, 20, 50);
Vetor Ienv(1, 1, 1);

std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
std::vector< Point > temp_vertices;
std::vector< Vec2 > temp_uvs;
std::vector< Vec3 > temp_normals;

bool parser(const char* path) {
	FILE * file;
	errno_t err = fopen_s(&file, path, "r");
	if (err) {
		printf("Impossible to open the file !\n");
		return false;
	}
	while (1) {
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf_s(file, "%s", lineHeader,sizeof(lineHeader));
		if (res == EOF)
			break;
		if (strcmp(lineHeader, "v") == 0) {
			double x,y,z;
			fscanf_s(file, "%lf %lf %lf\n", &x,&y,&z);
			temp_vertices.push_back(Point(x,y,z));
		}else if (strcmp(lineHeader, "vt") == 0) {
			double x,y;
			fscanf_s(file, "%lf %lf\n", &x, &y);
			temp_uvs.push_back(Vec2(x,y));
		}else if (strcmp(lineHeader, "vn") == 0) {
			double x,y,z;
			fscanf_s(file, "%lf %lf %lf\n", &x, &y, &z);
			temp_normals.push_back(Vec3(x,y,z));
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf_s(file, "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2]);
			
			if (matches != 6) {
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return false;
			}

			Vetor floor_env_material(1, 0, 1);       // Material's enviroment component factors
			Vetor floor_dif_material(0.6, 0.6, 0.6);       // Material's difuse component factors
			Vetor floor_spe_material(0.8, 0.8, 0.8); // Material's specular component factors
			Material floor_material(floor_env_material, floor_dif_material, floor_spe_material);

			Point p1 = temp_vertices[vertexIndex[0] - 1];
			Point p2 = temp_vertices[vertexIndex[1] - 1];
			Point p3 = temp_vertices[vertexIndex[2] - 1];

			Objeto* p = new Triangle(p1, p2, p3, floor_material);
			scenario.addObjeto(p);

		}
	}
}

void setScenario() {
	scenario = Scenario(O, Ienv);
	/*---------------------------Load the objects to scenario-----------------------*/
	parser("C:\\Users\\mscor\\Documents\\2018.2\\cubeplane.obj");
	cout << "Load fished" << endl;

	/*---------------------------Light Snowman-----------------------*/
	Point light_center(0, 20, 0);
	Vetor light_color(0.8, 0.8, 0.8);
	Light* light = new Light(light_center, light_color);
	scenario.addLuz(light);

	/*---------------------------Material Snowman-----------------------*/
	Vetor floor_env_material(0, 1, 0.5);       // Material's enviroment component factors
	Vetor floor_dif_material(0.5, 0.5, 0.5);       // Material's difuse component factors
	Vetor floor_spe_material(0.5, 0.5, 0.5); // Material's specular component factors
	Material floor_material(floor_env_material, floor_dif_material, floor_spe_material);

	Vetor	triangle_env_material(1, 1, 1);       // Material's enviroment component factors
	Vetor triangle_dif_material(0.5, 0.5, 0.5);       // Material's difuse component factors
	Vetor triangle_spe_material(0.5, 0.5, 0.5); // Material's specular component factors
	Material triangle_material(triangle_env_material, triangle_dif_material, triangle_spe_material);

	Vetor triangle_env_material2(0, 0, 1);       // Material's enviroment component factors
	Vetor triangle_dif_material2(0.5, 0.5, 0.5);       // Material's difuse component factors
	Vetor triangle_spe_material2(0.5, 0.5, 0.5); // Material's specular component factors
	Material triangle_material2(triangle_env_material2, triangle_dif_material2, triangle_spe_material2);


	Vetor snow_env_material(1, 1, 1);       // Material's enviroment component factors
	Vetor snow_dif_material(0.5, 0.5, 0.5);       // Material's difuse component factors
	Vetor snow_spe_material(0.5, 0.5, 0.5); // Material's specular component factors
	Material snow_material(snow_env_material, snow_dif_material, snow_spe_material);


	// Vetor snow_env_materialEye(0, 0, 0);       // Material's enviroment component factors
	// Vetor snow_dif_materialEye(0.6, 0.6, 0.6);       // Material's difuse component factors
	// Vetor snow_spe_materialEye(0.5, 0.5, 0.5); // Material's specular component factors
	// Material snow_materialEye(snow_env_materialEye, snow_dif_materialEye, snow_spe_materialEye);

	// Vetor snow_env_materialBottom1(0, 0, 0);       // Material's enviroment component factors
	// Vetor snow_dif_materialBottom1(0.6, 0.6, 0.6);       // Material's difuse component factors
	// Vetor snow_spe_materialBottom1(0.5, 0.5, 0.5); // Material's specular component factors
	// Material snow_materialBottom1(snow_env_materialBottom1, snow_dif_materialBottom1, snow_spe_materialBottom1);

	// Vetor snow_env_materialBottom2(0, 0, 0);       // Material's enviroment component factors
	// Vetor snow_dif_materialBottom2(0.6, 0.6, 0.6);       // Material's difuse component factors
	// Vetor snow_spe_materialBottom2(0.5, 0.5, 0.5); // Material's specular component factors
	// Material snow_materialBottom2(snow_env_materialBottom2, snow_dif_materialBottom2, snow_spe_materialBottom2);

	// Vetor snow_env_materialBottom3(0, 0, 0);       // Material's enviroment component factors
	// Vetor snow_dif_materialBottom3(0.6, 0.6, 0.6);       // Material's difuse component factors
	// Vetor snow_spe_materialBottom3(0.5, 0.5, 0.5); // Material's specular component factors
	// Material snow_materialBottom3(snow_env_materialBottom3, snow_dif_materialBottom3, snow_spe_materialBottom3);

	/*---------------------------Corpo Snowman-----------------------*/

	// Point body_center(0, -10, 0); // Center of body sphere
	// Objeto* body = new Sphere(body_center, 20, snow_material);
	// scenario.addObjeto(body);

	// Point eye_center1(4, 22, 9); // Center of eye sphere
	// Objeto *eye1 = new Sphere(eye_center1, 2, snow_materialEye);
	// scenario.addObjeto(eye1);

	// Point eye_center2(-4, 22, 9); // Center of eye sphere
	// Objeto* eye2 = new Sphere(eye_center2, 2, snow_materialEye);
	// scenario.addObjeto(eye2);

	// Point nose_center(0, 20, 10); // Center of eye sphere
	// Objeto* nose = new Sphere(nose_center, 2, snow_materialEye);
	// scenario.addObjeto(nose);

	// Point bottom_center1(0, -20, 17); // Center of bottom sphere
	// Objeto* bottom1 = new Sphere(bottom_center1, 2, snow_materialBottom1);
	// scenario.addObjeto(bottom1);

	// Point bottom_center2(0, -10, 20); // Center of bottom sphere
	// Objeto* bottom2 = new Sphere(bottom_center2, 2, snow_materialBottom2);
	// scenario.addObjeto(bottom2);

	// Point bottom_center3(0, 0, 17); // Center of bottom sphere
	// Objeto* bottom3 = new Sphere(bottom_center3, 2, snow_materialBottom3);
	// scenario.addObjeto(bottom3);

	/*Point head_center(0, 50, 0); // Center of head sphere
	Objeto* head = new Sphere(head_center, 10, snow_material);
	scenario.addObjeto(head);

	Point floor_center(0, -1990, 0); // Center of head sphere
	Objeto* floor1 = new Sphere(floor_center, 1960, floor_material);
	scenario.addObjeto(floor1);

	Point p1(-50, 0, 50);
	Point p2(50, 0, 50);
	Point p3(0, 50, 0);
	Point p4(-50, 0, -50);
	Point p5(50, 0, -50);

	Objeto* triangle1 = new Triangle(p1, p2, p3, triangle_material);
	scenario.addObjeto(triangle1);

	Objeto* triangle2 = new Triangle(p4, p1, p3, triangle_material);
	scenario.addObjeto(triangle2);

	Objeto* triangle3 = new Triangle(p4, p5, p3, triangle_material);
	scenario.addObjeto(triangle3);

	Objeto* triangle4 = new Triangle(p2, p5, p3, triangle_material);
	scenario.addObjeto(triangle4);*/

	//Objeto* body = new Sphere(p3, 20, snow_material);
	//scenario.addObjeto(body);


	Point lookat(0, 0, 0);
	Point viewUP(0, 100, 0);
	Camera* cam = new Camera(O, lookat, viewUP);
	scenario.addCam(cam);

	scenario.changeObj(0);
	scenario.changePoint(0, scenario.getOrigin());
	scenario.changePoint(0, &scenario.getLight(0)->center);

};

void drawScene(void) {
	int l, c;
	double x, y, Dy, Dx;

	Dx = W / W_Npixels;
	Dy = H / H_Npixels;

	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POINTS);

	double d = 1500;
	for (l = 0; l < H_Npixels; l++) {
		y = (H / 2 - Dy / 2 - l * Dy);
		for (c = 0; c < W_Npixels; c++) {
			x = (-W / 2 + Dx / 2 + c * Dx);
			float t_int = numeric_limits<float>::max();

			Vetor V(x, y, -d); // Vector from camera to Pixel

			float deltaRay = -1;
			int indexSphere = -1;
			Point O(0, 0, 0);
			for (int k = 0; k < scenario.getQtObj(); k++) {
				Data data = scenario.getObjeto(k)->intersect(O, V, k, t_int);

				if (!data.empty) {
					t_int = data.t_int;
					indexSphere = data.indexSphere;
					deltaRay = data.deltaRay;
				}
			}

			if (deltaRay >= 0) {

				Vetor VT(V * t_int);
				Point P_int(VT.getX(), VT.getY(), VT.getZ());
				Point l = scenario.getLight(0)->center;

				Vetor PL(l.getX() - P_int.getX(), l.getY() - P_int.getY(), l.getZ() - P_int.getZ());

				int indexO = 0;
				bool result = false;
				while (indexO < scenario.getQtObj() && result == false) {
					if (indexO != indexSphere) {
						result = scenario.getObjeto(indexO)->simpleIntersect(P_int, PL);
					}
					indexO++;
				}

				Vetor color = scenario.getObjeto(indexSphere)->calcColor(O, V, Ienv, t_int, scenario.getLight(0), result);
				glColor3f(color.getX(), color.getY(), color.getZ());
			}
			else {
				glColor3f(0.3921, 0.5843, 0.9294);
			}
			glVertex2f(c, l);
		}
	}
	glEnd();
	glFlush();
}

void resize(int w, int h) {
	int hSize = w * H / W;
	int wSize = h * W / H;

	if (h >= w)
		glViewport(0, (h - hSize) / 2, w, hSize);

	else if (h < w)
		glViewport((w - wSize) / 2, 0, wSize, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, W_Npixels, H_Npixels, 0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char ** argv) {
	setScenario();
	glutInit(&argc, argv);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(W_Npixels, H_Npixels);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Snowman");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);

	glewExperimental = GL_TRUE;
	glewInit();

	glClearColor(1.0, 1.0, 1.0, 0.0);
	
	glutMainLoop();
}