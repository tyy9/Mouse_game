#ifndef _DEVICE_GLOBAL_H_
#define _DEVICE_GLOBAL_H_
#include<iostream>
#include"my_head.h"


int lcd_open();
void lcd_draw_point(int x, int y, unsigned int color);
int inittouch_device(int *fd);
int lcd_close(void);
#endif