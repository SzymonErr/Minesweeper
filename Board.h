/*
 * Board.h
 *
 *  Created on: Jun 28, 2018
 *      Author: szymon
 */

#ifndef BOARD_H_
#define BOARD_H_

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <vector>
#include "Singletile.h"
using board_line = std::vector<Single_tile>;

class Board: public Single_tile {
	int board_width;
	int board_height;
	int number_of_bombs;
	int covered_tiles_left;
	std::vector<board_line> game_board;
public:
	Board();
	virtual ~Board();
	Board(const Board & board_copy);
	void SetBoardSize();
	void SetNumberOfBombs();
	int GetBoardHeight(){ return board_height;}
	int GetBoardWidth(){ return board_width;}
	void GenerateBoard();
	void DrawBombPosition();
	void PrintBoard();
	void GetGameBoard();
	int GetNumberOfBombs() {return number_of_bombs;}
	int & GetCoveredTilesLeft() {return covered_tiles_left;}
	void DecrementNumberOfCoveredTiles() {covered_tiles_left--;}
	void CountBombsSurrounding(int height, int width);
	void UpdateBombsInfo();
	void UncoverArea(int height, int width);
	void PrintLowerFrame();
	Single_tile & tileAt(int x, int y);
};

#endif /* BOARD_H_ */
