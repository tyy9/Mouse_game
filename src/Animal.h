#ifndef _ANIMAL_H_
#define _ANIMAL_H_
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
extern Mouse head;      // 鼠头
extern int PauseFlag;   // 暂停
extern int GameOverFlag;
//----------
 void *Mouse_autoMove(void *args);//老鼠自动行走
 void adjustMove(Mouse *head,int x,int y);//调整在移动时各节点的   
 void cleanMouse(Mouse *head);//老鼠在移动前的清除函数
 void GameOver(Mouse *head);//老鼠在撞墙后的处理函数
 void eatCheese(Mouse *head);//判断是否吃到奶酪
 int    hitBody(Mouse *head);//身体碰撞判断
//----------------------------------
class Cat
{
private:
    /* data */
    int x;
    int y;
public:
    Cat(/* args */int x=525,int y=425);
    ~Cat();
    void show();
    void setX(int x);
    void setY(int y);
    int getX();
    int getY();
    void show_lcd(int direct);
    void reset();
};
extern Cat cat;
extern pthread_cond_t Cat_Pause_cond;
extern pthread_mutex_t Cat_Pause_mutex;
void *CatMove(void *args);
void CatMove_adjust(int direct,Cat *cat);
#endif