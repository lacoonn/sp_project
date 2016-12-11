#include "snake.h"
#include <time.h>

void make_token(void)
{
	int number=0;
	int x,y;
	srand(time(NULL));
	while(number<=5)
	{
		x=rand()%(COLS-4)+2;
		y=rand()%(LINES-4)+2;
		if(x>COLS-21 && y<5)//만약 token좌표가 점수표시 영역 안에 찍혔을 때
			continue;
		mvaddch(y,x,TOKEN);
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
