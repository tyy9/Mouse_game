#ifndef _CAT_H_
#define _CAT_H_
#include<iostream>
#include"my_head.h"
#include "item.h"
using namespace std;
class Cat
{
private:
    /* data */
    int x;
    int y;
public:
    Cat(/* args */int x=525,int y=425);
    ~Cat();
    
};
extern Cat cat;
void CatMove();
#endif