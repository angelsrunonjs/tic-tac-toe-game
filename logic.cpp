#include <iostream>
#include "Gamelogic.h"

char space[9] = {'0', '1', '2', '3', '4', '5', '6', '7', '8'};
char markx = 'X';
char marko = 'O';

int checkgamestatus() {
	if (space[0] == space[1] && space[1] == space[2]) return 1;
	if (space[3] == space[4] && space[4] == space[5]) return 1;
	if (space[6] == space[7] && space[7] == space[8]) return 1;


	if (space[0] == space[3] && space[3] == space[6]) return 1;
	if (space[1] == space[4] && space[4] == space[7]) return 1;
	if (space[2] == space[5] && space[5] == space[8]) return 1;


	if (space[0] == space[4] && space[4] == space[8]) return 1;
	if (space[2] == space[4] && space[4] == space[6]) return 1;


	if (space[0] != '0' && space[1] != '1' && space[2] != '2' &&
		space[3] != '3' && space[4] != '4' && space[5] != '5' &&
		space[6] != '6' && space[7] != '7' && space[8] != '8')
		return 0;

	return -1;
}

void playermove(int which, int pos) {

	if (which % 2 == 0) {
		space[pos] = markx;
	}
	else {
		space[pos] = marko;
	}
}

void resetGame() {
	for (int i = 0; i < 9; i++) {
		space[i] = '0' + i;
	}
}