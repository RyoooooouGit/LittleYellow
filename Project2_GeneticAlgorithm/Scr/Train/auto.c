#pragma once
int a[12][12], score, i0, j0;
int straParental[200][243], index[200], stra[200][243];
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
void action_(int n) {
	switch (n) {
	case 0:action_(randomInt(1, 6)); break;
	case 1: {
		moveleft();
		printMap();
		break;
	}
	case 2: {
		movedown();
		printMap();
		break;
	}
	case 3: {
		moveright();
		printMap();
		break;
	}
	case 4: {
		dontmove();
		printMap();
		break;
	}
	case 5: {moveup();
		printMap();
		break;
	}
	case 6: {
		pick();
		printMap();
		break;
	}
	}
}
void test(void) {
	score = 0;
	i0 = 1;
	j0 = 1;
	int i, select;
	int strategy[243];
	createMap();
	printMap();
	for (i = 0; i < 200; i++) {
		system("cls");
		select = a[i0 - 1][j0] * 81 + a[i0 + 1][j0] * 27 + a[i0][j0 + 1] * 9 + a[i0][j0 - 1] * 3 + (a[i0][j0] - 10);
		action_(stra[index[0]][select]);
	}
	getchar();
}