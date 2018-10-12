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
#include <vector>
#include <ctime>
//-----------------
//	Methods Signatures
void Display(void);
void DrawPlayer(void);
void DrawEnemy(void);
void Fire(double,double,double);
void Anim(void);
void EnemyFire(double,double);
void print(int, int, char *);
int* bezier(float , int* , int* , int* , int*);
void drawTriangle(void);
void drawCircle(int, int, float);
void playerFirePush(double,double,double,bool);
bool detectEnemyHit(double, double , double , double);
void updateEnemyHealth(void);
bool detectPlayerHit(double, double , double, double );
void DrawExtraLifePowerUP(double , double );
void DrawDoubleDamagePowerUp(double , double );
bool detectDoubleDamagePowerUpCollision(double, double, double, double);
//-----------------

//	Global Variables
struct bullet { double x; double y; double rotationAngle; bool collided; };
struct powerup { double x; double y; bool collided; };
struct doubleDamageTimer { clock_t start; };
vector<bullet> playerFire{};
vector<bullet> enemyFire ;
vector<bullet> defenderFire ;
vector<powerup> extraLives;
vector<powerup> doubleDamages;
vector<doubleDamageTimer> doubleDamagesTimer;
bool detectExtraLivesPowerUpCollision(double, double, double, double );
int sizeofplayerFire;
double colAnim = 0;     // for fading the background color from white to black
double enemyHealth = 20;
double pastEnemyHealth = 20;
double playerX= 1000;
double playerY = 200;
int playerScore = 0;
int playerLives = 5;
bool doubleDamage = false;
bool fire = true;
bool enemyfire = false;

double fireY = 220;
double enemyX = 0;
double enemyY = 0;

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
	int i = playerFire.size();
	std::string text = "PlayerBullets ";
	text += std::to_string(i);
	char * S = new char[text.length() + 1];
	std::strcpy(S, text.c_str());
	print(1500, 800, S);
	 i = enemyFire.size();
	 text = "EnemyBullets ";
	text += std::to_string(i);
	 S = new char[text.length() + 1];
	std::strcpy(S, text.c_str());
	print(1500, 700, S);
	i = enemyHealth;
	text = "EnemyHealth ";
	text += std::to_string(i);
	S = new char[text.length() + 1];
	std::strcpy(S, text.c_str());
	print(1500, 600, S);
	i = playerLives;
	text = "PlayerLives ";
	text += std::to_string(i);
	S = new char[text.length() + 1];
	std::strcpy(S, text.c_str());
	print(1500, 850, S);
	//Drawing Player
	glPushMatrix();
	glTranslated(playerX, playerY, 0);
	glRotated(playerRotationAngle, 0, 0, 1);
	DrawPlayer();
	glPopMatrix();

	DrawEnemy();
	for (int i = 0; i < playerFire.size(); i++){
		Fire(playerFire[i].x,playerFire[i].y,playerFire[i].rotationAngle);
		bool collided = detectEnemyHit(playerFire[i].x, playerFire[i].y, enemyX, enemyY);
		if (collided){
		
			updateEnemyHealth();
			playerFire[i].collided = true;
		}
	}
	for (int i = 0; i < enemyFire.size(); i++){
		EnemyFire(enemyFire[i].x,enemyFire[i].y);
		bool collided = detectPlayerHit(enemyFire[i].x, enemyFire[i].y, playerX, playerY);
		if (collided){
			playerLives--;
			enemyFire[i].collided = true;
		}
	}
	for (int i = 0; i < extraLives.size(); i++){
		DrawExtraLifePowerUP(extraLives[i].x, extraLives[i].y);
		bool collided = detectExtraLivesPowerUpCollision(extraLives[i].x, extraLives[i].y, playerX, playerY);
		if (collided){
			playerLives++;
			extraLives[i].collided = true;
		}
	}
	for (int i = 0; i < doubleDamages.size(); i++){
		DrawDoubleDamagePowerUp(doubleDamages[i].x, doubleDamages[i].y);
		bool collided = detectDoubleDamagePowerUpCollision(doubleDamages[i].x, doubleDamages[i].y, playerX, playerY);
		if (collided){
			doubleDamage = true;
			doubleDamages[i].collided = true;
			if (doubleDamagesTimer.size() == 0){
				clock_t start = clock();
				doubleDamageTimer t = { start };
				doubleDamagesTimer.push_back(t);

			}
		}
	}
	glFlush(); //must be called to draw
}
void updateEnemyHealth(){
	if (enemyHealth > 1 && doubleDamage ==false)
		enemyHealth--;
	else if (enemyHealth > 2 && doubleDamage == true){
		enemyHealth -= 2;
	}else{
		enemyHealth = pastEnemyHealth * 2;
		pastEnemyHealth = enemyHealth;
	     }
}

bool detectEnemyHit(double playerBulletX,double playerBulletY,double enemyx,double enemyy){
	if (playerBulletX >= enemyx-50 && playerBulletX < enemyx + 100 && playerBulletY<enemyy && playerBulletY >enemyy - 140){
		return true;
	}
	return false;

}
bool detectPlayerHit(double enemyBulletX, double enemyBulletY, double playerx, double playery){
	if (enemyBulletX >= playerx - 70 && enemyBulletX < playerx + 60 && enemyBulletY<playery && enemyBulletY > playery - 110){
		return true;
	}
	return false;
}

bool detectDoubleDamagePowerUpCollision(double powerupx, double powerupy, double playerx, double playery){
	if (powerupx >= playerx - 70 && powerupx < playerx + 60 && powerupy <playery && powerupy> playery - 110){
		return true;
	}
	return false;
}
bool detectExtraLivesPowerUpCollision(double powerupx, double powerupy, double playerx, double playery){
	if (powerupx >= playerx - 70 && powerupx < playerx + 60 && powerupy <playery && powerupy> playery - 110){
		return true;
	}
	return false;
}
void playerFirePush(double x, double y, double rotation, bool collided){
	bullet bullet = { x, y, rotation, collided };
	playerFire.push_back(bullet);
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
void DrawExtraLifePowerUP(double x, double y){
	glPushMatrix();
	glTranslated(x, y, 0);
	glColor3f(0, 1, 0);
	glBegin(GL_QUADS);
	glVertex3d(0, 0, 0);
	glVertex3d(40, 0, 0);
	glVertex3d(40, -40, 0);
	glVertex3d(0, -40, 0);

	glEnd();
	glPopMatrix();
}

void DrawDoubleDamagePowerUp(double x,double y){
	glPushMatrix();
	glTranslated(x, y, 0);
	glColor3f(0, 0, 1);

	glBegin(GL_QUADS);
	glVertex3d(0, 0, 0);
	glVertex3d(40, 0, 0);
	glVertex3d(40, -40, 0);
	glVertex3d(0, -40, 0);

	glEnd();
	glPopMatrix();
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
		playerX = x;
	}
	if (playerX > 1200)
		playerRotationAngle = -5;
	else if (playerX < 800)
		playerRotationAngle = 5;
	else
		playerRotationAngle = 0;
	print(700, 500, "here" );
	//glColor3f(0, 1, 0);
	glutPostRedisplay();

}
void PlayerShooting(int button, int state, int x, int y){
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN &&fire==true )//if the left button has been clicked then translate the square to the mouse position
	{
		
		playerFirePush(x,fireY,playerRotationAngle,false);
		fire = false;
		
	}

	//if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)//if the right button has been clicked, translate  the square to the origin (0,0)
	//{
	//	fire = false;
	//}
}

void Fire(double firex,double firey,double rotationAngle ){
	/*if (fire == true){*/
		glPushMatrix();
		glColor3f(1, 1, 1);
		if (rotationAngle == 0){
			glTranslated(firex + 30, firey, 0);
		}
		else if (rotationAngle < 0){
			glTranslated(firex + 35, firey, 0);
		}
		else if (rotationAngle > 0){
			glTranslated(firex + 25, firey, 0);
		}
		glRotated(rotationAngle, 0, 0, 1);
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
		if (doubleDamage == true){
			glBegin(GL_QUADS);
			glVertex3d(0, -20, 0);
			glVertex3d(20, -20, 0);
			glVertex3d(20, -40, 0);
			glVertex3d(0, -40, 0);
			glEnd();
		}
		glPopMatrix();
	//}
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

void EnemyFire(double enemyFirex,double enemyFirey){
	
		glPushMatrix();
		glColor3f(1, 1, 1);
		glTranslated(enemyFirex+45, enemyFirey, 0);
		glBegin(GL_QUADS);
		glVertex3d(0, 0, 0);
		glVertex3d(20, 0, 0);
		glVertex3d(35, -20, 0);
		glVertex3d(-15, -20, 0);
		glEnd();
		glBegin(GL_QUADS);
		glVertex3d(-15, -20, 0);
		glVertex3d(35, -20, 0);
		glVertex3d(20, -40, 0);
		glVertex3d(0, -40, 0);
		glEnd();
		glColor3f(1, 0.8, 0);
		drawCircle(10, -20, 10);
		glPopMatrix();
	
	
}
void EnemyShootTimer(int val){
	bullet bullet = { enemyX, enemyY, 0, false };
	enemyFire.push_back(bullet);
	
	glutTimerFunc(1500, EnemyShootTimer, 0);
}
void PlayerShootTimer(int val){
	fire = true;
	glutTimerFunc(500, PlayerShootTimer, 0);
}
void DoubleDamagesTimer(int val){
	double x = 100 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 1900));
	powerup powerup = { x, 1100,false };
	doubleDamages.push_back(powerup);
	glutTimerFunc(7000, DoubleDamagesTimer, 0);
}
//void DoubleDamagesEffectTimer(int val){
//	    
//		doubleDamage = val;
//		glutTimerFunc(1000, DoubleDamagesEffectTimer, 0);
//	
//
//}


void  ExtraLivesTimer(int val){
	double x = 100 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 1900));
	powerup powerup = { x, 1100,false };
	extraLives.push_back(powerup);
	glutTimerFunc(10000, ExtraLivesTimer, 0);
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
	for (int i = 0; i < playerFire.size();i++){
		if (playerFire[i].y <= 900 && playerFire[i].collided ==false ){
			playerFire[i].y += 0.5;
		}
		else{
			playerFire.erase(playerFire.begin() + i);
			i--;
		}
		//else{

		//	fire = false;
		//	fireY = 250;
		//}
	}
	for (int i = 0; i < enemyFire.size(); i++){
		if (enemyFire[i].y > 0 && enemyFire[i].collided == false){
			enemyFire[i].y -= 1;
		}
		else {
			enemyFire.erase(enemyFire.begin() + i);
			i--;
		}
	}
	for (int i = 0; i < doubleDamages.size(); i++){
		if (doubleDamages[i].y > 0 && doubleDamages[i].collided == false){
			doubleDamages[i].y -= 1;
		}
		else{
			doubleDamages.erase(doubleDamages.begin() + i);
			i--;
		}
	}
	for (int i = 0; i < extraLives.size(); i++){
		if(extraLives[i].y > 0 && extraLives[i].collided == false){
			extraLives[i].y -= 1;
		}
		else{
			extraLives.erase(extraLives.begin() + i);
			i--;
		}
	}
	if (doubleDamagesTimer.size() > 0){
		double duration = (clock() - doubleDamagesTimer[0].start) / (double)CLOCKS_PER_SEC;
		if (duration >= 5){
			doubleDamage = false;
			doubleDamagesTimer.pop_back();
		}
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
	glutTimerFunc(0, PlayerShootTimer, 0);
	glutTimerFunc(0, DoubleDamagesTimer, 0);
	glutTimerFunc(0, ExtraLivesTimer, 0);
	//glutTimerFunc(0, DoubleDamagesEffectTimer, 0);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	gluOrtho2D(0.0, 2000.0, 0.0, 1000.0);
	glutMainLoop();//nth gets excuted after this
	
}
