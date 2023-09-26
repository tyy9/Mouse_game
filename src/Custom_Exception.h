#ifndef _CUSTOM_EXCEPTION_H_
#define _CUSTOM_EXCEPTION_H_
#include<iostream>
using namespace std;
class MouseOutRange:public exception 
{
private:
    /* data */
public:
    const char *what()const throw(){
        cout<<"老鼠越过边界异常"<<endl;
        return "exception";
    }
};
#endif