#ifndef _TRAP_H_
#define _TRAP_H_
#include <iostream>
#include "my_head.h"
#include <vector>
// #include "cheese.h"
using namespace std;
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
};
//-------------------
// extern Cheese cheese;
//----------------
void LevelSelected(int level);//关卡选择与陷阱生成
#endif
