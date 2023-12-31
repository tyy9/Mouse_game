#ifndef _MOUSE_H_
#define _MOUSE_H_
#include <iostream>
// #include"cheese.h"
#include "lcd_jpeg.h"
#include<memory>
#include<vector>
#include"my_head.h"
#include"fontshow.h"
#include "game_mplayer.h"
// #include "trap.h"
#include "item.h"

using namespace std;
//extern Cheese cheese;
extern int game_level;
//------------------------------
//------------------------------
class Mouse
{
private:
    /* data */
    int x;
    int y;
    int score;
    // 采用双向链表的形式链接
    Mouse *next; // 下一个老鼠
    Mouse *prev; // 上一个老鼠
public:
    Mouse(/* args */ int x = 50, int y = 45,int score=0);
    void MouseTailAdd(Mouse *other);
    void MouseReset();//数据重置  
    void MouseDestroy();//数据销毁  
    void operator+(string sign);
    void show();
    void setX(int x);
    void setY(int y);
    void setScore(int score);
    int getScore();
    int getX();
    int getY();
    Mouse *getNext();
    void setNext(Mouse *next);
    Mouse *getPrev();
    void setPrev(Mouse *prev);
    ~Mouse();
};

 void *Mouse_autoMove(void *args);//老鼠自动行走
 void adjustMove(Mouse *head,int x,int y);//调整在移动时各节点的   
 void cleanMouse(Mouse *head);//老鼠在移动前的清除函数
 void GameOver(Mouse *head);//老鼠在撞墙后的处理函数
 void eatCheese(Mouse *head);//判断是否吃到奶酪
 void hitBody(Mouse *head);//身体碰撞判断

#endif