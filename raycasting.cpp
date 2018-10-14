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

#include <IL/il.h>

#define PI 3.14159265

using namespace std;

static unsigned int   windowW = 500, windowH = 500;
static float          W = 50., H = 50.;




// Initialization routine.
void setup(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
};

float x, y;

float Dx;
float Dy;

Point O(0, 10, 1000); // Origin's point of camera

Point light_center(0, -10000, 0);
Vector light_color(1, 1, 1);
Light light(light_center, light_color);

// Setting snow material
Vector snow_env_material(1, 1, 1);       // Material's enviroment component factors
Vector snow_dif_material(0.1, 0.1, 0.1);       // Material's difuse component factors
Vector snow_spe_material(0.4, 0.5, 0.5); // Material's specular component factors
Material snow_material(snow_env_material, snow_dif_material, snow_spe_material);


Vector snow_env_materialEye(0, 0, 0);       // Material's enviroment component factors
Vector snow_dif_materialEye(0.6, 0.6, 0.6);       // Material's difuse component factors
Vector snow_spe_materialEye(1, 1, 1); // Material's specular component factors
Material snow_materialEye(snow_env_materialEye, snow_dif_materialEye, snow_spe_materialEye);

Vector snow_env_materialBottom1(0, 0, 0);       // Material's enviroment component factors
Vector snow_dif_materialBottom1(0.6, 0.6, 0.6);       // Material's difuse component factors
Vector snow_spe_materialBottom1(1, 1, 1); // Material's specular component factors
Material snow_materialBottom1(snow_env_materialBottom1, snow_dif_materialBottom1, snow_spe_materialBottom1);

Vector snow_env_materialBottom2(0, 0, 0);       // Material's enviroment component factors
Vector snow_dif_materialBottom2(0.6, 0.6, 0.6);       // Material's difuse component factors
Vector snow_spe_materialBottom2(1, 1, 1); // Material's specular component factors
Material snow_materialBottom2(snow_env_materialBottom2, snow_dif_materialBottom2, snow_spe_materialBottom2);

Vector snow_env_materialBottom3(0, 0, 0);       // Material's enviroment component factors
Vector snow_dif_materialBottom3(0.6, 0.6, 0.6);       // Material's difuse component factors
Vector snow_spe_materialBottom3(1, 1, 1); // Material's specular component factors
Material snow_materialBottom3(snow_env_materialBottom3, snow_dif_materialBottom3, snow_spe_materialBottom3);




// Snowman definition
//Point eye_center();
Point eye_center1(5, 22, -12); // Center of eye sphere
Sphere eye1(eye_center1, 2, snow_materialEye);

Point eye_center2(-5, 22, -12); // Center of eye sphere
Sphere eye2(eye_center2, 2, snow_materialEye);

Point nose_center(0, 20, -12); // Center of eye sphere
Sphere nose(nose_center, 2, snow_materialEye);

Point bottom_center1(0, -20, -17); // Center of bottom sphere
Sphere bottom1(bottom_center1, 2, snow_materialBottom1);

Point bottom_center2(0, -10, -20); // Center of bottom sphere
Sphere bottom2(bottom_center2, 2, snow_materialBottom2);

Point bottom_center3(0, 0, -20); // Center of bottom sphere
Sphere bottom3(bottom_center3, 2, snow_materialBottom3);

Point body_center(0, -10, 0); // Center of body sphere
Sphere body(body_center, 20, snow_material);

Point head_center(0, 20, 0); // Center of head sphere
Sphere head(head_center, 10, snow_material);



int n = 8; // Number of objects (spheres) in scenario
Sphere objects[] = { body,head,eye1,eye2,bottom1,bottom2,bottom3 }; // List of these objects


Point lookat(0, 20, 0);
Point viewUp(0, 30, 0);

Vector lookatO(O.x - lookat.x, O.y - lookat.y, O.z - lookat.z); //Vecto lookat->O is created
Vector kc = lookatO.normalize();//Vector lookat->O normalized (0,-1,0)
Vector Vup(viewUp.x - O.x, viewUp.y - O.y, viewUp.z - O.z); //(0,30,0)

Vector I = Vup.vectorialProduct(kc); //(0,0,0)
Vector ic = I.normalize();
Vector jc = kc.vectorialProduct(ic);
float Mw_c[4][4] = { { ic.x,ic.y,ic.z, -(ic.dot(O)) },{ jc.x, jc.y, jc.z, -(jc.dot(O)) },{ kc.x , kc.y, kc.z, -(kc.dot(O)) },{ 0,0,0,1 } };

//Essa função passa os objetos de coordenado do mundo para coordenadas de câmera
void setObjetos() {
	for (int i = 0; i < n; i++) {
		objects[i].center.changeCamera(Mw_c);
	}
}

// Drawing routine.
void drawScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Dx = W / windowW;
	Dy = H / windowH;

	glPushAttrib(GL_CURRENT_BIT);
	glColor3f(1.0, 1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);     // Operate on model-view matrixTESTE

	glEnable(GL_PROGRAM_POINT_SIZE_EXT);
	glPointSize(1);
	glLoadIdentity();


	glTranslated(0, 0, -2.5);

	glPushMatrix();
	glRotatef(180, 0, 0, 1);
	glBegin(GL_QUADS);
	glTexCoord3f(0, 0, 0); glVertex3f((-1 * (H / 2 - Dy / 2)), -W / 2 + Dx / 2, -2);
	glTexCoord3f(0, 1, 0); glVertex3f(-1 * (H / 2 - Dy / 2), W / 2 + Dx / 2, -2);
	glTexCoord3f(1, 1, 0); glVertex3f(H / 2 - Dy / 2, W / 2 + Dx / 2, -2);
	glTexCoord3f(1, 0, 0); glVertex3f(H / 2 - Dy / 2, -W / 2 + Dx / 2, -2);
	glEnd();
	glPopMatrix();
	glPopAttrib();

	//glMatrixMode(GL_MODELVIEW);
	glPushAttrib(GL_CURRENT_BIT);
	glBegin(GL_POINTS);
	for (float i = 0; i < windowH; i++) {
		y = H / 2 - Dy / 2 - i * Dy;
		for (float j = 0; j < windowW; j++) {
			x = -W / 2 + Dx / 2 + j * Dx;
			float d = 200; // Position of window
			Point Pix(x, y, d); // Pixel point in window

			float t_int = numeric_limits<float>::max();
			float t = numeric_limits<float>::max();

			Vector V(O.x - Pix.x, O.y - Pix.y, O.z - Pix.z); // Vector from camera to Pixel
															 // Setting the enviroment light;
			Vector Ienv(0.3921, 0.5843, 0.9294);
			float deltaRay = -1;
			int indexSphere = -1;

			for (int k = 0; k < n; k++) {
				// Checking if the ball is intercepted by ray
				// This check uses the square equation delta
				float alpha = V.dot(V);

				Vector CO(O.x - objects[k].center.x, O.y - objects[k].center.y, O.z - objects[k].center.z);
				float beta = 2 * V.dot(CO);

				float gamma = CO.dot(CO) - pow(objects[k].radius, 2);

				// Calculating the delta from 'alpha', 'beta' and 'gamma';
				float delta = beta * beta - 4 * alpha * gamma;

				if (delta >= 0) {
					t = min((-beta + sqrt(delta)) / (2 * alpha), (-beta - sqrt(delta)) / (2 * alpha));
					if (t < t_int) {
						t_int = t;
						indexSphere = k;
						deltaRay = delta;
					}
				}
			}

			// Vector Ienv(0, 1, 0);
			if (deltaRay >= 0) {
				// Scalar that stretch the 'V' vector from camera to intercepted point


				V.times(t_int); // V now is a Vector from the camera to the point in the object

								// Find the intercepted point
				Point P(O);
				P.plus(V);//Point whose the vector V intercept

				Vector N(objects[indexSphere].center, P);
				Vector n = N.normalize(); // Normal vector to point in sphere surface

				Vector L(P, light.center);
				Vector l = L.normalize(); // Nomalized vector from point to light

				Vector Kenv(objects[indexSphere].material.env_material); // Components factors to enviroment light
				Vector Kdif(objects[indexSphere].material.dif_material); // Components factors to difuse light
				Vector Kspe(objects[indexSphere].material.spe_material);  // Components factors to specular light

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
				float Fspe = pow(r.dot(v), 1);
				Ispe.times(Fspe);

				// Generating the final color for current pixel
				Vector Color(Ienv);
				Color.at(Kenv);
				Color.plus(Idif);
				Color.plus(Ispe);

				glColor3f(Color.x, Color.y, Color.z);
				glVertex3f(x, y, -1);
			}
			else {
				glColor3f(Ienv.x, Ienv.y, Ienv.z);
				glVertex3f(x, y, -55);
			}

			
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

/* Initialize OpenGL Graphics */
void initGL(int w, int h)
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
	glEnable(GL_TEXTURE_2D);     // Enable 2D texturing

	glMatrixMode(GL_PROJECTION);     // Make a simple 2D projection on the entire window
	glLoadIdentity();
	//glOrtho(-w, w, h, -h, 0.0, 100.0);

	glMatrixMode(GL_MODELVIEW);    // Set the matrix mode to object modeling

	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClearDepth(0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the window
}

/* Load an image using DevIL and return the devIL handle (-1 if failure) */
int LoadImage(char *filename)
{
	ILboolean success;
	ILuint image;

	ilGenImages(1, &image); /* Generation of one image name */
	ilBindImage(image); /* Binding of image name */
	success = ilLoadImage(filename); /* Loading of the image filename by DevIL */

	if (success) /* If no error occured: */
	{
		/* Convert every colour component into unsigned byte. If your image contains alpha channel you can replace IL_RGB with IL_RGBA */
		success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

		if (!success)
		{
			return -1;
		}
	}
	else
		return -1;

	return image;
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
int main(int argc, char **argv) {
	GLuint texid;
	ILuint    image;
	char* filename = "C:\\Users\\Marcos\\Desktop\\ExemploComImagens\\praia.jpg";

	glutInit(&argc, argv);
	//setObjetos();
	setObjetos();
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

	/* OpenGL 2D generic init */
	initGL(W, H);


	/* Initialization of DevIL */
	if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION)
	{
		printf("wrong DevIL version \n");
		return -1;
	}
	ilInit();


	/* load the file picture with DevIL */
	image = LoadImage(filename);
	if (image == -1)
	{
		printf("Can't load picture file %s by DevIL \n", argv[1]);
		return -1;
	}

	/* OpenGL texture binding of the image loaded by DevIL  */
	glGenTextures(1, &texid); /* Texture name generation */
	glBindTexture(GL_TEXTURE_2D, texid); /* Binding of texture name */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); /* We will use linear interpolation for magnification filter */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); /* We will use linear interpolation for minifying filter */
	glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT),
		0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData()); /* Texture specification */

	glutMainLoop();

	/* Delete used resources and quit */
	ilDeleteImages(1, &image); /* Because we have already copied image data into texture data we can release memory used by image. */
	glDeleteTextures(1, &texid);

	return 0;
}