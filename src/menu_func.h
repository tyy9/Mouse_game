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
extern pthread_cond_t Over_cond;
extern pthread_mutex_t Over_mutex;

void Button_Direct(int x, int y); // 方向键判断
void EndMenu(int x, int y);       // 游戏结束菜单选择

#endif