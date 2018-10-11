// Assignment1.1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <string>
using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

//	Includes
#include <glut.h>
#include <GL/GL.h>
#include <math.h>
#include <iostream>
#include <queue>
#define DEG2RAD 3.14159/180.0

//-----------------
//	Methods Signatures
void Display(void);
void DrawPlayer(void);
void DrawEnemy(void);
void Fire(void);
void Anim(void);
void EnemyFire(void);
void print(int, int, char *);
int* bezier(float , int* , int* , int* , int*);
void drawTriangle(void);
void drawCircle(int, int, float);
//-----------------

//	Global Variables
struct bullet { double x; double y; };

double colAnim = 0;     // for fading the background color from white to black
double enemyHealth = 20;
double playerx = 1000;
bool fire = false;
bool enemyfire = false;
double fireX=20;
double fireY = 150;
double enemyX = 1000;
double enemyY = 700;
double enemyFireX = 1000;//to be changed
double enemyFireY = 700;
double currentEnemyFireY = 700;
double playerRotationAngle = 0;
bool playerAlive = true;
int p0[2];
int p1[2];
int p2[2];
int p3[2];
float bezT = 0;
int tar = 4;

//-----------------


void Display(void)
{
	//glClearColor(colAnim, colAnim, colAnim, 0.0f); // update the background color
	glClearColor(0.5f, colAnim, colAnim, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	//Bezier
	//print(750, 500, "Bezier Control Points");
	//glColor3f(1, 0, 0);
	/*char* p0s[20];
	sprintf((char *)p0s, "P0={%d,%d}", p0[0], p0[1]);
	print(785, 450, (char *)p0s);
	glColor3f(0, 1, 0);
	char* p1s[20];
	sprintf((char *)p1s, "P1={%d,%d}", p1[0], p1[1]);
	print(785, 400, (char *)p1s);
	glColor3f(0, 0, 1);
	char* p2s[20];
	sprintf((char *)p2s, "P2={%d,%d}", p2[0], p2[1]);
	print(785, 350, (char *)p2s);
	glColor3f(1, 1, 1);
	char* p3s[20];
	sprintf((char *)p3s, "P3={%d,%d}", p3[0], p3[1]);
	print(785, 300, (char *)p3s);*/

	//glPointSize(1);
	//glColor3f(1, 1, 0);
	//glBegin(GL_POINTS);
	////for (float t = 0; t<1; t += 0.001)
	////{
	////	int* p = bezier(t, p0, p1, p2, p3);
	////	glVertex3f(p[0], p[1], 0);
	////}
	//glEnd();
	//glPointSize(9);
	//glBegin(GL_POINTS);
	//glColor3f(1, 0, 0);
	//glVertex3f(p0[0], p0[1], 0);
	//glColor3f(0, 1, 0);
	//glVertex3f(p1[0], p1[1], 0);
	//glColor3f(0, 0, 1);
	//glVertex3f(p2[0], p2[1], 0);
	//glColor3f(1, 1, 1);
	//glVertex3f(p3[0], p3[1], 0);
	//glEnd();
	print(playerRotationAngle, 500, "here");
	//Drawing Player
	glPushMatrix();
	glTranslated(playerx, 200, 0);
	//glRotated(playerRotationAngle, 0, 0, 1);
	DrawPlayer();
	glPopMatrix();

	DrawEnemy();
	Fire();
	EnemyFire();
	glFlush(); //must be called to draw
}
void print(int x, int y, char *string)
{
	int len, i;

	//set the position of the text in the window using the x and y coordinates
	glRasterPos2f(x, y);

	//get the length of the string to display
	len = (int)strlen(string);

	//loop to display character by character
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}
void DrawPlayer(){
	if (playerAlive){
	//	glPushMatrix();
		glColor3f(0.2, 0.1, 0.1);
		//glMatrixMode(GL_MODELVIEW);
		//glTranslated(enemyX, enemyY, 0);
		glBegin(GL_QUADS);
		glVertex3d(0, 0, 0);
		glVertex3d(80, 0, 0);
		glVertex3d(100, -50, 0);
		glVertex3d(-20, -50, 0);
		
		glEnd();
		glBegin(GL_QUADS);
		glVertex3d(-20, -50, 0);
		glVertex3d(100, -50, 0);
		glVertex3d(75, -110, 0);
		glVertex3d(5, -110, 0);

		glEnd();

		glColor3f(1, 1, 1);
		glBegin(GL_QUADS);
		glVertex3d(10, 0, 0);
		glVertex3d(70, 0, 0);
		glVertex3d(70, 20, 0);
		glVertex3d(10, 20, 0);

		glEnd();
		glColor3f(0.6, 0.2, 0.2);
		glBegin(GL_QUADS);
		glVertex3d(15, 20, 0);
		glVertex3d(15, 40, 0);
		glVertex3d(25, 40, 0);
		glVertex3d(25, 20, 0);

		glEnd();

		glBegin(GL_QUADS);
		glVertex3d(65, 20, 0);
		glVertex3d(65, 40, 0);
		glVertex3d(55, 40, 0);
		glVertex3d(55, 20, 0);

		glEnd();

		glColor3f(0.9, 0.6, 0.1);
		glBegin(GL_TRIANGLES);
		glVertex3d(5, -110, 0);
		glVertex3d(25, -110, 0);
		glVertex3d(15, -130, 0);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex3d(75, -110, 0);
		glVertex3d(55, -110, 0);
		glVertex3d(65, -130, 0);
		glEnd();
		glColor3f(0, 0, 0);
		glColor3f(0.6, 1, 0.2);
		drawCircle(15, -50, 15);
		glColor3f(0.9, 0, 0.1);
		drawCircle(53, 0, 15);

		//glPopMatrix();
	}
}
//player movement by mouse
void PlayerMovement(int x, int y){
	if (x > 50 && x<1990){
		playerx = x;
	}
	if (playerx > 1200)
		playerRotationAngle = 30;
	else if (playerx < 800)
		playerRotationAngle = -30;
	else
		playerRotationAngle = 0;
	print(700, 500, "here" );
	//glColor3f(0, 1, 0);
	glutPostRedisplay();

}
void PlayerShooting(int button, int state, int x, int y){
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && fire==false)//if the left button has been clicked then translate the square to the mouse position
	{
		fireX = x;
		fire = true;
		
	}

	//if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)//if the right button has been clicked, translate  the square to the origin (0,0)
	//{
	//	fire = false;
	//}
}

void Fire(){
	if (fire == true){
		glPushMatrix();
		glColor3f(1, 1, 1);
		glTranslated(fireX, fireY, 0);
		glBegin(GL_QUADS);
		glVertex3d(0, 0, 0);
		glVertex3d(0, -20, 0);
		glVertex3d(20, -20, 0);
		glVertex3d(20, 0, 0);
		glEnd();
		//left side
		glBegin(GL_TRIANGLES);
		glVertex3d(0, 0, 0);
		glVertex3d(0, -20, 0);
		glVertex3d(-10, -10, 0);
		glEnd();
		//top
		glBegin(GL_TRIANGLES);
		glVertex3d(0, 0, 0);
		glVertex3d(10, 10, 0);
		glVertex3d(20, 0, 0);
		glEnd();
		//right
		glBegin(GL_TRIANGLES);
		glVertex3d(20, 0, 0);
		glVertex3d(20, -20, 0);
		glVertex3d(30, -10, 0);
		glEnd();
		//bottom
		/*glBegin(GL_TRIANGLES);
		glVertex3d(0, -20, 0);
		glVertex3d(20, -20, 0);
		glVertex3d(10, -30, 0);
		glEnd();*/
		glPopMatrix();
	}
}
void drawCircle(int x, int y, float r) {

	glTranslatef(x, y, 0);
	GLUquadric *quadObj = gluNewQuadric();
	gluDisk(quadObj, 0, r, 50, 50);

}

void DrawEnemy(){
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslated(enemyX, enemyY, 0);
	//glRotated(-45, 0, 0, 1);
	glColor3f(0, 0.9, 1);
	glBegin(GL_QUADS);
	glVertex3d(0, 0, 0);
	glVertex3d(100, 0, 0);
	glVertex3d(150, -85, 0);
	glVertex3d(-50, -85, 0);
	glEnd();
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glVertex3d(-35, -85, 0);
	glVertex3d(135, -85, 0);
	glVertex3d(90, -140, 0);
	glVertex3d(10, -140, 0);
	glEnd();
	drawCircle(50, 28, 30);
	glColor3f(0.3, 0.5, 0);
	drawCircle(3, 8, 4);
	glColor3f(1, 0.7, 0.6);
	drawCircle(25, -190, 15);
	drawCircle(-55, 0, 15);
	glColor3f(0, 0, 0);
	glLineWidth(5);
	glBegin(GL_LINES);
	//glLineWidth(5);
	glVertex3d(20, 197, 0);
	glVertex3d(40, 197, 0);
	glEnd();
	glColor3f(1, 0.8, 0.4); 
		glBegin(GL_TRIANGLES);
		
		glVertex2f(55, 195);
		glVertex2f(80, 185);

		glVertex2f(55, 175);
		glEnd();
		glColor3f(0.9, 0.4, 0.5);
		drawCircle(25 ,100, 7);
		drawCircle(1, 30, 7);

	glPopMatrix();
	

}
void drawTriangle(){
	glBegin(GL_TRIANGLES);
	glColor3f(1, 0, 0); // red
	glVertex2f(0, -100);
	glColor3f(0, 1, 0); // green
	glVertex2f(100, 0);
	glColor3f(0, 0, 1); // blue
	glVertex2f(0, 100);
	glEnd();
}
void EnemyFire(){
	if (enemyfire == true){
		glPushMatrix();
		glColor3f(1, 1, 1);
		glTranslated(enemyFireX, enemyFireY, 0);
		glBegin(GL_QUADS);
		glVertex3d(0, 0, 0);
		glVertex3d(20, 0, 0);
		glVertex3d(30, -20, 0);
		glVertex3d(-10, -20, 0);
		glEnd();
		glBegin(GL_QUADS);
		glVertex3d(-10, -20, 0);
		glVertex3d(30, -20, 0);
		glVertex3d(20, -40, 0);
		glVertex3d(0, -40, 0);
		glEnd();
		glColor3f(1, 0.8, 0);
		drawCircle(10, -20, 10);
		glPopMatrix();
	}
}
void EnemyShootTimer(int val){
	enemyfire = true;
	glutTimerFunc(1000, EnemyShootTimer, 0);
}

int* bezier(float t, int* p0, int* p1, int* p2, int* p3)
{
	int res[2];
	res[0] = pow((1 - t), 3)*p0[0] + 3 * t*pow((1 - t), 2)*p1[0] + 3 * pow(t, 2)*(1 - t)*p2[0] + pow(t, 3)*p3[0];
	res[1] = pow((1 - t), 3)*p0[1] + 3 * t*pow((1 - t), 2)*p1[1] + 3 * pow(t, 2)*(1 - t)*p2[1] + pow(t, 3)*p3[1];
	return res;
}
void Anim()
{
	bezT += 0.00001;
	if (bezT <= 1){
		int* p = bezier(bezT, p0, p1, p2, p3);
		enemyX = p[0];
		enemyY = p[1];
	}
	else {
		bezT = 0 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 1));
	}
	if (fireY <= 900 && fire ==true){
		fireY += 0.5;
	}
	else{
		
		fire = false;
		fireY = 150;
	}
	if (enemyFireY > 0 && enemyfire == true){
		enemyFireY -= 1;
	}
	else {
		enemyfire = false;
		enemyFireY = enemyY;
	}
	glutPostRedisplay();
}
void main(int argc, char** argr)
{
	p0[0] = 25;
	p0[1] = 759;

	p1[0] = 900;
	p1[1] = 164;

	p2[0] = 1417;
	p2[1] = 1200;

	p3[0] = 1900;
	p3[1] = 610;
	glutInit(&argc, argr);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(2000, 1000);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Chicken Invaiders");
	glutDisplayFunc(Display);
	glPointSize(50);
	glutIdleFunc(Anim);

	glutPassiveMotionFunc(PlayerMovement);
	glutMouseFunc(PlayerShooting);

	glutTimerFunc(0, EnemyShootTimer, 0);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	gluOrtho2D(0.0, 2000.0, 0.0, 1000.0);
	glutMainLoop();
}
