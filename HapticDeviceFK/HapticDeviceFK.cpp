#include "stdafx.h"
#include <iostream>
#include <GL\freeglut.h>
#include <math.h>


/*  Globals */
double dim = 40.0; /* dimension of orthogonal box */
const char *windowName = "Forward Kin Haptic Device";
int windowWidth = 1200;
int windowHeight = 1200;
double cameraAngle1 = 0;
double cameraAngle2 = 0;
double cameraAngle3 = 0;


/*  Various global state */
int th = 340;   /* azimuth of view angle */
int ph = 30;    /* elevation of view angle */
int fov = 55;   /* field of view for perspective */
int asp = 1;    /* aspect ratio */



				//Function used to draw the frames for each joint
void drawFrame() {

	glPushMatrix();
	glPushMatrix();
	//Red to represent x axis
	glColor3f(1, 0, 0);
	glTranslatef(1, 0, 0);
	glScalef(2, 0.5, 0.5);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	//Green to represent y axis
	glColor3f(0, 1, 0);
	glTranslatef(0, 1, 0);
	glScalef(0.5, 2, 0.5);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	//Blue to represent z axis
	glColor3f(0, 0, 1);
	glTranslatef(0, 0, 1);
	glScalef(0.5, 0.5, 2);
	glutSolidCube(1);
	glColor3f(1, 1, 1);
	glPopMatrix();
	glPopMatrix();

}


class hapticDeivce {

public:
	//inital joint angles
	double theta1 = 0, theta2 = 45, theta3 = -45, theta4 = 0, theta5 = 45, theta6 = 0;

	void initHapticDevice() {

		//Draw cone (Base Platform for the Haptic Device
		glPushMatrix();
		glTranslatef(0, -10, 0);
		glRotatef(90, 1, 0, 0);
		glRotatef(180, 0, 1, 0);
		glutWireCone(-10, 10, 40, 40);
		glPopMatrix();

		//Draw the sphere
		glRotatef(-90, 1, 0, 0);
		glPushMatrix();
		glRotatef(theta1, 0, 0, 1); // Rotation of Joint 1
		glPushMatrix();
		glColor3f(0.4, 0.4, 0.4);
		glutWireSphere(8, 30, 30);
		drawFrame();
		glColor3f(0, 0, 1);
		glTranslatef(8, 0, 0);
		glutSolidSphere(2, 100, 100); // Draw Sphere that marks the front of the device
		glPopMatrix();


		glPushMatrix();
		glRotatef(-90, 1, 0, 0);
		glRotatef(theta2, 0, 0, 1); // Rotation of Joint 2
		drawFrame();
		glPushMatrix();
		glTranslatef(7, 0, 0);
		glScalef(14, 2, 0.75);
		glColor3f(1, 1, 1);
		glutWireCube(1);
		glPopMatrix();


		glPushMatrix();
		glRotatef(-90, 0, 0, 1);
		glTranslatef(0, 13, 0);
		glRotatef(theta3, 0, 0, 1); // Rotation of Joint 3
		drawFrame();
		glPushMatrix();
		glTranslatef(0, 3, 1);
		glScalef(2, 8, 0.75);
		glutWireCube(1);
		glPopMatrix();


		glPushMatrix();
		glRotatef(-90, 1, 0, 0);
		glTranslatef(0, -1, 7);
		glRotatef(theta4, 0, 0, 1); // Rotation of Joint 4
		drawFrame();
		glPushMatrix();
		glTranslatef(0, 0, 0.5);
		glPushMatrix();
		glScalef(2, 1, 1);
		glutWireCube(1);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0, 1, 0);
		glScalef(2, 1.5, 1);
		glutWireCube(1);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0, -1, 0);
		glScalef(2, 1.5, 1);
		glutWireCube(1);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0, 2, 2);
		glScalef(2, 1.5, 6);
		glutWireCube(1);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0, -2, 2);
		glScalef(2, 1.5, 6);
		glutWireCube(1);
		glPopMatrix();
		glPopMatrix();



		glRotatef(90, 1, 0, 0);
		glTranslatef(0, 4.5, 0);
		glRotatef(theta5, 0, 0, 1); // Rotation of Joint 5
		drawFrame();
		glPushMatrix();
		glPushMatrix();
		glScalef(2, 7, 0.75);
		glutWireCube(1);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0, 0, 1);
		glScalef(2, 1, 0.75);
		glutWireCube(1);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0, 0, -1);
		glScalef(2, 1, 0.75);
		glutWireCube(1);
		glPopMatrix();
		glPopMatrix();


		glPushMatrix();
		glRotatef(-90, 1, 0, 0);
		glRotatef(theta6, 0, 0, 1); // Rotation of Joint 6
		drawFrame();
		glPushMatrix();
		glTranslatef(0, 0, 10.25);
		glScalef(2, 0.75, 13.5);
		glutWireCube(1);
		glPopMatrix();
		glPopMatrix();

		glPopMatrix();
		glPopMatrix();
		glPopMatrix();
		glPopMatrix();

	}
};

//Instantiate haptic device
hapticDeivce * device = new hapticDeivce();

//For text rendering at designated raster position
void renderBitmap(double x, double y, double z, void *font, char *string) {

	char *c;
	glRasterPos3f(x, y, z);
	for (c = string; *c != 0; c++) {
		glutBitmapCharacter(font, *c);
	}
}

//Utilize renderBitmap to render text
void addText() {
	glLoadIdentity();
	glPushMatrix();
	glColor3f(1, 1, 1);
	char buf[300] = { 0 };
	sprintf_s(buf, "Press number from 1 to 6 to increment the joint angle for the corresponding joint number");
	renderBitmap(-35, 35, 0, GLUT_BITMAP_HELVETICA_12, buf);
	sprintf_s(buf, "Press Shift + number from 1 to 6 to decrement the joint angle for the corresponding joint number");
	renderBitmap(-35, 34, 0, GLUT_BITMAP_HELVETICA_12, buf);
	glPopMatrix();
}

//glOrtho to set the projection
void project()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-dim * asp, +dim * asp, -dim, +dim, -dim, +dim);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//Set original camera angle
void setEye()
{
	glRotatef(ph + cameraAngle1, 1, 0, 0);
	glRotatef(th + cameraAngle2, 0, 1, 0);
	glRotatef(cameraAngle3, 0, 0, 1);
}


//Display funtion to use in glutDisplayFunc() call back
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();
	setEye();
	device->initHapticDevice(); //draw haptic device
	addText(); // add instructions on contorls
	glFlush();
	glutSwapBuffers();
}


//Called when window is changed
void reshape(int width, int height)
{
	asp = (height > 0) ? (double)width / height : 1;
	glViewport(0, 0, width, height);
	project();
}

//Keyboardfunc to be used for controlling the joint angle
void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case '1':
		device->theta1 = fmod((device->theta1 + 1), 360);
		glutPostRedisplay();
		addText();
		break;
	case '2':
		device->theta2 = fmod((device->theta2 + 1), 360);
		glutPostRedisplay();
		break;
	case '3':
		device->theta3 = fmod((device->theta3 + 1), 360);
		glutPostRedisplay();
		break;
	case '4':
		device->theta4 = fmod((device->theta4 + 1), 360);
		glutPostRedisplay();
		break;
	case '5':
		device->theta5 = fmod((device->theta5 + 1), 360);
		glutPostRedisplay();
		break;
	case '6':
		device->theta6 = fmod((device->theta6 + 1), 360);
		glutPostRedisplay();
		break;
	case '!':
		device->theta1 = fmod((device->theta1 - 1), 360);
		glutPostRedisplay();
		break;
	case '@':
		device->theta2 = fmod((device->theta2 - 1), 360);
		glutPostRedisplay();
		break;
	case '#':
		device->theta3 = fmod((device->theta3 - 1), 360);
		glutPostRedisplay();
		break;
	case '$':
		device->theta4 = fmod((device->theta4 - 1), 360);
		glutPostRedisplay();
		break;
	case '%':
		device->theta5 = fmod((device->theta5 - 1), 360);
		glutPostRedisplay();
		break;
	case '^':
		device->theta6 = fmod((device->theta6 - 1), 360);
		glutPostRedisplay();
		break;
	case 'w':
		cameraAngle1 += 1;
		glutPostRedisplay();
		break;
	case 'W':
		cameraAngle1 -= 1;
		glutPostRedisplay();
		break;
	case 'e':
		cameraAngle2 += 1;
		glutPostRedisplay();
		break;
	case 'E':
		cameraAngle2 -= 1;
		glutPostRedisplay();
		break;
	case 'r':
		cameraAngle3 += 1;
		glutPostRedisplay();
		break;
	case 'R':
		cameraAngle3 -= 1;
		glutPostRedisplay();
		break;

	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

//Main function of the project, set callbacks and loop
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow(windowName);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}


