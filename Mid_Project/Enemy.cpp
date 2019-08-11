#include"Enemy.h"

//constructor set the border condition
Enemy::Enemy() {
	y = -1;
	x_min = 2;
	y_min = 1;
	x_max = WIDTH - 3;
	y_max = HEIGHT - 3;
	cnt_interval = 0;
}

//init the enemy
void Enemy::Init_Enemy(int level) {
	cnt_interval = 0;
	if (level == 0) {	//easy->slow
		move_interval = Rand_Num(10000, 160000);
	}
	else {			//difficult->fast
		move_interval = Rand_Num(4400, 16000);
	}
	y = y_min;
	x = Rand_Num(x_min, x_max) / 3 * 3 + 2;	//to avoid overlap
}

//draw the enemy
void Enemy::Draw_Enemy() {
	if (y != -1) {
		Set_Cursor(x - 1, y);
		cout << "*";
		Set_Cursor(x, y);
		cout << "*";
		Set_Cursor(x + 1, y);
		cout << "*";
		Set_Cursor(x, y + 1);
		cout << "*";
	}
}

//clean the enemy
void Enemy::Clean_Enemy() {
	Set_Cursor(x - 1, y);
	cout << " ";
	Set_Cursor(x, y);
	cout << " ";
	Set_Cursor(x + 1, y);
	cout << " ";
	Set_Cursor(x, y + 1);
	cout << " ";
}

//move the enemy down
void Enemy::Move_Down() {
	if (y == y_max) {
		y = -1;
	}
	else {
		y++;
	}
}

//whether the enemy is valid
bool Enemy::Enemy_Valid() {
	if (y == -1) {
		return false;
	}
	else {
		return true;
	}
}

//to implement different enemy move speed
bool Enemy::Check_Move() {
	if (cnt_interval == move_interval) {
		cnt_interval = 0;
		return true;
	}
	else {
		cnt_interval++;
		return false;
	}
}

//get the pos of enemy 
void Enemy::Get_Pos(int &pos_x, int &pos_y) {
	pos_x = x;
	pos_y = y;
}

//the enemy meet the plane or bullet, has destroyed
void Enemy::Destroy_Enemy() {
	y = -1;
}
