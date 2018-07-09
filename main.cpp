/*
 * main.cpp
 *
 *  Created on: Jun 28, 2018
 *      Author: szymon
 */

#include <iostream>
#include <memory>
#include <cstdio>
#include "Singletile.h"
#include "Board.h"
#include "Gameplay.h"

using namespace std;

int main(){
	Gameplay minesweeper;
	minesweeper.PrepareGame();
	minesweeper.Play();
	return 0;
}
