#include "iGraphics.h"
#include "bitmap_loader.h"
#include "Menu.h"
#include "myheader.h"
#include "Variables.h"
//#include "BgRotate.h"
//#include "Minions.h"
int m;

//Structure for minions
typedef struct minions minions;

struct minions{
	int mini_x;
	int mini_y;
	int mini_num;
	bool mini_show;
};minions enemy[10];

char mins[10][30]={"1.bmp", "2.bmp", "3.bmp", "4.bmp", "5.bmp"};

//Setting up the initial values for the structure variables
void initialize(){
	
	int x=20;
	int y=100;

		for(int i=0;i<5;i++)
		{
			if(!enemy[i].mini_show){
				enemy[i].mini_show=true;
				enemy[i].mini_x=1600+x;
				enemy[i].mini_y=120+y;
				y+=90;
				x+=60;
			}
		}
}

//Setting up the changed numbers for the minions to initialize
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

/*
char lokio[4][15]={"loki1.bmp","loki2.bmp","loki3.bmp","blast.bmp"};

void loki(){
	if(standing){
		iShowBMP2(850,150,lokio[0],0);
	}
	if(attack){
		iShowBMP2(800,150,lokio[1],0);
	}
	if(attack1){
		iShowBMP2(220,210,lokio[3],0);
		iShowBMP2(850,150,lokio[2],0);
	}
	
	
}*/

//This method controls Iron-Man's life states & also the collision logic in terms with minions
void showLife(){
	
	for(int i = 0; i<5; i++){
			if((imPos_y <= enemy[i].mini_y && imPos_y + 240 >= enemy[i].mini_y + 88) && imPos_x + 150 >= enemy[i].mini_x){
				enemy[i].mini_show=false;
				imLife -= 1;
				
			}
						
		}
}

void showLife2(){
	if(wlAttack == true && imPos_y <= 200 && imPos_y >= 100)
		imLife -= 10;
	if(attack == true && imPos_y <= 200 && imPos_y >= 100)
		imLife -= 10;

}


//This method deals with the movement of minibots or minions
void miniMovement()
{
	for(int i=0;i<5;i++)
	{
		enemy[i].mini_x-=25;
		if(enemy[i].mini_x<=0)
		{
			enemy[i].mini_x=1600+rand()%200;
		}
		enemy[i].mini_num++;
		if(enemy[i].mini_num>=5)
		{
			enemy[i].mini_num=0;
		}
	}
	
}


//This method visualizes the minions/minibots. This method also calls miniMovement function to regenarate the minions again, using iSetTimer function
void miniShow(){
	if(miniFly)
		for(int i=0;i<5;i++)
		{

			if(enemy[i].mini_show)
			{
				iShowBMP2(enemy[i].mini_x,enemy[i].mini_y,mins[enemy[i].mini_num],0);
			}
			
		}
		iSetTimer(150, miniMovement);
		
}

//This method stops the loading picture and initializes level1
void state1(){
	loadPic = false;
	bgRotate = true;
	imStatic = true;
	miniFly = true;
	imStatus = true;
}	 

//This method shows the loading game image before starting the game and also calls state1 function after 6 seconds
void loading_Game(){
	
	iSetTimer(6000, state1);
	
	if(loadPic){
		iShowImage(0, 0, 1600, 900, loadingGame);
	
		imStatic = false;
		imBlast = false;
		bgRotate = false;
		miniFly = false;
		imStatus = false;
	}
	
}

//Changes the background
void change_background(){
	
	if(bgRotate){
	for(int i=0;i<2;i++)
	{
		background_x[i] -= 1; //left slide
		if(background_x[i]+1600<0) //left slide out of frame
			background_x[i] = background_x[(i+1)%2]+1600-2; 
	}
	}
		
}

//Rotates the background
void bgRotating(){
	if(bgRotate)
		for(int i=0;i<2;i++)
			iShowImage(background_x[i],0,1600,900,background[i]);
}

//Initializes Iron-Man's normal position
void imStatic2(){
	imStatic = true;
}
//Uninitializes Iron-Man's blast position
void imBlast2(){
	imBlast = false;
}
//Uninitializes Iron-Man's Arc-blast position
void imArcBlast2(){
	imArcBlast = false;
}

//This method is Iron-Mans whole appearance in the game-play. Also shows Iron-Man's life status and points 
void imEntrance(){
	
	if(imStatic){
		iShowBMP2(imPos_x, imPos_y, "1e.bmp", 0);	
	}
	
	if(imBlast){
		iShowBMP2(imPos_x, imPos_y, "1d.bmp", 0);
		iShowBMP2(imPos_x + 240, imPos_y + 157, "1o.bmp",0);
	}
	
	if(imArcBlast){
		iShowBMP2(imPos_x, imPos_y, "1i.bmp", 0);
		iShowBMP2(imPos_x + 91, imPos_y + 179-12, "blast2.bmp",0);
	}

	iSetTimer(400, imStatic2);
	iSetTimer(400, imArcBlast2);
	iSetTimer(400, imBlast2);
	

	if(imStatus){
		iText(700, 800, imScore_c, GLUT_BITMAP_TIMES_ROMAN_24);
		iText(40, 800, imLife_c, GLUT_BITMAP_TIMES_ROMAN_24);
		sprintf(imLife_c,"Life: %d", imLife);
		sprintf(imScore_c,"Score: %d", imScore);
	}
}

//Sets all variables to false and returns to gameState 5
void imDead(){
	if(imLife == 0){
		//iSetTimer(5000, genDeadPic);
		iDelay(3);
		loadPic = false;
		imStatic = false;
		imBlast = false;
		bgRotate = false;
		miniFly = false;
		imStatus = false;
		
		gameState = 5;
		
	}
}

//Whiplash images
char whipImage[3][50]={"whiplash.bmp", "whiplash attack 1.bmp", "whiplash attacking.bmp"}; 

//Brings back Whiplashes initial position
void back(){
	wlShow = true;
	wlAttack = false;
}

//Whiplash attacking mode
void whipState() // will be called from the iDraw() method
{
	wlShow = false;
	wlAttack = true;
	
} 

//Shows whiplash in the gameplay
void whipShow1(){
	if(wlShow) 
		iShowBMP2(1200, 100, whipImage[0], 0);
	if(wlAttack)
		iShowBMP2(100, 100, whipImage[2], 0);
	iSetTimer(1000, whipState);
	//iSetTimer(1000, back);
	
}

//This function deals when Whiplash is dead. Goes to gameState 7
void whipDead(){
	if(wlLife == 0)
		iDelay(2);
		gameState = 7;
}

//This method initializes Loki in the gamePlay
void initializeLoki(){
	if(gameState == 7){
		if(standing && !attack){
			standing=true;
			attack=false;
			attack1=false;
		
		}
		else if(standing && !attack){
			standing=false;
			attack=true;
			attack1=false;
		}
		else if(!standing && !attack1){
			standing=false;
			attack=false;
			attack1=true;
		}
	}
}

char lokio[4][15]={"loki1.bmp","loki2.bmp","loki3.bmp","blast.bmp"};

//Shows Loki's images at various states
void Loki(){
	if(standing){
		iShowBMP2(850,150,lokio[0],0);
	}
	if(attack){
		iShowBMP2(800,150,lokio[1],0);
	}
	if(attack1){
		iShowBMP2(850,210,lokio[3],0);
		iShowBMP2(850,150,lokio[2],0);
	}
	iSetTimer(3000, initializeLoki);
	
}

//Deals when Loki is dead. Returns to the main menu.
void lokiDead(){
	if(lokiLife == 0)
		iDelay(2);
		gameState = -1;
}

//changes the level when minibots are defeated
void levelChange(){
	//if(imScore >= 300)
		gameState = 7;
	
}



void iDraw()
{
	iClear();
	//iPauseTimer();
	if(gameState == -1)
	{
		iShowImage(0, 0, 1600, 900, menuPage);
		applyButtons();
	}
	
	if(gameState == 2)
		
		iShowImage(0, 0, 1600, 900, Instructions);
	
	if(gameState == 3)
		
		iShowImage(0, 0, 1600, 900, aboutUs);
	
	if(gameState == 4)
	
		exit(0);
	
	if(gameState == 5){
		
		iShowImage(0, 0, 1600, 900, imDeadPic);
		//iText(600, 400, "%s");
		imLife = 300;
		imScore = 0;
		
		
	}

	if(gameState == 0){
		
		imDead();
		loading_Game();
		//bgRotate = true;
		bgRotating();
	    imEntrance();
		miniShow();
		showLife();

		
	}
	if(gameState == 6){
		
		iPauseTimer(m);
		bgRotate = false;
		iShowImage(0, 0, 1600, 900, levelbg);
		imEntrance();
		showLife2();
		
		//whipShow2();
		//iSetTimer(1000, back);
		//iSetTimer(3000, whipState);
		//whipDead();
		whipShow1();
		//iSetTimer(1000, back);
		//iSetTimer(3000, whipState);
		//back();
	}

	if(gameState == 7){
		//bgRotate = true;
		//bgRotating();
		bgRotate = false;
		iShowImage(0, 0, 1600, 900, levelbg);
	    imEntrance();
		
		showLife2();	
		Loki();
		//lokiDead();
	}
}



void iPassiveMouse(int mx, int my)
{
	mposx = mx;
	mposy = my;

/*	if(mposx >= 67 && mposx <= 329  && mposy >= 178 && mposy <= 245)
			iShowBMP2(67, 178, "border.bmp", 0);
	if(mposx >= 67 && mposx <= 329  && mposy >= 285 && mposy <= 355)
			iShowBMP2(67, 285, "border.bmp", 0);
	if(mposx >= 67 && mposx <= 329  && mposy >= 395 && mposy <= 465)
			iShowBMP2(67, 395, "border.bmp", 0);
	if(mposx >= 67 && mposx <= 329  && mposy >= 505 && mposy <= 575)
			iShowBMP2(67, 505, "border.bmp", 0);
	if(mposx >= 67 && mposx <= 329  && mposy >= 615 && mposy <= 685)
			iShowBMP2(67, 615, "border.bmp", 0);*/
}


/*
 function iMouseMove() is called when the user presses and drags the mouse.
 (mx, my) is the position where the mouse pointer is.
 */
void iMouseMove(int mx, int my)
{
	mposx = mx;
	mposy = my;
}

/*
 function iMouse() is called when the user presses/releases the mouse.
 (mx, my) is the position where the mouse pointer is.
 */


void iMouse(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if(mx >= 67 && mx <= 329  && my >= 178 && my <= 245)
			gameState = 4;
		if(mx >= 67 && mx <= 329  && my >= 285 && my <= 355)
			gameState = 3;
		if(mx >= 67 && mx <= 329  && my >= 395 && my <= 465)
			gameState = 2;
		if(mx >= 67 && mx <= 329  && my >= 505 && my <= 575)
			gameState = 1;
		if(mx >= 67 && mx <= 329  && my >= 615 && my <= 685){
			gameState = 0;
			//
			iSetTimer(3000, imEntrance);
			iSetTimer(5000,initialize);
			
			loading_Game();
			setVariables();
			//iSetTimer(30000, levelChange);
		}
	
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		
	}
}

/*
 function iKeyboard() is called whenever the user hits a key in keyboard.
 key- holds the ASCII value of the key pressed.
 */
void iKeyboard(unsigned char key)
{
	if (key == 'q')
	{
		exit(0);
	}

	//place your codes for other keys here
	if ( key == '\b'){
		gameState = -1;
		imLife = 300;
		imScore = 0;
	}

	if ( key == 's'){
		imStatic = false;
		imBlast = true;
		//imArcBlast = false;
		

		if(((imPos_y + 140 >= enemy[0].mini_y && imPos_y + 140 <= enemy[0].mini_y+88) || (imPos_y + 172 >= enemy[0].mini_y && imPos_y + 172 <= enemy[0].mini_y+88)) && (imPos_x + 1440 >= enemy[0].mini_x))
		{
			enemy[0].mini_show=false;
			imScore += 10;
		}
		
		if(((imPos_y + 140 >= enemy[1].mini_y && imPos_y + 140 <= enemy[1].mini_y+88) || (imPos_y + 172 >= enemy[1].mini_y && imPos_y + 172 <= enemy[1].mini_y+88)) && (imPos_x + 1440 >= enemy[1].mini_x))
		{
			enemy[1].mini_show=false;
			imScore += 10;
		}
		
		if(((imPos_y + 140 >= enemy[2].mini_y && imPos_y + 140 <= enemy[2].mini_y+88) || (imPos_y + 172 >= enemy[2].mini_y && imPos_y + 172 <= enemy[2].mini_y+88)) && (imPos_x + 1440 >= enemy[2].mini_x))
		{
			enemy[2].mini_show=false;
			imScore += 10;
		}
		
		if(((imPos_y + 140 >= enemy[3].mini_y && imPos_y + 140 <= enemy[3].mini_y+88) || (imPos_y + 172 >= enemy[3].mini_y && imPos_y + 172 <= enemy[3].mini_y+88)) && (imPos_x + 1440 >= enemy[3].mini_x))
		{
			enemy[3].mini_show=false;
			imScore += 10;
		}
		
		if(((imPos_y + 140 >= enemy[4].mini_y && imPos_y + 140 <= enemy[4].mini_y+88) || (imPos_y + 172 >= enemy[4].mini_y && imPos_y + 172 <= enemy[4].mini_y+88)) && (imPos_x + 1440 >= enemy[4].mini_x))
		{
			enemy[4].mini_show=false;
			imScore += 10;
		}
		
		
		if(((imPos_y + 140 >= wl_Y && imPos_y + 140 <= wl_Y+224) || (imPos_y + 172 >= wl_Y && imPos_y + 172 <= wl_Y+224)) && (imPos_x + 1200 >= wl_X))
		{
			
			wlLife -= 10;
			imScore += 10;
		}
		if(((imPos_y + 140 >= wl_Y && imPos_y + 140 <= wl_Y+224) || (imPos_y + 172 >= wl_Y && imPos_y + 172 <= wl_Y+224)) && (imPos_x + 1200 >= wl_X))
		{
			
			lokiLife -= 10;
			imScore += 10;
		}

	}

		//iSetTimer(5000,initialize);
		
		if ( key == 'd'){
		imStatic = false;
		//imBlast = false;
		imArcBlast = true;
		

		if(((imPos_y + 170 >= enemy[0].mini_y && imPos_y + 170 <= enemy[0].mini_y+88) || (imPos_y + 240 >= enemy[0].mini_y && imPos_y + 240 <= enemy[0].mini_y+88)) && (imPos_x + 1440 >= enemy[0].mini_x))
		{
			enemy[0].mini_show=false;
			imScore += 10;
		}
		
		if(((imPos_y + 170 >= enemy[1].mini_y && imPos_y + 170 <= enemy[1].mini_y+88) || (imPos_y + 240 >= enemy[1].mini_y && imPos_y + 240 <= enemy[1].mini_y+88)) && (imPos_x + 1440 >= enemy[1].mini_x))
		{
			enemy[1].mini_show=false;
			imScore += 10;
		}
		
		if(((imPos_y + 170 >= enemy[2].mini_y && imPos_y + 170 <= enemy[2].mini_y+88) || (imPos_y + 240 >= enemy[2].mini_y && imPos_y + 240 <= enemy[2].mini_y+88)) && (imPos_x + 1440 >= enemy[2].mini_x))
		{
			enemy[2].mini_show=false;
			imScore += 10;
		}
		
		if(((imPos_y + 170 >= enemy[3].mini_y && imPos_y + 170 <= enemy[3].mini_y+88) || (imPos_y + 240 >= enemy[3].mini_y && imPos_y + 240 <= enemy[3].mini_y+88)) && (imPos_x + 1440 >= enemy[3].mini_x))
		{
			enemy[3].mini_show=false;
			imScore += 10;
		}
		
		if(((imPos_y + 170 >= enemy[4].mini_y && imPos_y + 170 <= enemy[4].mini_y+88) || (imPos_y + 240 >= enemy[4].mini_y && imPos_y + 240 <= enemy[4].mini_y+88)) && (imPos_x + 1440 >= enemy[4].mini_x))
		{
			enemy[4].mini_show=false;
			imScore += 10;
		}
			
	}
}



/*
 function iSpecialKeyboard() is called whenver user hits special keys like-
 function keys, home, end, pg up, pg down, arraows etc. you have to use
 appropriate constants to detect them. A list is:
 GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
 GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
 GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
 GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
 */
void iSpecialKeyboard(unsigned char key)
{

	if (key == GLUT_KEY_END)//for exit
	{
		exit(0);
	}

	//place your codes for other keys here
	if (key == GLUT_KEY_UP){ 
		imPos_y += 10;
		if(imPos_y >= 500)
			imPos_y -= 10;
	}
	if (key == GLUT_KEY_DOWN){
		imPos_y -= 10;
		if(imPos_y <= 120)
			imPos_y += 10;
	}
}

int main()
{
	//place your own initialization codes here.

	
	int sum = 0.111*ScH;
	for(int i=4; i>=0; i--)
	{
		bCordinate[i].x = 0.04375*ScW;
		bCordinate[i].y = sum;
		sum += 0.1333*ScH;


	}

	int m = iSetTimer(150, miniMovement);
	
	iInitialize(ScW, ScH, "The Invincible Iron Man");
	Instructions = iLoadImage("1.png");
	aboutUs = iLoadImage("Credits.png");
	menuPage = iLoadImage("MenuBG.bmp");
	levelbg = iLoadImage("bg2.bmp");
	
	iSetTimer(2,change_background);
	dx = 5;
	dy = 7;

	pic_x = 0;
	pic_y = 0;
	
	loadingGame = iLoadImage("loadingGame.png");
	imDeadPic = iLoadImage("imDead2.png");

	background[0] = iLoadImage("bg2.bmp");
	background[1] = iLoadImage("bg2.bmp");
	
	
	
	
	
	//levelChange();
	
	//iSetTimer(2000, back);
	//iSetTimer(3000, whipState);
	
	iStart(); // it will start drawing
	

	return 0;
}

