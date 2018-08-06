#include "snake.h"

/*******************************************************************
*
*游戏结束释放蛇
*******************************************************************/
void free_snake(body *head) {
	body *neck;
	neck = head;
	while(head) {
		//printf("\n%d,%d\n",head->x,head->y);
		free(neck);
		head = neck = head->next;
	}
}

/***********************************************************************************
*获取键盘按键,并带延时,获取到键盘输入时，立刻结束
×无形参,返回一个字符(代表方向)
*
**********************************************************************************/
char input(void) {
	char buf;
	FILE *fp = NULL;
	buf = 0;
	fp = popen("read -s -a array -t 0.5 -n 1; echo $array", "r");
	if(!fp) {
		perror("popen");
		exit(EXIT_FAILURE);
	}
	buf = getc(fp);
	pclose(fp);
	return buf;
}

/* *****************************************************************************
 * 蛇函数,一步一调用,输入:
 * 蛇头(body*  head),
 * 食物块(food),
 * 方向("a(A)","s(S)","w(W)","d(D)")
 * 返回新蛇头(body*)
 * ***************************************************************************/
body *snake(const int row, const int line, \
				body* head, block *food, const char ori) {
	block step,temp;
	body *neck=NULL;
	//计算下一步方向
	step.x = (head->x)-(head->next->x);
	step.y = (head->y)-(head->next->y);
	switch(ori) {
		case 'w':
		case 'W':
			if(step.x==0) {
				step.x=-1;
				step.y=0;
			}
			//printf("1");
			break;

		case 'd':
		case 'D':
			if(step.y==0) {
				step.x=0;
				step.y=1;
			}
			//printf("2");
			break;
		
		case 'a':
		case 'A':
			if(step.y==0) {
				step.x=0;
				step.y=-1;
			}
			//printf("3");
			break;

		case 's':
		case 'S':
			if(step.x==0) {
				step.x=1;
				step.y=0;
			}
			//printf("4");
			break;
		default:
			break;
	}
	step.x=step.x+head->x;
	step.y=step.y+head->y;
	if((step.x==food->x)&&(step.y==food->y)) {
		neck = (body*)malloc(sizeof(body));
		neck->x = head->x;
		neck->y = head->y;
		neck->next = head->next;
		head->x=step.x;
		head->y=step.y;
		head->next=neck;
		food->x = 0;
		neck = NULL;
		return head;
	}
	else if(head->x<=0||head->x>=row-1||head->y<=0||head->y>=line-1) {
		free_snake(head);
		return NULL;
	}
	else {
		neck=head->next;
		temp.x=head->x;
		temp.y=head->y;
		if((head->x==neck->x)&&(head->y==neck->y)) {
			free_snake(head);
			return NULL;
		}
		head->x=step.x;
		head->y=step.y;
		while(neck) {
			if((head->x==neck->x)&&(head->y==neck->y)) {
				free_snake(head);
				return NULL;
			}
			step.x=neck->x;
			step.y=neck->y;
			neck->x=temp.x;
			neck->y=temp.y;
			temp.x=step.x;
			temp.y=step.y;
			neck=neck->next;
		}
	}
	return head;
}

/*********************************************************************************
*显示函数,刷新界面
*形参,界面行和列,蛇链表,食物块
×无返回值
*纠结于采用全判断输出,还是采用二维数组存储后一次性输出,前一种输出慢,节省内存,后一种运行快,耗费内存
*********************************************************************************/
void show(const int row, const int line, body* const head, const block food) {
	int i,j;
	char win[row][line];
	memset(win, 0, sizeof(win));
	i = j = 0;
	body *sk = head;
	win[sk->x][sk->y] = 'O';
	sk = sk->next;
	while(sk) {
		win[sk->x][sk->y] = 'X';
		sk = sk->next;
	}
	win[food.x][food.y] = '@';
	for(i=0; i<row; i++) {
		for(j=0; j<line; j++) {
			if(i==0||j==0||i==row-1||j==line-1)
				printf("#");
			else if(win[i][j])
				printf("%c", win[i][j]);
			else
				printf(" ");
		}
		printf("\n");
	}
}

/********************************************************************
*
*随机食物函数,不能产生到边界上,而且不能产生在蛇身上
********************************************************************/
void randfood(block* food,body* const head,const int row,const int line) {
	body *neck=NULL;
	neck = head;
	srand(time(NULL));
	food->x = rand()%row;
	food->y = rand()%line;
	if(food->x == 0) food->x = 1;
	if(food->x == row-1) food->x = row-2;
	if(food->y == 0) food->y = 1;
	if(food->y == line-1) food->y = line-2;
	while(neck) {
		if(food->x==neck->x&&food->y==neck->y) {
			food->x = rand()%row;
			food->y = rand()%line;
			if(food->x == 0) food->x = 1;
			if(food->x == row-1) food->x = row-2;
			if(food->y == 0) food->y = 1;
			if(food->y == line-1) food->y = line-2;
			neck=head;
		}
		else
			neck=neck->next;
	}
}


