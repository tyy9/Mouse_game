#ifndef _FONTSHOW_H_
#define _FONTSHOW_H_
#include <iostream>
#include "my_head.h"
#include "font.h"
using namespace std;
int Score_font_show_text(char *text, int b_length, int b_width,
                             int b_x, int b_y, int text_size, int text_x, int text_y);
int tip_font_show_text(char *text, int b_length, int b_width,
                             int b_x, int b_y, int text_size, int text_x, int text_y);
struct LcdDevice *init_lcd(const char *device);
#endif