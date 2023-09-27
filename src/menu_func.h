#ifndef _MENU_FUNC_H_
#define _MENU_FUNC_H_
#include <iostream>
#include "mouse.h"
#include "lcd_jpeg.h"
#include <pthread.h>
using namespace std;

extern string sign;
extern Mouse head;
extern int GameOverFlag;
extern int ResetFlag;
extern int DestroyFlag;
extern pthread_cond_t Over_cond;
extern pthread_mutex_t Over_mutex;
extern pthread_cond_t Pause_cond;
extern pthread_mutex_t Pause_mutex;
extern int speed;
extern int PauseFlag;
//---------
void Button_Direct(int x, int y); // 方向键判断
int EndMenu(int x, int y);       // 游戏结束菜单选择
int GameMenu(int x,int y);//游戏菜单选择
void initdata();//初始化数据
#endif