#pragma once
int a[12][12], score, i0, j0;
int straParental[200][243], index[200];
int randomInt(int x, int y);
void createMap();
void printMap(void);
void moveup(void);
void movedown(void);
void moveleft(void);
void moveright(void);
void dontmove(void);
void pick(void);
void action_(int n);
void test(void);