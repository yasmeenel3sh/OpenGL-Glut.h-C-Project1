// Assignment1.1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TextureBuilder.h"
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
#define PI 3.14159265
//	Methods Signatures
void Display(void);
void DrawPlayer(void);
void DrawEnemy(void);
void Fire(double,double,double);
void Anim(void);
void EnemyFire(double,double);
void print(int, int, char *);
float* bezier(float , float* , float* , float* , float*);
void drawTriangle(void);
void drawCircle(int, int, float);
void playerFirePush(double,double,double,bool);
bool detectEnemyHit(double, double , double , double);
void updateEnemyHealth(void);
bool detectPlayerHit(double, double , double, double );
void DrawExtraLifePowerUP(double , double );
void DrawDoubleDamagePowerUp(double , double );
bool detectDoubleDamagePowerUpCollision(double, double, double, double);
void DrawDefender(void);
bool detectDefenderHit(double , double , double , double );
void DrawHealthBar(void);
void DrawUnderLyingHealthBar(void);
void PrintEnemyHealth(void);
void PrintPlayerScore(void);
void PrintPlayerLives(void);
void PrintGameOver(void);
void DefenderFire(double, double);
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
double playerScore = 0;
double playerLives = 5;
bool doubleDamage = false;
bool fire = true;
bool enemyfire = false;
bool showDefender = false;
double defenderX = 0;
double fireY = 220;
double enemyX = 0;
double enemyY = 0;
float previousEnemyX = 0;
float previousEnemyY = 0;
double EnemyRotationAngle = 0;
double playerRotationAngle = 0;
bool playerAlive = true;
float p0[2];
float p1[2];
float p2[2];
float p3[2];
float bezT = 0;
int defenderCount = 0;
int defenderShowWait = 4;
double defenderY = 0;
double BackGroundY =1000;
double HealthBarRightX = 600;
bool defenderShowing =false;
int rep = 1;
double bezChangeValue = 0.00025;
bool leftdir = 0;
bool rightdir =1;
double chickenBeakX1 = 55;
double chickenBeakX2 = 80;
GLuint spacetexID;
GLuint extralifetexID;
GLuint defenderID;
GLuint doubledamageID;
bool alreadyPlayed = false;
//-----------------


void Display(void)
{
	
	if (playerLives <= 0 && !alreadyPlayed){
		
		mciSendString(TEXT("play Audio/die.mp3"), NULL, 0, NULL);
		mciSendString(TEXT("play Audio/die2.mp3"), NULL, 0, NULL);
		//playerLives = 10;
		//playerScore = 0;
		enemyHealth = 20;
		pastEnemyHealth = 20;
		HealthBarRightX = 600;
		playerAlive = false;
		alreadyPlayed = true;
		
	}
	//glClearColor(colAnim, colAnim, colAnim, 0.0f); // update the background color
	//glClearColor(0.5f, colAnim, colAnim, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	//BackGround1
	glEnable(GL_TEXTURE_2D);
	glColor3f(0.5, 0.5, 0.5);
	glPushMatrix();
	glTranslated(0, BackGroundY, 0);
	glBindTexture(GL_TEXTURE_2D, spacetexID);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);			glVertex3f(0, 0, 0);
	glTexCoord2f(rep, 0.0f);			glVertex3f(2000, 0, 0);
	glTexCoord2f(rep, rep);				 glVertex3f(2000, 1000, 0);
	glTexCoord2f(0.0f, rep);			 glVertex3f(0, 1000, 0);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	//BackGound2
	glEnable(GL_TEXTURE_2D);
	glColor3f(0.55, 0.55, 0.55);
	glPushMatrix();
	glTranslated(0, BackGroundY, 0);
	glBindTexture(GL_TEXTURE_2D, spacetexID);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);			glVertex3f(0, -1000, 0);
	glTexCoord2f(rep, 0.0f);			glVertex3f(2000, -1000, 0);
	glTexCoord2f(rep, rep);				 glVertex3f(2000, 0, 0);
	glTexCoord2f(0.0f, rep);			 glVertex3f(0, 0, 0);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	//Bezier
	/*print(750, 500, "Bezier Control Points");
	glColor3f(1, 0, 0);
	char* p0s[20];
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
	print(785, 300, (char *)p3s);

	glPointSize(1);
	glColor3f(1, 1, 0);
	glBegin(GL_POINTS);
	for (float t = 0; t<1; t += 0.001)
	{
		float* p = bezier(t, p0, p1, p2, p3);
		glVertex3f(p[0], p[1], 0);
	}
	glEnd();
	glPointSize(9);
	glBegin(GL_POINTS);
	glColor3f(1, 0, 0);
	glVertex3f(p0[0], p0[1], 0);
	glColor3f(0, 1, 0);
	glVertex3f(p1[0], p1[1], 0);
	glColor3f(0, 0, 1);
	glVertex3f(p2[0], p2[1], 0);
	glColor3f(1, 1, 1);
	glVertex3f(p3[0], p3[1], 0);
	glEnd();*/
	/*int i = playerFire.size();
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
	print(1500, 850, S);*/
	if (defenderCount == defenderShowWait){
		DrawDefender();
	}

	for (int i = 0; i < playerFire.size(); i++){
		Fire(playerFire[i].x,playerFire[i].y,playerFire[i].rotationAngle);
		bool collided;
		if (defenderCount ==defenderShowWait){
			collided = detectDefenderHit(playerFire[i].x, playerFire[i].y, defenderX, defenderY);
		}
		else{
		  collided = detectEnemyHit(playerFire[i].x, playerFire[i].y, enemyX, enemyY);
		}
		if (collided){
			if (defenderCount < defenderShowWait){
				updateEnemyHealth();
			}
			playerFire[i].collided = true;
			//PlaySound(TEXT("Audio/chick.wav"), NULL, SND_ASYNC | SND_FILENAME);
			if (defenderCount <defenderShowWait)
			mciSendString(TEXT("play Audio/chick.mp3"), NULL, 0, NULL);
			else
		    mciSendString(TEXT("play Audio/nope.mp3"), NULL, 0, NULL);
		}
	}
	for (int i = 0; i < enemyFire.size(); i++){
		EnemyFire(enemyFire[i].x,enemyFire[i].y);
		bool collided = detectPlayerHit(enemyFire[i].x, enemyFire[i].y, playerX, playerY);
		if (collided){
			playerLives--;

			enemyFire[i].collided = true;
			PlaySound(TEXT("Audio/bump.wav"), NULL, SND_ASYNC | SND_FILENAME);
			//mciSendString(TEXT("play Audio/bump.mp3"), NULL, 0, NULL);
		}
	}
	for (int i = 0; i < defenderFire.size(); i++){
		DefenderFire(defenderFire[i].x+50, defenderFire[i].y-70);
		bool collided = detectPlayerHit(defenderFire[i].x, defenderFire[i].y, playerX, playerY);
		if (collided){
			playerLives--;
			defenderFire[i].collided = true;
			PlaySound(TEXT("Audio/bump.wav"), NULL, SND_ASYNC | SND_FILENAME);
			//mciSendString(TEXT("play Audio/bump.mp3"), NULL, 0, NULL);
		}
	}
	for (int i = 0; i < extraLives.size(); i++){
		DrawExtraLifePowerUP(extraLives[i].x, extraLives[i].y);
		bool collided = detectExtraLivesPowerUpCollision(extraLives[i].x, extraLives[i].y, playerX, playerY);
		if (collided){
			playerLives++;
			extraLives[i].collided=true;
			//PlaySound(TEXT("Audio/pick.wav"), NULL, SND_ASYNC | SND_FILENAME);
			mciSendString(TEXT("play Audio/pick3.wav"), NULL, 0, NULL);
		}
	}
	for (int i = 0; i < doubleDamages.size(); i++){
		DrawDoubleDamagePowerUp(doubleDamages[i].x, doubleDamages[i].y);
		bool collided = detectDoubleDamagePowerUpCollision(doubleDamages[i].x, doubleDamages[i].y, playerX, playerY);
		if (collided){
			doubleDamage = true;
			doubleDamages[i].collided = true;
			//PlaySound(TEXT("Audio/pick.wav"), NULL, SND_ASYNC | SND_FILENAME);
			mciSendString(TEXT("play Audio/pick3.wav"), NULL, 0, NULL);
			if (doubleDamagesTimer.size() == 0){
				clock_t start = clock();
				doubleDamageTimer t = { start };
				doubleDamagesTimer.push_back(t);

			}
		}
	}
	DrawUnderLyingHealthBar();
	DrawHealthBar();
	PrintEnemyHealth();
	PrintPlayerScore();
	PrintPlayerLives();
	//Drawing Player
	glPushMatrix();
	glTranslated(playerX, playerY, 0);
	glRotated(playerRotationAngle, 0, 0, 1);
	DrawPlayer();
	glPopMatrix();

	DrawEnemy();

	if (!playerAlive)
		PrintGameOver();

	glFlush(); //must be called to draw
}
void PrintGameOver(){
	glColor3f(1, 1, 1);
	int i = playerScore;
	std::string text = "Score ";
	text += std::to_string(i);
	char * S = new char[text.length() + 1];
	std::strcpy(S, text.c_str());
	print(900, 600, "Game Over");
	print(920, 500, S);
}
void PrintEnemyHealth(){
	//Printing EnemyHealth
	glColor3f(1, 1, 1);
	int i = enemyHealth;
	std::string text = "";
	text += std::to_string(i);
	char * S = new char[text.length() + 1];
	std::strcpy(S, text.c_str());
	print(980, 910, S);
}
void PrintPlayerScore(){
	glColor3f(1, 1, 1);
	int i = playerScore;
	std::string text = "+";
	text += std::to_string(i);
	char * S = new char[text.length() + 1];
	std::strcpy(S, text.c_str());
	print(1600, 910, S);
}
void PrintPlayerLives(){
	glColor3f(1, 1, 1);
	int i = playerLives;
	std::string text = "x";
	text += std::to_string(i);
	char * S = new char[text.length() + 1];
	std::strcpy(S, text.c_str());
	print(300, 910, S);
	DrawExtraLifePowerUP(200, 960);
}
void updateEnemyHealth(){
	if (enemyHealth > 1 && doubleDamage == false){
		enemyHealth--;
		HealthBarRightX = HealthBarRightX - (600 / pastEnemyHealth);
	}
	else if (enemyHealth > 2 && doubleDamage == true){
		enemyHealth -= 2;
		HealthBarRightX = HealthBarRightX - (1200 / pastEnemyHealth);
	}else{
		enemyHealth = pastEnemyHealth * 2;
		HealthBarRightX = 600;
		pastEnemyHealth = enemyHealth;
	     }
}

bool detectEnemyHit(double playerBulletX,double playerBulletY,double enemyx,double enemyy){
	if (playerBulletX >= enemyx-50 && playerBulletX < enemyx + 80 && playerBulletY<enemyy && playerBulletY >enemyy - 130){
		playerScore++;
		return true;
	}
	return false;

}
bool detectDefenderHit(double playerBulletX, double playerBulletY, double defenderx, double defendery){
	if (playerBulletX >= defenderX && playerBulletX < defenderX+200 && playerBulletY<defendery && playerBulletY> defenderY-50 ){
		return true;
	}
	return false;

}
bool detectPlayerHit(double enemyBulletX, double enemyBulletY, double playerx, double playery){
	if (enemyBulletX >= playerx - 70 && enemyBulletX < playerx + 60 && enemyBulletY-100<playery && enemyBulletY > playery -110 && playerAlive){
		return true;
	}
	return false;
}

bool detectDoubleDamagePowerUpCollision(double powerupx, double powerupy, double playerx, double playery){
	if (powerupx >= playerx - 70 && powerupx < playerx + 60 && powerupy-100 <playery && powerupy> playery - 110 && playerAlive){
		return true;
	}
	return false;
}
bool detectExtraLivesPowerUpCollision(double powerupx, double powerupy, double playerx, double playery ){
	if (powerupx >= playerx - 70 && powerupx < playerx + 60 && powerupy - 100 <playery && powerupy> playery - 110 && playerAlive){
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
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24
			, string[i]);
	}
}
void DrawExtraLifePowerUP(double x, double y){
	/*glPushMatrix();
	glTranslated(x, y, 0);
	glColor3f(0, 1, 0);
	glBegin(GL_QUADS);
	glVertex3d(0, 0, 0);
	glVertex3d(40, 0, 0);
	glVertex3d(40, -40, 0);
	glVertex3d(0, -40, 0);

	glEnd();
	glPopMatrix();*/
	glEnable(GL_TEXTURE_2D);
	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslated(x, y, 0);

	glBindTexture(GL_TEXTURE_2D, extralifetexID);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, rep); glVertex3d(0, 0, 0);
	glTexCoord2f(rep, rep);  glVertex3d(70, 0, 0);
	glTexCoord2f(rep, 0.0f);	 glVertex3d(70, -70, 0);
	glTexCoord2f(0.0f, 0.0f); glVertex3d(0, -70, 0);

	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void DrawDoubleDamagePowerUp(double x,double y){
	/*glPushMatrix();
	glTranslated(x, y, 0);
	glColor3f(0, 0, 1);

	glBegin(GL_QUADS);
	glVertex3d(0, 0, 0);
	glVertex3d(40, 0, 0);
	glVertex3d(40, -40, 0);
	glVertex3d(0, -40, 0);

	glEnd();
	glPopMatrix();*/
	glEnable(GL_TEXTURE_2D);
	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslated(x, y, 0);

	glBindTexture(GL_TEXTURE_2D, doubledamageID);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, rep); glVertex3d(0, 0, 0);
	glTexCoord2f(rep, rep);  glVertex3d(70, 0, 0);
	glTexCoord2f(rep, 0.0f);	 glVertex3d(70, -70, 0);
	glTexCoord2f(0.0f, 0.0f); glVertex3d(0, -70, 0);

	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}
void DrawDefender(){
	//glPushMatrix();

	//glTranslated(defenderX, defenderY, 0);
	//glRotated(EnemyRotationAngle, 0, 0, 1);
	//glColor3f(0, 0, 1);

	//glBegin(GL_QUADS);
	//glVertex3d(0, 0, 0);
	//glVertex3d(200, 0, 0);
	//glVertex3d(200, -60, 0);
	//glVertex3d(0, -60, 0);

	//glEnd();
	//glPopMatrix();
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslated(defenderX, defenderY, 0);
	glRotated(EnemyRotationAngle, 0, 0, 1);
	glBindTexture(GL_TEXTURE_2D, defenderID);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, rep);	glVertex3d(0, 0, 0);
	glTexCoord2f(rep, rep);    glVertex3d(200, 0, 0);
	glTexCoord2f(rep, 0.0f);     glVertex3d(200, -100, 0);
	glTexCoord2f(0.0f, 0.0f);    glVertex3d(0, -100, 0);

	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}
void DrawHealthBar(){
	glPushMatrix();

	glTranslated(700, 950, 0);

	

	glBegin(GL_QUADS);
	glColor3f(0, 0.7, 0.8);
	glVertex3d(0, 0, 0);
	glColor3f(0, 0.9, 0.5);
	glVertex3d(HealthBarRightX, 0, 0);
	glColor3f(0, 0.7, 0.8);
	glVertex3d(HealthBarRightX, -50, 0);
	glColor3f(0, 0.9, 0.5);
	glVertex3d(0, -50, 0);

	glEnd();
	glPopMatrix();
}
void DrawUnderLyingHealthBar(){
	glPushMatrix();

	glTranslated(700, 950, 0);



	glBegin(GL_QUADS);
	//glColor3f(1, 0.2, 0.1);
	glColor3f(0.7, 0.7, 0.7);
	glVertex3d(0, 0, 0);
	//glColor3f(0.75, 0.75, 0.75);
	glVertex3d(600, 0, 0);
	//glColor3f(1, 0.2, 0.1);
	glVertex3d(600, -50, 0);
	//glColor3f(0.75, 0.75, 0.75);
	glVertex3d(0, -50, 0);

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
		mciSendString(TEXT("play Audio/gun2.mp3 "), NULL, 0, NULL);
		playerFirePush(playerX,fireY,playerRotationAngle,false);
		fire = false;
		
	}

	//if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)//if the right button has been clicked, translate  the square to the origin (0,0)
	//{
	//	fire = false;
	//}
}
void key(unsigned char k, int x, int y)//keyboard function, takes 3 parameters

{
	if (k == ' ' && fire ==true){
		mciSendString(TEXT("play Audio/gun2.mp3 "), NULL, 0, NULL);
		playerFirePush(playerX, fireY, playerRotationAngle, false);
		fire = false;
	}
	
	glutPostRedisplay();//redisplay to update the screen with the changes
}
void spe(int k, int x, int y)
{
	if (k == GLUT_KEY_RIGHT && playerX < 1990){
		playerX += 30;
		if (playerX > 50 && playerX < 1400)
			playerRotationAngle = -5;
		else if (playerX > 1400 && playerX < 1990)
			playerRotationAngle = -8;
		else
			playerRotationAngle = 0;
	}
	if (k == GLUT_KEY_LEFT && playerX > 50){
		playerX -= 30;
		if (playerX < 1990 && playerX>600)
			playerRotationAngle = 5;
		else if (playerX < 600 && playerX >50)
			playerRotationAngle = 8;
		else
			playerRotationAngle = 0;
	}
	
	/*if (playerX > 1200)
		playerRotationAngle = -5;
	else if (playerX < 800)
		playerRotationAngle = 5;
	else
		playerRotationAngle = 0;*/
	glutPostRedisplay();
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
		
		glColor3f(0.9, 0.7, 0.0);
		glVertex3d(0, 0, 0);

		glColor3f(0.6, 0.9, 0.9);
		glVertex3d(0, -20, 0);

		glColor3f(0.6, 0.9, 0.9);
		glVertex3d(20, -20, 0);

		glColor3f(0.9, 0.7, 0.0);
		glVertex3d(20, 0, 0);
		glEnd();
		//left side
		glBegin(GL_TRIANGLES);
		glColor3f(0.9, 0.7, 0);
		glVertex3d(0, 0, 0);
		
		glColor3f(0.6, 0.9, 0.9);
		glVertex3d(0, -20, 0);

		glColor3f(0.9, 0.7, 0);
		glVertex3d(-10, -10, 0);
		glEnd();
		//top
		glBegin(GL_TRIANGLES);
		glColor3f(0.9, 0.7, 0);
		//glColor3f(0.6, 0.9, 0.9);
		glVertex3d(0, 0, 0);

		//glColor3f(0.9, 0.7, 0);
		glVertex3d(10, 10, 0);

		//glColor3f(0.6, 0.9, 0.9);
		glVertex3d(20, 0, 0);
		glEnd();
		//right
		glBegin(GL_TRIANGLES);
		glColor3f(0.9, 0.7, 0);
		glVertex3d(20, 0, 0);

		glColor3f(0.6, 0.9, 0.9);
		glVertex3d(20, -20, 0);

		glColor3f(0.9, 0.7, 0);
		glVertex3d(30, -10, 0);
		glEnd();
		//bottom
		if (doubleDamage == true){
			glBegin(GL_QUADS);
			glColor3f(0.6, 0.9, 0.9);
			glVertex3d(0, -20, 0);
			glVertex3d(20, -20, 0);
			glColor3f(0.9, 0.7, 0);
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
	glRotated(EnemyRotationAngle, 0, 0, 1);
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
	 //glColor3f(0.9, 0.7, 0.3);
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
		
		glVertex2f(chickenBeakX1, 195);
		glVertex2f(chickenBeakX2, 185);

		glVertex2f(chickenBeakX1, 175);
		glEnd();
		glColor3f(0.9, 0.4, 0.5);
		drawCircle(25 ,100, 7);
		drawCircle(1, 30, 7);

	glPopMatrix();
	

}

void EnemyFire(double enemyFirex,double enemyFirey){
	
		glPushMatrix();
		glColor3f(1, 1, 1);
		glTranslated(enemyFirex+45, enemyFirey-100, 0);
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
void DefenderFire(double defenderFirex,double defenderFirey){
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslated(defenderFirex + 45, defenderFirey , 0);
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
	
	glutTimerFunc(750, EnemyShootTimer, 0);
}
void DefenderShootTimer(int val){
	bullet bullet = { defenderX, defenderY, 0, false };
	defenderFire.push_back(bullet);
	glutTimerFunc(400, DefenderShootTimer, 0);
}
void PlayerShootTimer(int val){
	fire = true;
	glutTimerFunc(250, PlayerShootTimer, 0);
}
void DoubleDamagesTimer(int val){
	double x = 100 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 1900));
	powerup powerup = { x, 1100,false };
	doubleDamages.push_back(powerup);
	double timer = 1000 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 2000));
	glutTimerFunc(timer, DoubleDamagesTimer, 0);
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
	double timer = 1000 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 5000));
	glutTimerFunc(timer, ExtraLivesTimer, 0);
}
float* bezier(float t, float* p0, float* p1, float* p2, float* p3)
{
	float res[2];
	res[0] = pow((1 - t), 3)*p0[0] + 3 * t*pow((1 - t), 2)*p1[0] + 3 * pow(t, 2)*(1 - t)*p2[0] + pow(t, 3)*p3[0];
	res[1] = pow((1 - t), 3)*p0[1] + 3 * t*pow((1 - t), 2)*p1[1] + 3 * pow(t, 2)*(1 - t)*p2[1] + pow(t, 3)*p3[1];
	return res;
}
void Anim()
{

	if (BackGroundY >0){
		BackGroundY -= 0.2;
	}
	else{
		BackGroundY = 1000;
	}
	//if (right ==true)
	bezT += 0.00025;
	if (bezT <= 1){
		float* p = bezier(bezT, p0, p1, p2, p3);
		enemyX = p[0];
		enemyY = p[1];
		double tan = (enemyY - previousEnemyY) / (enemyX - previousEnemyX);
		EnemyRotationAngle = atan(tan) * 180 / PI;
		previousEnemyX = enemyX;
		previousEnemyY = enemyY;
		defenderX = enemyX - 60;
		defenderY = enemyY - 180;
	}
	else {
		p1[0] = 300 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 1700));
		p2[0] = 300 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 1700));
		p1[1] = 400 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 800));
		p2[1] = 400 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 800));
		/*p0[1] = 200 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 800));
		p3[1] = 300 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 500));*/
		//bezT = 0 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 1));
		
		if (defenderCount < defenderShowWait){
			defenderCount++;
		}
		else{
			defenderCount = 0;
			
		}
		bezT = 0;
		rightdir = !rightdir;
		if (!rightdir){
			chickenBeakX1 = 0;
			chickenBeakX2 = -25;
			std::swap(p0, p3);

		}
		else{
			chickenBeakX1 = 55;
			chickenBeakX2 = 80;
			std::swap(p0, p3);
		}
	}
	for (int i = 0; i < playerFire.size();i++){
		if (playerFire[i].y <= 1100 && playerFire[i].collided ==false ){
			playerFire[i].y += 1.7;
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
	for (int i = 0; i < defenderFire.size(); i++){
		if (defenderFire[i].y > 0 && defenderFire[i].collided == false && defenderCount == defenderShowWait){
			defenderFire[i].y -= 1;
		}
		else{
			defenderFire.erase(defenderFire.begin() + i);
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
	p0[0] = -400;
	p0[1] =800;

	p1[0] = 200;
	p1[1] = 200;

	p2[0] = 1417;
	p2[1] = 1000;

	p3[0] = 2140;
	p3[1] = 710;
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
	glutKeyboardFunc(key);
	glutSpecialFunc(spe);
	glutTimerFunc(0, EnemyShootTimer, 0);
	glutTimerFunc(0, DefenderShootTimer, 0);
	glutTimerFunc(0, PlayerShootTimer, 0);
	glutTimerFunc(0, DoubleDamagesTimer, 0);
	glutTimerFunc(0, ExtraLivesTimer, 0);
	//glutTimerFunc(0, DoubleDamagesEffectTimer, 0);
	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//glEnable(GL_TEXTURE_2D);
	gluOrtho2D(0.0, 2000.0, 0.0, 1000.0);
	loadBMP(&spacetexID, "textures/space2.bmp", true);
	loadBMP(&extralifetexID, "textures/life.bmp", true);
	loadBMP(&defenderID, "textures/defender.bmp", true);
	loadBMP(&doubledamageID, "textures/doubledamage.bmp", true);
	//PlaySound(TEXT("Audio/theme1.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);

	mciSendString(TEXT("play Audio/theme3.mp3 repeat"), NULL, 0, NULL);
	glutMainLoop();//nth gets excuted after this
	
}
