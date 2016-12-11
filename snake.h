#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <termios.h>
#include <curses.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>

#define BLANK ' '
#define HEAD '@'
#define BODY 'O'
#define TOKEN '#'

struct snake
{
	struct snake *flink; // 바로 앞의 snake 구조체 포인터를 가진다
	struct snake *blink; // 바로 뒤의 snake 구조체 포인터를 가진다
	int x_pos, y_pos; // snake 몸체의 x, y 위치 좌표
};

struct head
{
	int ttg, ttm, x_dir, y_dir, score; // x,y direction, timevalue, interval, game score
};

struct snake *p_snake;
struct head head;
struct snake *last_tail;
