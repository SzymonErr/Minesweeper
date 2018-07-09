/*
 * Board.cpp
 *
 *  Created on: Jun 28, 2018
 *      Author: szymon
 */

#include "Board.h"

Board::Board():
	board_width (0),
	board_height (0),
	number_of_bombs(0),
	covered_tiles_left(0)
{
}

Board::~Board(){
	game_board.clear();
}

Board::Board(const Board & board_copy){
	board_width = board_copy.board_width;
	board_height = board_copy.board_height;
	number_of_bombs = board_copy.number_of_bombs;
	covered_tiles_left = board_copy.covered_tiles_left;
}

int SetSingleSize(){
	int size = 0;
	std::cin >> size;
	while(size < 1 || !std::cin.good()){
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cout << "Niepoprawna wartosc. Podaj wartosc w postaci liczby calkowitej, wiekszej od 0: " << std::endl;
			std::cin >> size;
		}
	return size;
}

void Board::SetBoardSize(){
	std::cout << "Podaj szerokosc planszy: " << std::endl;
	board_width = SetSingleSize();
	std::cout << "Podaj wysokosc planszy: " << std::endl;
	board_height = SetSingleSize();
}

void Board::SetNumberOfBombs(){
	std::cout << "Podaj liczbe bomb na planszy: " << std::endl;
	number_of_bombs = SetSingleSize();
	while(number_of_bombs > board_height*board_width){
		std::cout << "Za duzo bomb! Podaj nowa wartosc: " << std::endl;
		number_of_bombs = SetSingleSize();
	}
}

void Board::GenerateBoard(){
	std::vector<Single_tile> game_vec;
	for (int act_height = 0; act_height < board_height; act_height++){
		game_vec.clear();
		for (int act_width = 0; act_width < board_width; act_width++){
			Single_tile temp;
			game_vec.push_back(temp);
			covered_tiles_left++;
		}
	game_board.push_back(game_vec);
	}
}

void Board::PrintBoard(){
	std::cout << "Drukuje plansze!" << std::endl;
	//int ile = 0;
	/*for ( auto i : game_board)
		ile++;
	std::cout << "Ile?" << ile << std::endl;*/

	std::cout << "Board_height=" << board_height << std::endl;
	for (int tmp_height = 0; tmp_height < board_height; tmp_height++){
		for (int tmp_width = 0; tmp_width < board_width; tmp_width++){
			if(tileAt(tmp_height, tmp_width).CheckIfCovered() && !tileAt(tmp_height, tmp_width).CheckIfFlagged()){
				std::cout << "# ";
			}
			else if (!tileAt(tmp_height, tmp_width).CheckIfCovered() && !tileAt(tmp_height, tmp_width).CheckIfExploded()){
				std::cout << tileAt(tmp_height, tmp_width).PrintBombsSurroundingValue() << " ";
			}
			else if (tileAt(tmp_height, tmp_width).CheckIfFlagged() && tileAt(tmp_height, tmp_width).CheckIfCovered()){
				std::cout << "F ";
			}
			else{
				std::cout << "B ";
			}
		}
		std::cout << "| " <<tmp_height;
		std::cout << std::endl;
	}
	PrintLowerFrame();
}

void Board::DrawBombPosition(){
	std::srand(std::time(0));
	int bombs_to_plant = number_of_bombs;
	while (bombs_to_plant > 0){
		int y = rand() % board_height;
		int x = rand() % board_width;
		if (!game_board.at(y).at(x).CheckIfExploded()){
			tileAt(y,x).SetBomb();
			bombs_to_plant--;
		}
	}
}

void Board::CountBombsSurrounding(int height, int width){
	int tmp_number_of_bombs = 0;
	int tmp_height;
	int tmp_width;
	for(int surr_height = -1; surr_height <= 1; surr_height++){
		tmp_height = height + surr_height;
		if(tmp_height >= 0 && tmp_height < board_height){
			for(int surr_width = -1; surr_width <= 1; surr_width++){
				tmp_width = width + surr_width;
				if(tmp_width >= 0 && tmp_width < board_width){
					if(tileAt(tmp_height, tmp_width).CheckIfExploded()) tmp_number_of_bombs++;
				}
			}
		}
	}
	tileAt(height, width).SetBombsSurroundingValue(tmp_number_of_bombs);
}

void Board::UpdateBombsInfo(){
	for (int tmp_height = 0; tmp_height < board_height; tmp_height++){
		for (int tmp_width = 0; tmp_width < board_width; tmp_width++){
			CountBombsSurrounding(tmp_height, tmp_width);
		}
	}
}

void Board::UncoverArea(int height, int width){
	int tmp_height;
	int tmp_width;
	for (int surr = -1; surr <= 1; surr++){
		tmp_height = height + surr;
		if(tmp_height >= 0 && tmp_height < board_height){
			if(!tileAt(tmp_height, width).CheckIfExploded() && tileAt(tmp_height, width).CheckIfCovered()){
				tileAt(tmp_height, width).UncoverTile();
				DecrementNumberOfCoveredTiles();
				if(!tileAt(tmp_height, width).PrintBombsSurroundingValue()) UncoverArea(tmp_height, width);
			}
		}
	}
	for (int surr = -1; surr <= 1; surr++){
		tmp_width = width + surr;
		if(tmp_width >= 0 && tmp_width < board_width){
			if(!tileAt(height, tmp_width).CheckIfExploded() && tileAt(height, tmp_width).CheckIfCovered()){
				tileAt(height, tmp_width).UncoverTile();
				DecrementNumberOfCoveredTiles();
				if(tileAt(height, tmp_width).PrintBombsSurroundingValue() == 0) UncoverArea(height, tmp_width);
			}
		}
	}
}

void Board::PrintLowerFrame(){
	for (int tmp_width = 0; tmp_width < board_width; tmp_width++){
		std::cout <<  "--";
	}
	std::cout << std::endl;
	for (int tmp_width = 0; tmp_width < board_width; tmp_width++){
		std::cout <<  tmp_width%10 << " ";
	}
	std::cout << std::endl;
}

Single_tile & Board::tileAt(int x, int y)
{
	return game_board.at(x).at(y);
}


