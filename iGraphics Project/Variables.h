#define ScH 900
#define ScW 1600

int menuPage;
int Instructions;
int aboutUs;
int levelbg;

int loadingGame;
int imDeadPic;

int imPos_y = ScH/2;
int imPos_x = 20;



int imLife = 300;
int imScore = 0;

int wlLife = 100;

char imScore_c[1000];
char imLife_c[1000];

bool loadPic = true;	

bool bgRotate = false;
bool imStatic = true;
bool imBlast = false;
bool imArcBlast = false;
//bool miniBot = true;
bool miniFly = true;
//int imLife = 10;
bool imStatus = true;

int count=0;

bool wlShow = true;

#define wl_X 1200// setting the position of x coordinate for whiplash
#define wl_Y 100// setting the position of y coordinate for whiplash

bool wlAttack = false;
        
bool wlAttack2 = false;

int lokiLife = 100;
bool standing=true;
bool attack=false;
bool attack1=false;

int background[2];
int background_x[] = {0,1600}, background_y[] = {0,0};