#pragma once
#include<iostream>
#include<string>
#include<windows.h>
#include"Control.h"
using namespace std;

class Bullet {
private:
	int x;				//the bullet's coordinate,y=-1 means no existing
	int y;
	int y_min;			//the min y or the bullet will display
	int bullet_speed;	//to control the speed of the bullet
public:
	Bullet();										//constructor
	void Init_Bullet(int pos_x, int pos_y);			//init the bullet,(x,y) is the center of plane
	void Clean_Bullet();							//clean the bullet
	void Draw_Bullet();								//draw the bullet 
	void Bullet_Up();								//Move the bullet up
	void Bullet_Down();								//Move the bullet down
	bool Bullet_Valid();							//whether bullet is valid
	void Get_Pos(int &pos_x, int &pos_y);			//get the pos of bullet
	void Destroy_Bullet();							//if bullet meets the enemy, then destroy
	int Get_Speed();								//get the intervals of bullet move speed
};

class Enemy_Bullet:public Bullet {
private:
	int y_max;			//the max y or the bullet will disappear
public:
	void Init_EnemyBullet(int pos_x, int pos_y);	//init the enemy bullet
	void EnemyBullet_Down();						//enemy bullet will move down
};



