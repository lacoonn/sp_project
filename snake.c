#include "snake.h"

void terminal_set();
void set_async();
int set_ticker(int);
void change_dir(int);
void move_snake(int);


int main()
{
	print_menu();
	terminal_set();
	set_async();
	signal(SIGIO, change_dir);
	signal(SIGALRM, move_snake);
	
	set_ticker(10);

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
			print_replay();//여기에 종료 함수 넣을 예정
		}
		else if((temp_ch = (int)inch()) == (int)TOKEN)
		{
			head.score += 100;
			add_tail();//여기에 꼬리 증가 함수 넣을 예정(새로 추가한 꼬리는 함수안에서 mvaddch해줘야함)
			make_token();
		}

		mvaddch(p_snake->y_pos, p_snake->x_pos, HEAD);
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

void terminal_set()
{
	struct termios ttystate;

	tcgetattr(0, &ttystate);
	ttystate.c_lflag &= ~ICANON; // nocanonical 모드로 변경합니다.
	ttystate.c_cc[VMIN] = 1;
	ttystate.c_lflag &= ~ECHO; // noecho 모드로 변경합니다.
	tcsetattr(0, TCSANOW, &ttystate);
}

void set_async()
{
	int fd_flags;
	
	fcntl(0, F_SETOWN, getpid());
	fd_flags = fcntl(0, F_GETFL);
	fcntl(0, F_SETFL, (fd_flags | O_ASYNC));
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
