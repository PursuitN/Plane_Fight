#pragma once
#include<iostream>
#include<string>
#include<windows.h>
#include<time.h>
#include<conio.h>
using namespace std;

void Set_Cursor(int x, int y);						//set cursor to (x,y)
void Hide_Cursor();									//hide the cursor
void Display_Cursor();								//display the cursor
int Rand_Num(int head, int tail);					//produce rand num
void Draw_Row(int x1, int x2, int y, char c);		//draw a row, from(x1,y)->(x2,y),with c
void Draw_Column(int x, int y1, int y2, char c);	//draw a column, from (x,y1)->(x,y2),with c
void Press_Wait(char press);						//waitfor press down the keboard "press"
void Game_Cover();									//the cover of the game
void Game_Begin();									//when enter the space,the game begin
void Draw_Outline(int level);						//draw the background of the game
void Set_Score(int score);							//set the cur scores
void Game_Over(int score);							//the cover of the game over
void Set_Suspend();									//set state to suspend
void Set_Continue();								//set state to suspend
void Set_Blood(int blood);							//set the cur blood