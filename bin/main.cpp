#include<iostream>
#include"../src/device_global.h"
#include"../src/menu.h"
#include"../src/mouse.h"

using namespace std;
int main(){
    lcd_open();
    inittouch_device(&fd_touch);
    menu();
    lcd_close();
}   