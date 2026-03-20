#pragma once

extern char space[9];
extern char markx;
extern char marko;

int checkgamestatus();
void playermove(int which, int pos);
void resetGame();