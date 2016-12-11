#include "snake.h"

void print_bound() {

	endwin();
	initscr();
	int j;
	int i = 1;
	move(0, 0);
	j = COLS;
	while (j) {//위쪽  경계1
		addstr("*");
		j--;
	}
	j = COLS;
	move(1, 0);
	while (j) {//아래쪽 경계2
		addstr("*");
		j--;
	}
	while (i<LINES) {//왼 쪽, 오른쪽 경계
		move(i, 0);
		addstr("*");
		move(i, 1);
		addstr("*");
		move(i, COLS - 2);
		addstr("*");
		move(i, COLS - 1);
		addstr("*");
		i++;
	}
	j = COLS;
	move(LINES - 2, 0);
	while (j) {//아래쪽  경계1
		addstr("*");
		j--;
	}
	j = COLS;
	move(LINES - 1, 0);//아래쪽 경계2
	while (j) {
		addstr("*");
		j--;
	}
}
void print_menu() {
	char c;
	
	head.x_dir = 1;
	head.y_dir = 0;
	head.ttm = 5;
	head.ttg = 5;
	head.score = 0;

	initscr();
	print_bound();//boundary 출력 함수 호출

	move((LINES - 1) / 3 - 1, (COLS - 1) / 2.7);
	addstr("+---------------------------+");
	move((LINES - 1) / 3, (COLS - 1) / 2.7 + 10);
	standout();
	addstr("SNAKE GAME");
	standend();
	move((LINES - 1) / 3 + 1, (COLS - 1) / 2.7);
	addstr("+---------------------------+");
	move((LINES - 1) / 2, (COLS - 1) / 2.7);
	addstr("<PRESS 'S(s)' TO START>");
	move((LINES - 1) / 2 + 2, (COLS - 1) / 2.7);
	addstr("s,S:START");
	move((LINES - 1) / 2 + 3, (COLS - 1) / 2.7);
	addstr("q,Q:FINISH");
	refresh();

	c = getchar();
	while(1){
		if(c=='s'||c=='S'){print_rule();break;}
		else if(c=='q'||c=='Q'){endwin();exit(0);break;}
		else c=getchar();//s,S,q,Q가 아닌 값이 오면나올 때까지  다른 값을 받도록 함
	}
}

void print_rule()
{
	char c;
	initscr();
	print_bound();
	move((LINES - 1) / 3 - 1, (COLS - 1) / 2.7);
	addstr("+---------------------------+");
	move((LINES - 1) / 3, (COLS - 1) / 2.7 + 7);
	standout();
	addstr("SNAKE GAME RULE!");
	standend();
	move((LINES - 1) / 2, (COLS - 1) / 2.7);
	addstr("<PRESS ANY KEY TO START>");
	move((LINES - 1) / 2 + 2, (COLS - 1) / 2.7);
	addstr("->,<-:move");
	move((LINES - 1) / 2 + 3, (COLS - 1) / 2.7);
	addstr("q,Q  :quit");
	refresh();
	getchar();
	start_game();
}

void start_game()
{
	int i,j;
	char str[10];//score를 string으로 바꿔서 잠시 저장할 변수
	struct snake *temp; // malloc을 위한 변수

	temp = (struct snake*)malloc(sizeof(struct snake));
	p_snake = temp;//snake의 머리 위치 정하기
	p_snake->x_pos = 5;
	p_snake->y_pos = 5;
	temp = (struct snake*)malloc(sizeof(struct snake));
	temp->x_pos = 5;//snake의 꼬리 위치 정하기
	temp->y_pos = 5;
	p_snake->blink = temp;
	p_snake->flink = NULL;
	temp->flink = p_snake;
	temp->blink = NULL;
	last_tail = temp;
	temp = (struct snake*)malloc(sizeof(struct snake));
	temp->x_pos = 5;
	temp->y_pos = 5;
	temp->flink = last_tail;
	temp->blink = NULL;
	last_tail->blink = temp;
	last_tail = temp;

	
	i=COLS;
	j=LINES;
	initscr();
	clear();
	print_bound();
	/*
	for(i=2;i<4;i++){//time을 보여줄 테두리 출력
		move(i,COLS-20);
		addstr("*");
	}
	move(i,COLS-20);
	addstr("*****************");
	move(2, COLS-19);
	*/
	move(0,COLS-19);
	standout();
	addstr("score:");
	sprintf(str, "%d", head.score);
	addstr(str);//print score
	standend();
	make_token();
	mvaddch(p_snake->y_pos, p_snake->x_pos, HEAD);//snake의 머리 출력
	mvaddch(temp->y_pos, temp->x_pos, BODY);//snake의 몸 출력
	refresh();//화면에 출력

}
