#ifndef _ITEM_H_
#define _ITEM_H_
#include <iostream>
#include "my_head.h"
#include <vector>
#include"lcd_jpeg.h"
using namespace std;
class Cheese
{
private:
    /* data */
    int x;
    int y;
    int bonus;//双倍奖励,1||0
    int score;//分数
    int exsit;//是否被吃了
public:
    Cheese(/* args */int x=0,int y=0,int bouns=0,int score=10,int exsit=1);
    void CheeseCreate();
    void setX(int x);
    void setY(int y);
    void setBouns(int bouns);
    void setExsit(int exsit);
    int getX();
    int getY();
    int getBouns();
    int getExsit();
    int getscore();
    void show_lcd();
    ~Cheese();
};

class Trap
{
private:
    /* data */
    int x;
    int y;

public:
    Trap();
    ~Trap();
    void setX(int x);
    void setY(int y);
    int getX();
    int getY();
    void show_lcd();
};
//-------------------
extern Cheese cheese;
extern vector<Trap *> Trap_v;
extern int game_level;
//----------------
void LevelSelected(int level);//关卡选择与陷阱生成
void TrapCreate();
#endif