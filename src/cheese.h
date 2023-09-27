#ifndef _CHEESE_H_
#define _CHEESE_H_
#include<iostream>
#include"my_head.h"
#include"lcd_jpeg.h"
using namespace std;

extern string sign;
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
    ~Cheese();
};

#endif