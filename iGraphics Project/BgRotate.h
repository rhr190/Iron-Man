#include "stb_image.h"
#include"iGraphics.h"
#include "Variables.h"


void change_background()
{ for(int i=0;i<2;i++)
	{
		
		background_x[i] -= 1; //left slide
		if(background_x[i]+1600<0) //left slide out of frame
			background_x[i] = background_x[(i+1)%2]+1600-2; 
		
		
	}
		
}

void bgRotating(){
	if(bgRotate)
		for(int i=0;i<2;i++)
			iShowImage(background_x[i],0,1600,900,background[i]);
}