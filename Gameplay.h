/*
 * Gameplay.h
 *
 *  Created on: Jun 28, 2018
 *      Author: szymon
 */

#ifndef GAMEPLAY_H_
#define GAMEPLAY_H_

#include <iostream>
#include <cstdio>
#include "Board.h"

class Gameplay{
	int actual_x;
	int actual_y;
	bool gameover;
	bool win;
	Board myBoard;
	bool flag_mode;
public:
	Gameplay();
	virtual ~Gameplay();
	Gameplay(const Gameplay & play);
	void PrepareGame();
	void ReadPlayerMove();
	void UpdateBoardStatus();
	void Play();
	void PrintEndStatement();
	void CheckWinCondition();
};

#endif /* GAMEPLAY_H_ */
