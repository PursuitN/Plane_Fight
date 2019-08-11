#include"Plane.h"

//constrctor set the border for the plane center
Plane::Plane() {
	x_min = 2;
	x_max = WIDTH - 3;
	y_min = 2;
	y_max = HEIGHT - 3;
	score = 0;
	blood = 5;
	level = 0;
	enemy_nums = 6;
}

//init the plane
void Plane::Init_Plane() {
	x = (x_min + x_max) / 2;
	y = y_max;
}

//draw my plane,(x,y) is the middle pos
void Plane::Draw_Plane() {
	Set_Cursor(x, y - 1);
	cout << "@";
	Set_Cursor(x - 1, y);
	cout << "@";
	Set_Cursor(x, y);
	cout << "@";
	Set_Cursor(x + 1, y);
	cout << "@";
	Set_Cursor(x - 1, y + 1);
	cout << "@";
	Set_Cursor(x, y + 1);
	cout << "@";
	Set_Cursor(x + 1, y + 1);
	cout << "@";
}

//clean the cur plane
void Plane::Clean_Plane() {
	Set_Cursor(x, y - 1);
	cout << " ";
	Set_Cursor(x - 1, y);
	cout << " ";
	Set_Cursor(x, y);
	cout << " ";
	Set_Cursor(x + 1, y);
	cout << " ";
	Set_Cursor(x - 1, y + 1);
	cout << " ";
	Set_Cursor(x, y + 1);
	cout << " ";
	Set_Cursor(x + 1, y + 1);
	cout << " ";
}

//when input 'wasd' then move
void Plane::Move_Plane(char c) {
	if ('w' == c) {
		if (y > y_min) {
			y--;
		}
	}
	else if ('a' == c) {
		if (x > x_min) {
			x--;
		}
	}
	else if ('s' == c) {
		if (y<y_max) {
			y++;
		}
	}
	else if ('d' == c) {
		if (x < x_max) {
			x++;
		}
	}
}

//get the cur pos of the plane to(pos_x, pos_y)
void Plane::Get_Pos(int &pos_x, int &pos_y) {
	pos_x = x;
	pos_y = y;
}

//if bullet hit the enemy, score++
void Plane::Add_Score() {
	score += 1;
}

//an api for getting the player's scores
int Plane::Get_Score() {
	return score;
}

//when collison, decrease the blood
void Plane::Decrease_Blood() {
	blood--;
}

//if blood==0 then die
bool Plane::Check_die() {
	if (blood == 0) {
		return true;
	}
	else {
		return false;
	}
}

//an api for getting the player's scores
int Plane::Get_Blood() {
	return blood;
}

//an api for getting the player's level
int Plane::Get_Level() {
	return level;
}

//set the level
void Plane::Set_Level(int l) {
	level = l;
}

//an api for getting the player's enemy nums
int Plane::Get_EnemyNum() {
	return enemy_nums;
}

//set the enemynum
void Plane::Set_EnemyNum(int l) {
	enemy_nums = l;
}