#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "auto.h"
int a[12][12], score, i0, j0;
int parent[20100];
const int MU = 400;
int straParental[200][243], stra[200][243], index[200];
float ascore[200];
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
}
float averageScore(int n) {
	int i, j, select, sum;
	sum = 0;
	for (i = 0; i < 100; i++) {
		createMap();
		score = 0;
		for (j = 0; j < 200; j++) {
			select = a[i0 - 1][j0] * 81 + a[i0 + 1][j0] * 27 + a[i0][j0 + 1] * 9 + a[i0][j0 - 1] * 3 + (a[i0][j0] - 10);
			action(stra[n][select]);
		}
		sum += score;
	}
	return (float)sum / 100;
}
void sort(void) {
	int i, j, k, t, flag = 1, temp;
	while (flag == 1) {
		for (i = 0; i < 200; i++) index[i] = i;
		for (i = 0; i < 200; i++) {
			k = i;
			flag = 0;
			for (j = i + 1; j < 200; j++) {
				if (ascore[index[k]] < ascore[index[j]]) k = j;
				if (ascore[index[j - 1]] < ascore[index[j]]) flag = 1;
			}
			if (k != i) {
				temp = index[k];
				for (t = k; t > i; t--) index[t] = index[t - 1];
				index[i] = temp;
			}
		}
	}
}
void breed(void) {
	int i, j, parent1, parent2;
	sort();
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 243; j++) {
			stra[i][j] = straParental[index[i]][j];
		}
	}
	for (i = 0; i < 95; i++) {
		parent1 = parent[randomInt(0, 20099)] - 1;
		parent2 = parent[randomInt(0, 20099)] - 1;
		for (j = 0; j < 243; j++) {
			if (0 <= (j % 120) && (j % 120) < 60) {
				if (randomInt(0, MU) != 0) stra[2 * i + 10][j] = straParental[index[parent1]][j];
				else stra[2*i+10][j] = randomInt(0, 6);
				if (randomInt(0, MU) != 0) stra[2 * i + 11][j] = straParental[index[parent2]][j];
				else stra[2*i+11][j] = randomInt(0, 6);
			}
			else {
				if (randomInt(0, MU) != 0) stra[2 * i + 10][j] = straParental[index[parent2]][j];
				else stra[2 * i + 10][j] = randomInt(0, 6);
				if (randomInt(0, MU) != 0) stra[2 * i + 11][j] = straParental[index[parent1]][j];
				else stra[2 * i + 10][j] = randomInt(0, 6);
			}
		}
	}
}
void rankrand(void) {
	int i, j, sum=0;
	for (i = 1; i <= 200; i++) {
		sum += i;
		for (j = sum - i; j < sum; j++) {
			parent[j] = 201 - i;
		}
	}
}
int main() {
	int i, j, generate;
	i0 = 1;
	j0 = 1;
	rankrand();
	srand(time(0));
	//FILE* fpsp = fopen("scatterPlot.txt", "w+");
	for (generate = 0; generate < 1000; generate++) {
		float sum = 0;
		if (generate == 0) {
			for (i = 0; i < 200; i++) {
				for (j = 0; j < 243; j++) {
					stra[i][j] = randomInt(0, 6);
					straParental[i][j] = stra[i][j];
				}
				ascore[i] = averageScore(i);
				sum += ascore[i];
			}
		}
		else {
			breed();
			for (i = 0; i < 200; i++) {
				for (j = 0; j < 243; j++) {
					straParental[i][j] = stra[i][j];
				}
				ascore[i] = averageScore(i);
				sum += ascore[i];
			}
		}
		printf("g_%d_ ave_%f\n", generate,sum / 200);
	}
	sort();
	FILE* fpout = fopen("iteration.txt", "w+");
	for (i = 0; i < 243; i++) fprintf(fpout, "%d", stra[index[0]][i]);
	getchar();
	test();
	return 0;
}