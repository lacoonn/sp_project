#include "snake.h"

//void terminal_set(int);
//void set_async(int);
//int set_ticker(int);
//void change_dir(int);
//void move_snake(int);


int main()
{
	print_menu();
	//terminal_set();
	//set_async();
	//signal(SIGIO, change_dir);
	//signal(SIGALRM, move_snake);
	
	//set_ticker(10);

	while (1) {}

	return 0;
}

void change_dir(int signum)
{
	int c = getchar();

	if(c == '\033') // catch arrow key input
	{
		c = getchar();
		c = getchar();
		if(c == 67 && head.x_dir != -1) // 오른쪽 화살표이면 x 방향을 1로 한다.
		{
			head.x_dir = 1;
			head.y_dir = 0;
			head.ttg = 0;
		}
		else if(c == 68 && head.x_dir != 1) // 왼쪽 화살표이면 x 방향을 -1로 한다.
		{
			head.x_dir = -1;
			head.y_dir = 0;
			head.ttg = 0;
		}
		else if(c == 65 && head.y_dir != 1) // 위쪽 화살표이면 y 방향을 -1로 한다.
		{
			head.x_dir = 0;
			head.y_dir = -1;
			head.ttg = 0;
		}
		else if(c == 66 && head.y_dir != -1) // 아래쪽 화살표이면 y 방향을 1로 한다.
		{
			head.x_dir = 0;
			head.y_dir = 1;
			head.ttg = 0;
		}
	}
	else if(c == 'q' || c == 'Q')
	{
		endwin();
		exit(0);
	}
}

void move_snake(int signum)
{
	int temp_ch; // 임시로 다음 위치의 문자를 가져오는 변수
	char str[10];//score 변수를 string으로 바꿔서 저장할 변수
	

	signal(SIGALRM, SIG_IGN);
	signal(SIGIO, SIG_IGN);
	if(head.ttg-- == 0)
	{
		head.ttg = head.ttm;
		while(p_snake->blink != NULL)
		{
			mvaddch(p_snake->y_pos, p_snake->x_pos,BLANK);
			p_snake = p_snake->blink;
		}
		mvaddch(p_snake->y_pos, p_snake->x_pos, BLANK);
		last_tail = p_snake;
		while(p_snake->flink != NULL)
		{
			p_snake->x_pos = p_snake->flink->x_pos;
			p_snake->y_pos = p_snake->flink->y_pos;

			mvaddch(p_snake->y_pos, p_snake->x_pos, BODY);

			p_snake = p_snake->flink;
		}
		p_snake->x_pos += head.x_dir;
		p_snake->y_pos += head.y_dir;

		move(p_snake->y_pos, p_snake->x_pos);
		if((temp_ch = (int)inch()) == (int)'*' || (temp_ch == (int)BODY)) // 충돌을 판정하는 부분
		{
			clear();
			free_snake();
			terminal_set(1);
			set_async(1);
			signal(SIGIO, 0);
			set_ticker(0);
			signal(SIGALRM, 0);
			print_replay();
		}
		else if((temp_ch = (int)inch()) == (int)TOKEN)//when snake eat token
		{
			head.score += 100;
			add_tail();
			make_token();
		}

		mvaddch(p_snake->y_pos, p_snake->x_pos, HEAD);
		mvaddch(token.y, token.x, TOKEN);
		standout();
		sprintf(str, "%d", head.score);
		mvaddstr(0, COLS-13, str);
		standend();
		move(0, 0);
		

		refresh();
	}

	signal(SIGALRM, move_snake);
	signal(SIGIO, change_dir);

}

void free_snake()
{
	struct snake *temp;

	while(p_snake != NULL)
	{
		temp = p_snake;
		p_snake = p_snake->blink;
		free(temp);
	}
}

void terminal_set(int i)
{
	struct termios ttystate;
	static struct termios prestate;
	
	if(i == 0)
	{
	tcgetattr(0, &ttystate);
	prestate = ttystate;
	ttystate.c_lflag &= ~ICANON; // nocanonical 모드로 변경합니다.
	ttystate.c_cc[VMIN] = 1;
	ttystate.c_lflag &= ~ECHO; // noecho 모드로 변경합니다.
	tcsetattr(0, TCSANOW, &ttystate);
	}
	else if(i == 1)
	{
		tcsetattr(0, TCSANOW, &prestate);
	}
}

void set_async(int i)
{
	int fd_flags;
	static int pre_flags;

	if(i == 0)
	{
		fcntl(0, F_SETOWN, getpid());
		fd_flags = fcntl(0, F_GETFL);
		pre_flags = fd_flags;
		fcntl(0, F_SETFL, (fd_flags | O_ASYNC));
	}
	if(i == 1)
	{
		fcntl(0, F_SETOWN, 0);
		fcntl(0, F_SETFL, pre_flags);
	}
}
		
int set_ticker(int n_msecs)
{
	struct itimerval new_timeset;
	long n_sec, n_usecs;

	n_sec = n_msecs / 1000;
	n_usecs = (n_msecs % 1000) * 1000L;
	new_timeset.it_interval.tv_sec = n_sec;
	new_timeset.it_interval.tv_usec = n_usecs;
	new_timeset.it_value.tv_sec = n_sec;
	new_timeset.it_value.tv_usec = n_usecs;


	return setitimer(ITIMER_REAL, &new_timeset, NULL);
}
