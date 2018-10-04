#include <cmath>
#include <iostream>
#include <limits>
#include "scenario.h"

#ifdef __APPLE__
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <OpenGL/glext.h>
#else
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glext.h>
#pragma comment(lib, "glew32.lib")
#endif

#define PI 3.14159265

using namespace std;

static unsigned int   windowW = 500, windowH = 500;
static float          W = 50., H = 50.;




// Initialization routine.
void setup(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
};

float x, y;

float Dx = W / windowW;
float Dy = H / windowH;

Point O(250, 250, -500); // Origin's point of camera

Point light_center(250, 300, -400);
Vector light_color(0.5, 0.5, 0.5);
Light light(light_center, light_color);

// Setting snow material
Vector snow_env_material(1, 1, 1);       // Material's enviroment component factors
Vector snow_dif_material(0.0, 0.0, 0.0);       // Material's difuse component factors
Vector snow_spe_material(1, 1, 1); // Material's specular component factors
Material snow_material(snow_env_material, snow_dif_material, snow_spe_material);

Vector snow_env_material2(1, 1, 1);       // Material's enviroment component factors
Vector snow_dif_material2(0.6, 0.6, 0.6);       // Material's difuse component factors
Vector snow_spe_material2(1, 1, 1); // Material's specular component factors
Material snow_material2(snow_env_material2, snow_dif_material2, snow_spe_material2);

Vector snow_env_materialEye(0, 0, 0);       // Material's enviroment component factors
Vector snow_dif_materialEye(0.6, 0.6, 0.6);       // Material's difuse component factors
Vector snow_spe_materialEye(1, 1, 1); // Material's specular component factors
Material snow_materialEye(snow_env_materialEye, snow_dif_materialEye, snow_spe_materialEye);


// Snowman definition
//Point eye_center();
Point eye_center1(250, 250, -430); // Center of body sphere
Sphere eye1(eye_center1, 100, snow_materialEye);

Point eye_center2(250, 250, -470); // Center of body sphere
Sphere eye2(eye_center2, 100, snow_materialEye);

Point body_center(250, 250, -400); // Center of body sphere
Sphere body(body_center, 100, snow_material2);

Point head_center(250, 270, -400); // Center of head sphere
Sphere head(head_center, 40, snow_material);


int n = 4; // Number of objects (spheres) in scenario
Sphere objects[] = { body, head, eye1, eye2}; // List of these objects

// Drawing routine.
void drawScene(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0, 0.0, 0.0);

    glEnable(GL_PROGRAM_POINT_SIZE_EXT);
    glPointSize(1);
    glBegin(GL_POINTS);
        for (float i = 0; i < windowH; i += 1) {
			x = H / 2 - Dy / 2 - i * Dy;
            for (float j = 0; j < windowW; j += 1) {
				y = -W / 2 + Dx / 2 + j * Dx;
                float d = -10; // Position of window
                Point Pix(i, j, d); // Pixel point in window
				float t = numeric_limits<float>::max();
				
                for (int k = 0; k < n; k++) {

                    Vector V(O, Pix); // Vector from camera to Pixel

                    // Checking if the ball is intercepted by ray
                    // This check uses the square equation delta
                    float alpha = V.dot(V);

					Vector OC(O.x - objects[k].center.x, O.y - objects[k].center.y, O.z - objects[k].center.z);
                    float beta = 2 * V.dot(OC);

                    Vector OO(O);
                    Vector CC(objects[k].center);
                    float gamma = OO.dot(OO) - 2 * OO.dot(CC) + CC.dot(CC) - 2 * objects[k].radius;

                    // Calculating the delta from 'alpha', 'beta' and 'gamma';
                    float delta = beta * beta - 4 * alpha * gamma;

                    // Setting the enviroment light;
                    Vector Ienv(0.3921, 0.5843, 0.9294);
                    // Vector Ienv(0, 1, 0);
                    if (delta >= 0) {
                        // Scalar that stretch the 'V' vector from camera to intercepted point
                        float t_int = min((-beta + sqrt(delta))/(2*alpha), (-beta - sqrt(delta))/(2*alpha));
						if (t_int < t){
							V.times(t_int); // V now is a Vector from the camera to the point in the object

							// Find the intercepted point
							Point P(O);
							P.plus(V);//Point whose the vector V intercept

							Vector N(objects[k].center, P);
							Vector n = N.normalize(); // Normal vector to point in sphere surface

							Vector L(P, light.center);
							Vector l = L.normalize(); // Nomalized vector from point to light

							Vector Kenv(objects[k].material.env_material); // Components factors to enviroment light
							Vector Kdif(objects[k].material.dif_material); // Components factors to difuse light
							Vector Kspe(objects[k].material.spe_material);  // Components factors to specular light

							Vector If(light.color); // Light rate

							// Calculating the difusing rate
							Vector Idif(If);
							Idif.at(Kdif);
							float Fdif = l.dot(n);
							Idif.times(Fdif);

							// Calculating the specular rate
							Vector Ispe(If);
							Ispe.at(Kspe);
							Vector r(n);
							r.times(2 * l.dot(n));
							r.less(l);
							Vector PO(P, O);
							Vector v = PO.normalize();
							float Fspe = pow(r.dot(v),3);
							Ispe.times(Fspe);

							// Generating the final color for current pixel
							Vector Color(Ienv);
							Color.at(Kenv);
							Color.plus(Idif);
							Color.plus(Ispe);

							glColor3f(Color.x, Color.y, Color.z);
							break;
						}
                    }
					else {
						glColor3f(Ienv.x, Ienv.y, Ienv.z);
					}
                }

                glVertex3f(x,y,-1);
            }
        }
    glEnd();

    glFlush();
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	int wsize = w, hsize = h;
	if (h >= w)
	{
		hsize = w * H / W;
		glViewport(0, (h - hsize) / 2, wsize, hsize);
	}
	else if (h < w)
	{
		wsize = h * W / H;
		glViewport((w - wsize) / 2, 0, wsize, hsize);
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-W / 2, W / 2, -H / 2, H / 2, 1.0, 10.0);
	// glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);
	// gluPerspective(90.0, 1.0, 5.0, 100.0);
	// gluPerspective(90.0, (float)w/(float)h, 5.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
            exit(0);
            break;
        default:
            break;
    }
}

// Main routine.
int main(int argc, char **argv){
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(windowW, windowH);
    glutInitWindowPosition(000, 000);
    glutCreateWindow("Ray Casting");
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);

    glewExperimental = GL_TRUE;
    glewInit();

    setup();

    glutMainLoop();
}
