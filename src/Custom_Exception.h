#ifndef _CUSTOM_EXCEPTION_H_
#define _CUSTOM_EXCEPTION_H_
#include<iostream>
using namespace std;
class CustomException:public exception 
{
private:
    /* data */
public:
    const char *what()const throw(){
        cout<<"自定义异常"<<endl;
        return "exception";
    }
};
#endif