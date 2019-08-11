#pragma once
#include<iostream>
#include<string>
#include<windows.h>
#include"Control.h"
using namespace std;

#define WIDTH 90		//width max
#define HEIGHT 30		//height max

class Plane {
private:
	int x_min;			//the border for the plane center tomove
	int x_max;	
	int y_min;
	int y_max;
	int x;				//my plane's middle coordinate
	int y;
	int score;			//record the scores
	int blood;			//blood volumn
	int level;			//0 means easy, 1 means difficult
	int enemy_nums;		//max enemy_nums in the screen, easy->6, difficulty->12
public:
	Plane();								//constrctor set the border for the plane center
	void Init_Plane();						//init the plane
	void Draw_Plane();						//draw my plane,(x,y) is the middle pos
	void Clean_Plane();						//clean the cur plane
	void Move_Plane(char c);				//when input 'wasd' then move
	void Get_Pos(int &pos_x, int &pos_y);	//get the cur pos of the plane to(pos_x, pos_y)
	void Add_Score();						//if bullet hit the enemy, score++
	int Get_Score();						//an api for getting the player's scores
	void Decrease_Blood();					//when collison, decrease the blood
	bool Check_die();						//if blood==0 then die
	int Get_Blood();						//an api for getting the player's scores
	int Get_Level();						//an api for getting the player's level
	void Set_Level(int l);					//set the level=l
	int Get_EnemyNum();						//an api for getting the player's enemy nums
	void Set_EnemyNum(int l);				//set the num=l
};