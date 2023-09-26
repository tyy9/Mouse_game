#ifndef _LCD_JPEG_H_
#define  _LCD_JPEG_H_
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>
#include "../include/jpeglib.h"
#include "device_global.h"
extern int fd_lcd;
extern int *pb;
extern int fd;
extern int fd_touch;
int lcd_draw_point_jpeg(int x, int y, unsigned int color);

int lcd_draw_img_jpeg(int x, int y, const char *pjpg_path);

int lcd_draw_img_jpeg_chat(int x, int y, const char *pjpg_path);

#endif