#pragma once
#include<iostream>
#include<string>
#include<windows.h>
#include"Control.h"
using namespace std;

#define WIDTH 90			//width max
#define HEIGHT 30			//height max

class Enemy {
private:
	int x;					//the enemy's coordinate, if y==-1,invalid
	int y;
	int x_min;				//border condition
	int x_max;
	int y_min;
	int y_max;
	int move_interval;		//when up to move_interval then move
	int cnt_interval;		//to cnt for interval
public:
	Enemy();								//constructor set the border condition
	void Init_Enemy(int level);				//init the enemy
	void Draw_Enemy();						//draw the enemy
	void Clean_Enemy();						//clean the enemy
	void Move_Down();						//move the enemy down
	bool Enemy_Valid();						//whether the enemy is valid
	bool Check_Move();						//to implement different enemy move speed
	void Get_Pos(int &pos_x, int &pos_y);	//get the pos of enemy 
	void Destroy_Enemy();					//the enemy meet the plane or bullet, has destroyed
};