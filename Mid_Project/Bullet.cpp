#include"Bullet.h"
#pragma once

//constructor
Bullet::Bullet() {
	y = -1;			//means no exist
	y_min = 1;		//left one row for border
	bullet_speed = 4000;
}

//init the bullet,(x,y) is the center of plane
void Bullet::Init_Bullet(int pos_x, int pos_y) {
	x = pos_x;
	y = pos_y - 2;
	if (y < y_min) {
		y = -1;
	}
}

//clean the bullet
void Bullet::Clean_Bullet() {
	Set_Cursor(x, y);
	cout << " ";
}

//draw the bullet 
void Bullet::Draw_Bullet() {
	if (y != -1) {
		Set_Cursor(x, y);
		cout << "|";
	}
}

//Move the bullet up
void Bullet::Bullet_Up() {
	if (y == y_min) {
		y = -1;
	}
	else {
		y--;
	}
}

//Move the bullet up
void Bullet::Bullet_Down() {
	y++;
}

//whether bullet is valid
bool Bullet::Bullet_Valid() {
	if (y == -1) {
		return false;
	}
	else {
		return true;
	}
}

//get the pos of bullet
void Bullet::Get_Pos(int &pos_x, int &pos_y) {
	pos_x = x;
	pos_y = y;
}

//if bullet meets the enemy, then destroy
void Bullet::Destroy_Bullet() {
	y = -1;
}

//get the intervals of bullet move speed
int Bullet::Get_Speed() {
	return bullet_speed;
}

//init the enemy bullet
void Enemy_Bullet::Init_EnemyBullet(int pos_x, int pos_y) {
	y_max = 28;
	int x = pos_x;
	int y = pos_y + 2;
	if (y > y_max) {
		Destroy_Bullet();
	}
	else {
		Init_Bullet(x, y + 2);
	}
}

//enemy bullet will move down
void Enemy_Bullet::EnemyBullet_Down() {
	int x, y;
	Get_Pos(x, y);
	if (y == y_max) {
		Destroy_Bullet();
	}
	else {
		Bullet_Down();
	}
}

