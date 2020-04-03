#include "iGraphics.h"
#include "Variables.h"


typedef struct minions minions;

struct minions{
	int mini_x;
	int mini_y;
	int mini_num;
	bool mini_show;
};minions enemy[10];

char mins[10][30]={"1.bmp", "2.bmp", "3.bmp", "4.bmp", "5.bmp"};

void setVariables(){
	int x=20;
	int y=100;

	for(int i=0;i<5;i++)
	{
		 enemy[i].mini_x=1600+x;  
		 enemy[i].mini_y=120+y;
		 enemy[i].mini_num=rand()%5;
		 enemy[i].mini_show = true;
		 y+=90;
		 
		
	}
}