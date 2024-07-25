#define _CRT_SECURE_NO_WARNINGS
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int a[12][12], score = 0, scoretemp, i0 = 1, j01 = 1;
int move, i, j, speedflag = 0, step, leftOrRight=0;
int close = 0;
int speed = 5, maxmove;
char scoret;
SDL_Rect dest, bottle, scorePosition;
SDL_Window* win;
Uint32 render_flags;
SDL_Renderer* rend;
SDL_Surface* surface_y, * surface_ypick, * surface_b, * surface_score;
SDL_Texture* tex_y, * tex_yr, * tex_yl, * tex_ypickr, * tex_ypickl, * tex_b, * tex_score;
TTF_Font* font;
SDL_Color color = { 0,0,0,50 };
int randomInt(int x, int y) {
	int t = rand() % (y - x + 1) + x;
	return t;
}
void numberSurface(int n) {
	switch (n) {
	case 0:surface_score = TTF_RenderUTF8_Blended(font, "0", color); break;
	case 1:surface_score = TTF_RenderUTF8_Blended(font, "1", color); break;
	case 2:surface_score = TTF_RenderUTF8_Blended(font, "2", color); break;
	case 3:surface_score = TTF_RenderUTF8_Blended(font, "3", color); break;
	case 4:surface_score = TTF_RenderUTF8_Blended(font, "4", color); break;
	case 5:surface_score = TTF_RenderUTF8_Blended(font, "5", color); break;
	case 6:surface_score = TTF_RenderUTF8_Blended(font, "6", color); break;
	case 7:surface_score = TTF_RenderUTF8_Blended(font, "7", color); break;
	case 8:surface_score = TTF_RenderUTF8_Blended(font, "8", color); break;
	case 9:surface_score = TTF_RenderUTF8_Blended(font, "9", color); break;
	}
	tex_score = SDL_CreateTextureFromSurface(rend, surface_score);
	SDL_FreeSurface(surface_score);
	scorePosition.w = 60;
	scorePosition.x = 610 - i * 60;
	SDL_RenderCopy(rend, tex_score, NULL, &scorePosition);
	SDL_DestroyTexture(tex_score);
}
void printScore(void) {
	surface_score = TTF_RenderUTF8_Blended(font, "score:", color);
	tex_score = SDL_CreateTextureFromSurface(rend, surface_score);
	SDL_FreeSurface(surface_score);
	scorePosition.w = 360;
	scorePosition.h = 200;
	scorePosition.x = 130;
	scorePosition.y = 400 - scorePosition.h / 2;
	SDL_RenderCopy(rend, tex_score, NULL, &scorePosition);
	SDL_DestroyTexture(tex_score);
	scoretemp = score;
	for (i = 0; i < 3; i++) {
		numberSurface(scoretemp % 10);
		scoretemp /= 10;
	}
}
void printScreen(void) {
	SDL_RenderClear(rend);
	printScore();
	for (i = 1; i <= 10; i++) {
		for (j = 1; j <= 10; j++) {
			if (a[i][j]%10 == 1) {
				bottle.x = 70 + 60 * j - bottle.w / 2;
				bottle.y = 70 + 60 * i - bottle.h / 2;
				SDL_RenderCopy(rend, tex_b, NULL, &bottle);
			}
		}
	}
	SDL_RenderCopy(rend, tex_y, NULL, &dest);
	SDL_RenderPresent(rend);
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
	a[i0][j01] += 10;
}
void printOriginMap(void) {
	dest.w /= 5;
	dest.h /= 5;
	dest.x = 130 - dest.w / 2;
	dest.y = 130 - dest.h / 2;
	printScreen();
	SDL_Delay(1000);
}
void moveup(void) {
	for (move = 0; move < maxmove; move++) {
		dest.y -= speed;
		if (dest.y == 100 - dest.h / 2) {
			speed *= (-1);
			speedflag = 1;
		}
		printScreen();
		SDL_Delay(20);
	}
	if (speedflag == 1) {
		speed *= (-1);
		speedflag = 0;
	}
	a[i0][j01] -= 10;
	i0 -= 1;
	if (a[i0][j01] == 2) {
		i0 += 1;
		score -= 5;
	}
	a[i0][j01] += 10;
}
void movedown(void) {
	for (move = 0; move < maxmove; move++) {
		dest.y += speed;
		if (dest.y == 700 - dest.h / 2) {
			speed *= (-1);
			speedflag = 1;
		}
		printScreen();
		SDL_Delay(20);
	}
	if (speedflag == 1) {
		speed *= (-1);
		speedflag = 0;
	}
	a[i0][j01] -= 10;
	i0 += 1;
	if (a[i0][j01] == 2) {
		i0 -= 1;
		score -= 5;
	}
	a[i0][j01] += 10;
}
void moveleft(void) {
	if (leftOrRight == 0) {
		tex_y = tex_yl;
		leftOrRight = 1;
	}
		SDL_QueryTexture(tex_y, NULL, NULL, &dest.w, &dest.h);
	dest.w /= 5;
	dest.h /= 5;
	printScreen();
	for (move = 0; move < maxmove; move++) {
		dest.x -= speed;
		if (dest.x == 100 - dest.w / 2) {
			speed *= (-1);
			speedflag = 1;
		}
		printScreen();
		SDL_Delay(20);
	}
	if (speedflag == 1) {
		speed *= (-1);
		speedflag = 0;
	}
	a[i0][j01] -= 10;
	j01 -= 1;
	if (a[i0][j01] == 2) {
		j01 += 1;
		score -= 5;
	}
	a[i0][j01] += 10;
}
void moveright(void) {
	if (leftOrRight == 1) {
		tex_y = tex_yr;
		leftOrRight = 0;
	}
		SDL_QueryTexture(tex_y, NULL, NULL, &dest.w, &dest.h);
	dest.w /= 5;
	dest.h /= 5;
	printScreen();
	for (move = 0; move < maxmove; move++) {
		dest.x += speed;
		if (dest.x == 700 - dest.w / 2) {
			speed *= (-1);
			speedflag = 1;
		}
		printScreen();
		SDL_Delay(20);
	}
	if (speedflag == 1) {
		speed *= (-1);
		speedflag = 0;
	}
	a[i0][j01] -= 10;
	j01 += 1;
	if (a[i0][j01] == 2) {
		j01 -= 1;
		score -= 5;
	}
	a[i0][j01] += 10;
}
void dontmove(void) {
	;
}
void pick(void) {
	if (leftOrRight == 0) tex_y = tex_ypickr;
	else tex_y = tex_ypickl;
	SDL_QueryTexture(tex_y, NULL, NULL, &dest.w, &dest.h);
	dest.w /= 5;
	dest.h /= 5;
	printScreen();
	SDL_Delay(200);
	if (leftOrRight == 0) tex_y = tex_yr;
	else tex_y = tex_yl;
	SDL_QueryTexture(tex_y, NULL, NULL, &dest.w, &dest.h);
	dest.w /= 5;
	dest.h /= 5;
	a[i0][j01] -= 1;
	if (a[i0][j01] < 10) {
		score -= 2;
		a[i0][j01] += 1;
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
}
int main(int argc, char* argv[]) {
	srand(time(0));
	int select;
	int strategy[243];
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	win = SDL_CreateWindow("GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, 0);
	render_flags = SDL_RENDERER_ACCELERATED;
	rend = SDL_CreateRenderer(win, -1, render_flags);
	SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
	font = TTF_OpenFont("FinoTitle-Bold.OTF", 200);
	surface_ypick = IMG_Load("Images/LittleYellow1.png");
	surface_y = IMG_Load("Images/LittleYellow2.png");
	tex_ypickr = SDL_CreateTextureFromSurface(rend, surface_ypick);
	tex_yr = SDL_CreateTextureFromSurface(rend, surface_y);
	SDL_FreeSurface(surface_y);
	SDL_FreeSurface(surface_ypick);
	surface_ypick = IMG_Load("Images/LittleYellow3.png");
	surface_y = IMG_Load("Images/LittleYellow4.png");
	tex_ypickl = SDL_CreateTextureFromSurface(rend, surface_ypick);
	tex_yl = SDL_CreateTextureFromSurface(rend, surface_y);
	SDL_FreeSurface(surface_y);
	SDL_FreeSurface(surface_ypick);
	surface_b = IMG_Load("Images/Bottle.png");
	tex_b = SDL_CreateTextureFromSurface(rend, surface_b);
	SDL_FreeSurface(surface_b);
	tex_y = tex_yr;
	SDL_QueryTexture(tex_y, NULL, NULL, &dest.w, &dest.h);	
	SDL_QueryTexture(tex_b, NULL, NULL, &bottle.w, &bottle.h);
	createMap();
	printOriginMap();
	FILE* fp = fopen("strategy.txt", "r");
	for (i = 0; i < 243; i++)
	{
		fscanf(fp, "%1d", &strategy[i]);
	}
	maxmove = 60 / speed;
	step=0;
	SDL_Event event;
	while (close == 0 && step < 200) {
		SDL_PollEvent(&event);
		if (event.key.keysym.scancode != SDL_SCANCODE_Q) {
			select = a[i0 - 1][j01] * 81 + a[i0 + 1][j01] * 27 + a[i0][j01 + 1] * 9 + a[i0][j01 - 1] * 3 + (a[i0][j01] - 10);
			action(strategy[select]);
			printScreen();
			SDL_Delay(100);
		}
		else close = 1;
		step += 1;
	}
	while (close == 0 && event.key.keysym.scancode != SDL_SCANCODE_Q) {
		SDL_PollEvent(&event);
	}
	SDL_DestroyTexture(tex_y);
	SDL_DestroyTexture(tex_yl);
	SDL_DestroyTexture(tex_yr);
	SDL_DestroyTexture(tex_ypickl);
	SDL_DestroyTexture(tex_ypickr);
	SDL_DestroyTexture(tex_b);
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}