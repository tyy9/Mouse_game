#ifndef _MENU_H
#define _MENU_H
#include<iostream>
#include "device_global.h"
#include "lcd_jpeg.h"
#include"mouse.h"
#include"menu_func.h"
#include<pthread.h>
extern Mouse head;
extern Cheese cheese;
extern string sign;
extern pthread_cond_t Over_cond;
extern pthread_mutex_t Over_mutex;
int menu();
#endif