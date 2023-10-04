#include<iostream>
#include"../src/device_global.h"
#include"../src/menu.h"

using namespace std;
int main(){
    lcd_open();
    inittouch_device(&fd_touch);
    menu();
    lcd_close();
    cout<<"退出成功"<<endl;
    return 0;
}   