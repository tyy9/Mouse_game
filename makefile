Target=game
Src=$(wildcard src/*.cpp)
MAIN_Src=bin/main.cpp
Include=-I./include
Lib=-L./lib
Lib_Object=-lfont -lpthread -lm -ljpeg
Std=-std=c++11
CC=arm-linux-g++
$(Target):$(Src) $(MAIN_Src) 
	$(CC) $(Src) $(MAIN_Src) -o $(Target) $(Include) ${Lib} $(Lib_Object) $(Std)
	
.PHONY:scp
scp:
	scp ${Target} root@192.168.63.170:/root/user/my_game

.PHONY:clean
clean:
	rm ${Target} 
	