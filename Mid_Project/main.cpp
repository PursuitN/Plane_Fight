#include<iostream>
#include<string>
#include<windows.h>
#include<conio.h>
#include"Bullet.h"
#include"Control.h"
#include"Enemy.h"
#include"Plane.h"
using namespace std;

#define BULLET_MAX 20				//max bullet nums

//find one unuse bullet to shoot, the center of plane is(x,y)
void Shoot_Bullet(Bullet *bullet,int x,int y) {
	for (int i = 0; i < BULLET_MAX; i++) {
		if (bullet[i].Bullet_Valid() == false) {
			bullet[i].Init_Bullet(x, y);
			bullet[i].Draw_Bullet();
			break;
		}
	}
}

//bullet will up by nature
void Handle_Bullet(Bullet *bullet,int &bullet_speed_cnt) {
	if (bullet_speed_cnt == bullet->Get_Speed()) {
		bullet_speed_cnt = 0;
		for (int i = 0; i < BULLET_MAX; i++) {
			if (bullet[i].Bullet_Valid() == true) {
				bullet[i].Clean_Bullet();
				bullet[i].Bullet_Up();
				bullet[i].Draw_Bullet();
			}
		}
	}
	else {
		bullet_speed_cnt++;
	}
}

//enemy bullet will down by nature
void Handle_EnemyBullet(Plane &plane,Enemy_Bullet *bullet, int &bullet_speed_cnt) {
	if (bullet_speed_cnt == bullet->Get_Speed()) {
		bullet_speed_cnt = 0;
		for (int i = 0; i < plane.Get_EnemyNum(); i++) {
			if (bullet[i].Bullet_Valid() == true) {
				bullet[i].Clean_Bullet();
				bullet[i].EnemyBullet_Down();
				bullet[i].Draw_Bullet();
			}
		}
	}
	else {
		bullet_speed_cnt++;
	}
}

//every enemy_produce_time produce enemy, and the time is changing
void Produce_Enemy(Plane &plane, Enemy *enemy, int &time_interval, int &enemy_produce_time,Enemy_Bullet*enemy_bullet) {
	if (time_interval == enemy_produce_time) {
		enemy_produce_time = Rand_Num(8000, 80000);
		//enemy_produce_time = Rand_Num(40000, 1000000);
		time_interval = 0;
		for (int i = 0; i < plane.Get_EnemyNum(); i++) {
			if (enemy[i].Enemy_Valid() == false) {
				enemy[i].Init_Enemy(plane.Get_Level());
				enemy[i].Draw_Enemy();
				int e_x, e_y;
				enemy[i].Get_Pos(e_x, e_y);
				enemy_bullet[i].Clean_Bullet();
				enemy_bullet[i].Init_EnemyBullet(e_x,e_y);
				enemy_bullet[i].Draw_Bullet();
				break;
			}
		}
	}
	else {
		time_interval++;
	}
}

//enemy will down by nature
void Handle_Enemy(Plane &plane,Enemy *enemy) {
	for (int i = 0; i < plane.Get_EnemyNum(); i++) {
		if (enemy[i].Enemy_Valid() == true&&enemy[i].Check_Move()==true) {
			enemy[i].Clean_Enemy();
			enemy[i].Move_Down();
			enemy[i].Draw_Enemy();
		}
	}
}

//check one plane and one enemy whether is overlap, 1 means overlap
bool Check_Plane_Enemy(Plane *plane, Enemy *enemy) {
	int p_x, p_y;
	plane->Get_Pos(p_x, p_y);
	int e_x, e_y;
	enemy->Get_Pos(e_x, e_y);
	if (e_x >= p_x - 2 && e_x <=p_x + 2 && e_y == p_y) {
		return true;
	}
	else if (e_x >= p_x - 1 &&e_x<=p_x+1&& e_y == p_y - 1) {
		return true;
	}
	else {
		return false;
	}
}

//check enemy bullet whether is overlap my plane, 1means overlap
bool Check_Bullet_Plane(Enemy_Bullet *bullet, Plane *plane) {
	int b_x, b_y;
	bullet->Get_Pos(b_x, b_y);
	int p_x, p_y;
	plane->Get_Pos(p_x, p_y);
	if (b_x == p_x - 1 && b_y == p_y) {
		return true;
	}
	else if (b_x == p_x && b_y == p_y - 1) {
		return true;
	}
	else if (b_x == p_x + 1 && b_y == p_y) {
		return true;
	}
	else {
		return false;
	}
}

//if plane and enemy overlap, handle it, return -1 and enemy bullet hit my plane
int Handle_Plane_Enemy(Plane *plane, Enemy *enemy,Enemy_Bullet*enemy_bullet) {
	int check = 0;
	for (int i = 0; i < plane->Get_EnemyNum(); i++) {
		if (enemy[i].Enemy_Valid() == true) {
			check = Check_Plane_Enemy(plane, &enemy[i]);
			if (check == 1) {
				//plane->Clean_Plane();
				enemy[i].Clean_Enemy();
				enemy[i].Destroy_Enemy();
				plane->Draw_Plane();
				plane->Decrease_Blood();
				Set_Blood(plane->Get_Blood());
				if (plane->Check_die() == true) {
					return -1;
				}
			}
		}
		if (enemy_bullet[i].Bullet_Valid() == true) {
			check = Check_Bullet_Plane( &enemy_bullet[i],plane);
			if (check == 1) {
				//plane->Clean_Plane();
				enemy_bullet[i].Clean_Bullet();
				enemy_bullet[i].Destroy_Bullet();
				plane->Draw_Plane();
				plane->Decrease_Blood();
				Set_Blood(plane->Get_Blood());
				if (plane->Check_die() == true) {
					return -1;
				}
			}
		}
	}
	return 1;
}

//check one bullet and one enemy whether is overlap, 1 means overlap
bool Check_Bullet_Enemy(Bullet *bullet, Enemy *enemy) {
	int b_x, b_y;
	bullet->Get_Pos(b_x, b_y);
	int e_x, e_y;
	enemy->Get_Pos(e_x, e_y);
	if (b_x == e_x - 1 && b_y == e_y) {
		return true;
	}
	else if (b_x == e_x && b_y == e_y + 1) {
		return true;
	}
	else if (b_x == e_x + 1 && b_y == e_y) {
		return true;
	}
	else {
		return false;
	}
}

//if bullet and enemy overlap, handle it, return -1
void Handle_Bullet_Enemy(Bullet *bullet, Enemy *enemy,Plane &plane){
	int check = 0;
	for (int i = 0; i < BULLET_MAX; i++) {
		if (bullet[i].Bullet_Valid() == true) {
			for (int j = 0; j < plane.Get_EnemyNum(); j++) {
				if (enemy[j].Enemy_Valid() == true) {
					check = Check_Bullet_Enemy(&bullet[i], &enemy[j]);
					if (check == 1) {
						bullet[i].Clean_Bullet();
						bullet[i].Destroy_Bullet();
						enemy[j].Clean_Enemy();
						enemy[j].Destroy_Enemy();
						plane.Add_Score();
						Set_Score(plane.Get_Score());
					}
				}
			}
		}
	}
}

//when playing normal, -> wasd  and space to control, 1->suspend 2->lose 2->quit_game
int Keyboard_Control(Plane &plane,Bullet *bullet,Enemy *enemy,Enemy_Bullet*enemy_bullet) {
	char input;
	int bullet_speed_cnt = 0;
	int enemybullet_speed_cnt = 0;
	int enemy_produce_cnt = 0;
	int enemy_speed_cnt = 0;
	int enemy_produce_time = 0;
	while (1) {
		if (_kbhit()) {
			input = _getch();
			if (input == 'q') {
				return 2;
			}
			else if (input == 'p') {
				return 1;
			}
			else if (input == ' ') {
				int plane_x, plane_y;
				plane.Get_Pos(plane_x, plane_y);
				Shoot_Bullet(bullet,plane_x,plane_y);
			}
			else {
				plane.Clean_Plane();
				plane.Move_Plane(input);
				plane.Draw_Plane();
			}
		}
		Produce_Enemy(plane,enemy, enemy_produce_cnt,enemy_produce_time,enemy_bullet);
		Handle_Enemy(plane,enemy);
		Handle_Bullet(bullet,bullet_speed_cnt);
		Handle_EnemyBullet(plane,enemy_bullet, enemybullet_speed_cnt);
		Handle_Bullet_Enemy(bullet, enemy, plane);
		if (Handle_Plane_Enemy(&plane, enemy,enemy_bullet) == -1) {
			return 2;
		}
	}
	return 0;
}

//choose the difficuly of the game
void Choose_Level(Plane &plane) {
	int temp=0;
	Set_Cursor(44, 22);
	Display_Cursor();
	cin >> temp;
	Hide_Cursor();
	Set_Cursor(15, 25);
	if (temp == 1) {
		plane.Set_Level(1);
		cout << ">> 你选择的难度为难";
	}
	else {
		plane.Set_Level(0);
		cout << ">> 你选择的难度为简单";
	}
	if (plane.Get_Level()==0) {
		plane.Set_EnemyNum(6);
	}
	else {
		plane.Set_EnemyNum(12);
	}
}

//main func
int main() {

	srand((int)time(0));
	Hide_Cursor();

	int ret_num = 0;		// ret num of Keyboard_Control
	while (1) {
		Plane plane;

		Game_Cover();
		Choose_Level(plane);
		Game_Begin();
		system("color 0f");
		Draw_Outline(plane.Get_Level());

		plane.Init_Plane();
		plane.Draw_Plane();
		Bullet *bullet = new Bullet[BULLET_MAX];
		Enemy *enemy = new Enemy[plane.Get_EnemyNum()];
		Enemy_Bullet *enemy_bullet = new Enemy_Bullet[plane.Get_EnemyNum()];

		while (1) {
			ret_num = Keyboard_Control(plane, bullet, enemy,enemy_bullet);
			if (ret_num == 1) {
				Set_Suspend();
				Press_Wait('p');
				Set_Continue();
			}
			else if (ret_num == 2) {
				system("cls");
				Game_Over(plane.Get_Score());
				Sleep(2000);
				break;
			}
		}

		if (ret_num == 2) {
			system("cls");
			continue;
		}
	}

	return 0;
}