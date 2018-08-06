#ifndef SNAKE_H_
#define SNAKE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

typedef struct body {
	char x;
	char y;
	struct body * next;
}body;

typedef struct block {
	char x;
	char y;
}block;

void free_snake(body *head);

char input(void);

body *snake(const int row, const int line, \
				body* head, block *food, const char ori);

void show(const int row, const int line, body* const head, const block food);

void randfood(block* food,body* const head,const int row,const int line);
		
#endif /*snake.h*/

