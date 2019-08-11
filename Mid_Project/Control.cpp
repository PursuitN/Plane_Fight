#include"Control.h"

//set cursor to (x,y)
void Set_Cursor(int x, int y) {
	COORD pos = { x,y };
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hand, pos);
}

//hide the cursor
void Hide_Cursor() {
	CONSOLE_CURSOR_INFO hide_info = { 1, 0 };	//1 is the depth and 0 means hide
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(hand, &hide_info);
}

//display the cursor
void Display_Cursor() {
	CONSOLE_CURSOR_INFO hide_info = { 1, 1 };	//1 is the depth and 0 means hide
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(hand, &hide_info);
}

//produce rand num
int Rand_Num(int head, int tail) {
	int res = rand() % (tail - head) + head;
	return res;
}

//draw a row, from(x1,y)->(x2,y),with c
void Draw_Row(int x1, int x2, int y, char c) {
	for (int i = x1; i <= x2; i++) {
		Set_Cursor(i, y);
		cout << c;
	}
}

//draw a column, from (x,y1)->(x,y2),with c
void Draw_Column(int x, int y1, int y2, char c) {
	for (int i = y1; i <= y2; i++) {
		Set_Cursor(x, i);
		cout << c;
	}
}

//waitfor press down the keboard "press"
void Press_Wait(char press) {
	while (1) {
		if (_kbhit()) {
			char input = _getch();
			if (input == press) {
				return;
			}
		}
	}
	return;
}

//the cover of the game
void Game_Cover() {
	// blackground->grey   font->white
	system("color 3f");
	char c = '*';
	//Plane
	Draw_Column(15, 5, 14, c);
	Draw_Column(22, 5, 9, c);
	Draw_Row(16, 21, 5, c);
	Draw_Row(16, 21, 9, c);
	//l
	Draw_Column(26, 5, 14, c);
	//a
	Draw_Row(30, 36, 10, c);
	Draw_Row(30, 36, 14, c);
	Draw_Column(30, 10, 14, c);
	Draw_Column(36, 10, 14, c);
	//n
	Draw_Column(40, 10, 14, c);
	Draw_Column(46, 10, 14, c);
	Draw_Row(40, 46, 10, c);
	//e
	Draw_Row(50, 56, 10, c);
	Draw_Row(50, 56, 12, c);
	Draw_Row(50, 56, 14, c);
	Draw_Column(50, 10, 14, c);
	Draw_Column(56, 10, 12, c);
	//plane fight 
	Set_Cursor(62, 13);
	cout << "飞机大战";
	Set_Cursor(62, 14);
	cout << "南林林";
	//guide
	Set_Cursor(15, 17);
	cout << "操作：wasd ↑←↓→";
	Set_Cursor(15, 18);
	cout << "攻击：空格 发射子弹";
	Set_Cursor(15, 19);
	cout << "暂停：p(pause)";
	Set_Cursor(15, 20);
	cout << "退出：q(quit)";
	//choose level
	Set_Cursor(15, 22);
	cout << "请输入难度(非法输入默认为0)：";
	Set_Cursor(15, 23);
	cout << "0.简单：少敌人，慢速度";
	Set_Cursor(15, 24);
	cout << "1.困难：多敌人，快速度";
	//to begin
	Set_Cursor(15, 27);
	cout << "开始：请按b(begin)开始游戏";
}

//when enter the space,the game begin
void Game_Begin() {
	//wait for space
	char press = 'b';
	Press_Wait(press);
	//clean the screen
	system("cls");
}

//draw the background of the game
void Draw_Outline(int level) {
	//outline
	char r = '=';
	char c = '|';
	Draw_Column(0, 0, 29, c);
	Draw_Column(89, 0, 29, c);
	Draw_Column(117, 0, 29, c);
	Draw_Row(0, 117, 0, r);
	Draw_Row(0, 117, 29, r);
	//info
	Set_Cursor(99, 4);
	cout << "飞机大战";
	Set_Cursor(94, 8);
	cout << "操作：wasd ↑←↓→";
	Set_Cursor(94, 9);
	cout << "攻击：空格 发射子弹";
	Set_Cursor(94, 10);
	cout << "暂停：p(pause)";
	Set_Cursor(94, 11);
	cout << "退出：q(quit)";
	//state
	Set_Cursor(94, 16);
	cout << "当前状态：正在游戏";
	Set_Cursor(94, 18);
	cout << "当前血量：5";
	Set_Cursor(94, 20);
	cout << "当前得分：0";
	if (level == 0) {
		Set_Cursor(94, 22);
		cout << "当前模式：简单";
	}
	else {
		Set_Cursor(94, 22);
		cout << "当前模式：困难";
	}
}

//set the cur scores
void Set_Score(int score) {
	Set_Cursor(104, 20);
	cout << " ";
	Set_Cursor(105, 20);
	cout << " ";
	Set_Cursor(106, 20);
	cout << " ";
	Set_Cursor(104, 20);
	cout << score;
}

//the cover of the game over
void Game_Over(int score) {
	char c = '*';
	//GAME
	Draw_Column(15, 5, 13, c);
	Draw_Column(26, 9, 13, c);
	Draw_Column(29, 5, 13, c);
	Draw_Column(39, 5, 13, c);
	Draw_Column(43, 5, 13, c);
	Draw_Column(48, 5, 13, c);
	Draw_Column(53, 5, 13, c);
	Draw_Column(56, 5, 13, c);
	Draw_Row(15, 26, 5, c);
	Draw_Row(29, 39, 5, c);
	Draw_Row(43, 53, 5, c);
	Draw_Row(56, 66, 5, c);
	Draw_Row(21, 26, 9, c);
	Draw_Row(29, 39, 9, c);
	Draw_Row(56, 66, 9, c);
	Draw_Row(15, 26, 13, c);
	Draw_Row(56, 66, 13, c);
	//over
	Set_Cursor(70, 13);
	cout << "over ...";
	//score
	Set_Cursor(15, 16);
	cout << "最终得分：" << score;
}

//set state to suspend
void Set_Suspend() {
	for (int i = 104; i < 114; i++) {
		Set_Cursor(i, 16);
		cout << " ";
	}
	Set_Cursor(104, 16);
	cout << "暂停中(p继续)";
}

//set state to suspend
void Set_Continue() {
	for (int i = 104; i < 117; i++) {
		Set_Cursor(i, 16);
		cout << " ";
	}
	Set_Cursor(104, 16);
	cout << "正在游戏";
}

//set the cur blood
void Set_Blood(int blood) {
	Set_Cursor(104, 18);
	cout << " ";
	Set_Cursor(105, 18);
	cout << " ";
	Set_Cursor(106, 18);
	cout << " ";
	Set_Cursor(104, 18);
	cout << blood;
}