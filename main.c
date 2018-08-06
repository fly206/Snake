#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "snake.h"
#define row 21
#define line 61

int main() {
	block food;
	int score = -10;
	//初始一节蛇头一节蛇身
	body *by = NULL;
	body *head = NULL;
	head = (body*)malloc(sizeof(body));
	by = (body*)malloc(sizeof(body));
	//初始化蛇及食物
	head->x = (int)(row/2);
	head->y = (int)(line/2);
	head->next = by;
	by->x = (int)(row/2);
	by->y = (int)(line/2+1);
	by->next = NULL;
	food.x = 0;
	//判断条件当蛇头销毁时,游戏结束,并计算分数
	while(head) {
		system("clear");
		if(food.x == 0) {
			randfood(&food, head, row,line);
			score += 10;		//分数,一个食物10分
			if(score == 3000) {
				free_snake(head);
				printf("游戏结束,恭喜,您的分数为3000\n");
			}
		}
		show(row, line, head, food);
		head = snake(row, line, head, &food, input());
		//printf("测试%c\n",input());
		sleep(0);
	}
	//printf("%d,%d\n",food.x,food.y);
	printf("游戏结束,您的分数为%d.\n",score);
	return 0;
}

