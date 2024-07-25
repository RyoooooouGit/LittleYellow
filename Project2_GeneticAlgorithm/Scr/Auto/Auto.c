#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int a[12][12], score = 0, i0 = 1, j0 = 1;
int randomInt(int x, int y) {
	int t = rand() % (y - x + 1) + x;
	return t;
}
void createMap() {
	int i, j;
	for (i = 0; i < 12; i++) {
		a[i][0] = 2;
		a[i][11] = 2;
		a[0][i] = 2;
		a[11][i] = 2;
	}
	for (i = 1; i <= 10; i++) {
		for (j = 1; j <= 10; j++) {
			a[i][j] = randomInt(0, 1);
		}
	}
	a[i0][j0] += 10;
}
void printMap(void) {
	int i, j;
	printf("score=%d\n", score);
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
	}
	a[i0][j0] += 10;
}
void movedown(void) {
	a[i0][j0] -= 10;
	i0 += 1;
	if (a[i0][j0] == 2) {
		i0 -= 1;
		score -= 5;
	}
	a[i0][j0] += 10;
}
void moveleft(void) {
	a[i0][j0] -= 10;
	j0 -= 1;
	if (a[i0][j0] == 2) {
		j0 += 1;
		score -= 5;
	}
	a[i0][j0] += 10;
}
void moveright(void) {
	a[i0][j0] -= 10;
	j0 += 1;
	if (a[i0][j0] == 2) {
		j0 -= 1;
		score -= 5;
	}
	a[i0][j0] += 10;
}
void dontmove(void) {
	;
}
void pick(void) {
	a[i0][j0] -= 1;
	if (a[i0][j0] < 10) {
		score -= 2;
		a[i0][j0] += 1;
	}
	else score += 10;
}
void action(int n) {
	switch (n) {
	case 0:action(randomInt(1, 6)); break;
	case 1:moveleft(); break;
	case 2:movedown(); break;
	case 3:moveright(); break;
	case 4:dontmove(); break;
	case 5:moveup(); break;
	case 6:pick(); break;
	}
	printMap();
}
int main() {
	srand(time(0));
	int i, select;
	int strategy[243];
	createMap();
	printMap();
	FILE* fp = fopen("..\\..\\strategy.txt", "r");
	for (i = 0; i < 243; i++)
	{
		fscanf(fp, "%1d", &strategy[i]);
	}
	for (i = 0; i < 200; i++) {
		system("cls");
		select = a[i0 - 1][j0] * 81 + a[i0 + 1][j0] * 27 + a[i0][j0 + 1] * 9 + a[i0][j0 - 1] * 3 + (a[i0][j0] - 10) ;
		action(strategy[select]);
	}
	//getchar();
	return 0;
}


// 当前问题
// 如何导入txt中数据				已解决
// 输出时(1,1)始终为"!"			已解决
// 输出的棋盘只能全为1或全为0		已解决
// 如何读取相对路径				已解决
// 按照最初的程序识别是否为墙较复杂	已解决
// exe文件放到要求位置后相对路径改变	已解决