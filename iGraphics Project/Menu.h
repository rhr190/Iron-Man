struct buttonCordinates
{
	int x;
	int y;
}bCordinate[5];

 int mposx, mposy;
 char buttons[10][50] = {"New game 2.bmp" , "High Scores 2.bmp","Instructions 2.bmp", "About us 2.bmp", "Exit 2.bmp"};
 //char menupage[50] = "MenuBG.bmp";
 char level1[50] = "gp1.bmp";
 char level2[50] = "gp2.bmp";
 char level3[50] = "gp3.bmp";
 //int Instructions = iLoadImage("1.png");
 char HighScore[50] = "hs.bmp";
 //char Instructions[50] = "ins.bmp";
 
 char AboutUs[50] = "Yo.bmp";
 
 int gameState = -1;



 void applyButtons()
 {
	 if(gameState == -1)
	{
		for(int i=0; i<5 ; i++)
		{
			iShowBMP(bCordinate[i].x, bCordinate[i].y, buttons[i]);
		}
	}
 }
	/*else if(gameState == 0)
	{
		//iShowBMP(0, 0, level1);
	}
	else if(gameState == 1)
	{
		//iShowBMP(0, 0, HighScore);
	}

	/*else if(gameState == 4)
	{
		exit(0);
	}*/
	
	
	
	/*
	else if(gameState == 3)
	{
		iShowBMP(0, 0, AboutUs);
	}*/
	/*
	else if(gameState == 4)
	{
		iShowBMP(0, 0, level2);
	}
	else if(gameState == 5)
	{
		iShowBMP(0, 0, level3);
	}
 }*/