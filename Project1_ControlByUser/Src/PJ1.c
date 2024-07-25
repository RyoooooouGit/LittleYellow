#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
int a[12][12], score, i0 = 1, j0 = 1;
int flagmove = 0, flagpick = 0;
int randomInt(int x, int y) {
	int t = rand() % (y - x + 1) + x;
	return t;
}
void scoreOut(void) {
	if (flagmove == 1) {
		printf(" 你这家伙！撞墙啦！！！");
		flagmove = 0;
	}
	if (flagpick == 1) {
		printf(" 呃 没捡到罐子 (￢_￢)");
		flagpick = 0;
	}
	else if (flagpick == 2) {
		printf(" 捡到罐子加大分！！");
		flagpick = 0;
	}
	printf(" score=%d\n", score);
	printf("按键提示：1:左移 2:下移 3:右移 4:不移动 5:上移 6:捡罐子 0:随机行动 Enter:结束游戏\n");
}
void createMap() {
	int i, j;
	for (i = 0; i < 12; i++) {
		a[i][0] = 2;
		a[i][11] = 2;
		a[0][i] = 2;
		a[11][i] = 2;
	}
	for (i = 1; i < 11; i++) {
		for (j = 1; j < 11; j++) {
			a[i][j] = randomInt(0, 1);
		}
	}
	a[i0][j0] += 10;
}
void printMap(void) {
	int i, j;
	for (i = 0; i < 12; i++) {
		for (j = 0; j < 12; j++) {
			if (a[i][j] == 0) printf("  ");
			else if (a[i][j] == 1) printf("@ ");
			else if (a[i][j] == 2) printf("# ");
			else printf("! ");
		}
		printf("\n");
	}
}
void moveup(void) {
	a[i0][j0] -= 10;
	i0 -= 1;
	if (a[i0][j0] == 2) {
		i0 += 1;
		score -= 5;
		flagmove = 1;
	}
	a[i0][j0] += 10;
	printMap();
	printf("尝试上移");
	scoreOut();
}
void movedown(void) {
	a[i0][j0] -= 10;
	i0 += 1;
	if (a[i0][j0] == 2) {
		i0 -= 1;
		score -= 5;
		flagmove = 1;
	}
	a[i0][j0] += 10;
	printMap();
	printf("尝试下移"); 
	scoreOut();
}
void moveleft(void) {
	a[i0][j0] -= 10;
	j0 -= 1;
	if (a[i0][j0] == 2) {
		j0 += 1;
		score -= 5;
		flagmove = 1;
	}
	a[i0][j0] += 10;
	printMap();
	printf("尝试左移");
	scoreOut();
}
void moveright(void) {
	a[i0][j0] -= 10;
	j0 += 1;
	if (a[i0][j0] == 2) {
		j0 -= 1;
		score -= 5;
		flagmove = 1;
	}
	a[i0][j0] += 10;
	printMap();
	printf("尝试右移");
	scoreOut();
}
void dontmove(void) {
	printMap();
	printf("不移动");
	scoreOut();
}
void pick(void) {
	a[i0][j0] -= 1;
	if (a[i0][j0] < 10) {
		score -= 2;
		a[i0][j0] += 1;
		flagpick = 1;
	}
	else {
		score += 10;
		flagpick = 2;
	}
	printMap();
	printf("尝试捡罐子");
	scoreOut();
}
void action(int n) {
	switch (n) {
		case 48:printf("随机行动");
			action(randomInt(49, 54)); 
			break;
		case 49:moveleft(); break;
		case 50:movedown(); break;
		case 51:moveright(); break;
		case 52:dontmove(); break;
		case 53:moveup(); break;
		case 54:pick(); break;
		default:if (n != 13) printf("opps!'%c'是无效的输入\n", n);
	}
}
int main() {
	int input=0, i;
	srand(time(0));
	createMap();
	printMap();
	printf("初始状态");
	scoreOut();
	while (input != 13) {
		input =_getch();
		system("cls");
		action(input);
	}
	system("cls");
	printf("*******GAME OVER*******\n");
	printMap();
	printf("小黄的最终得分 score:%d", score);
	getchar();
	return 0;
}
