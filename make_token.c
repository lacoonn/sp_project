#include "snake.h"
#include <time.h>

void make_token(void)
{
	int number=0;
	
	srand(time(NULL));
	while(number<=0)
	{
		token.x=rand()%(COLS-4)+2;
		token.y=rand()%(LINES-4)+2;
		mvaddch(token.y,token.x,TOKEN);
		number++;
	}
}
void make_one_token(void)
{
	int number=0;
	int x,y;
	srand(time(NULL));
	while(number==1)
	{
		x=rand()%(COLS-4)+2;
		y=rand()%(LINES-4)+2;
		if(x>COLS-21 && y<5)
			continue;
		mvaddch(y,x,TOKEN);
		number++;
	}
}
