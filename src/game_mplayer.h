#ifndef _GAME_MPLAYER_H_
#define _GAME_MPLAYER_H_
#include<iostream>
#include"my_head.h"
#include"Custom_Exception.h"
#define FIFO_FILE_MUSIC "./fifo_music"
#define FIFO_FILE_SFX "./fifo_sfx"
#define MUSIC_FILE "./music/3.wav"
#define SFX_FILE "./sfx/eat.wav"
using namespace std;
void mplayer_init(int fd,char *FIFO_PATH);
void send_cmd_music(char *cmd);//音乐控制
void music_init();
void send_cmd_sfx(char *cmd);//音效控制
void sfx_init();
#endif