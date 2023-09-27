#ifndef _MOUSE_H_
#define _MOUSE_H_
#include <iostream>
#include "Custom_Exception.h"
#include"cheese.h"
#include "lcd_jpeg.h"
#include<memory>
#include<vector>
#include<memory>
using namespace std;


extern Cheese cheese;

//------------------------------
//------------------------------
class Mouse
{
private:
    /* data */
    int x;
    int y;
    int near_flag_row;    // 同一行中是否还有mouse对象,如果有那么移动后，后面的内存不用刷白
    int near_flag_column; // 同一列中是否还有mouse对象，如果有那么移动后，后面的内存不用刷白
    // 采用双向链表的形式链接
    Mouse *next; // 下一个老鼠
    Mouse *prev; // 上一个老鼠
public:
    Mouse(/* args */ int x = 50, int y = 45);
    void MouseTailAdd(Mouse *other);
    void MouseReset();//数据重置
    void operator+(string sign);
    void show();
    void setX(int x);
    void setY(int y);
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
#endif