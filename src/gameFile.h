#include<iostream>
#include<fstream>
#include "my_head.h"
#include "Animal.h"
#include<cstring>
#include<string>
#include "item.h"
using namespace std;
extern Mouse head;
extern vector<Mouse *> mouse_v;
extern string sign;
void save();//存档
void load();//读档