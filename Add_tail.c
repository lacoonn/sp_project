//꼬리 추가 하는 함수
#include "snake.h"
#include <time.h>
void add_tail(void)
{
	int temp_ch,num=0,x,y;
	struct snake *temp;
	temp=(struct snake *)malloc(sizeof(struct snake));//새로운 꼬리 생성
	last_tail->blink=temp;//뱀의 마지막 꼬리에 새로운 꼬리 붙치기
	temp->flink=last_tail;//temp의 앞의 포인터를 last_tail(뱀꼬리)연결
	temp->blink=NULL;//꼬리 끝을 표시
	last_tail=temp;
	last_tail->x_pos=last_tail->flink->x_pos;
	last_tail->y_pos=last_tail->flink->y_pos;
	mvaddch(last_tail->y_pos,last_tail->x_pos,BODY);
}

