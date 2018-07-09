/*
 * Gameplay.cpp
 *
 *  Created on: Jun 28, 2018
 *      Author: szymon
 */

#include "Gameplay.h"

Gameplay::Gameplay():
	actual_x (0),
	actual_y (0),
	gameover (false),
	win (false),
	flag_mode (false)
{

}

Gameplay::~Gameplay(){
}

Gameplay::Gameplay(const Gameplay & play){
	actual_x = play.actual_x;
	actual_y = play.actual_y;
	gameover = play.gameover;
	win = play.win;
	flag_mode = play.flag_mode;
}

void Gameplay::PrepareGame(){
	myBoard.SetBoardSize();
	myBoard.SetNumberOfBombs();
	myBoard.GenerateBoard();
	myBoard.DrawBombPosition();
	myBoard.UpdateBombsInfo();
	myBoard.PrintBoard();
}



void Gameplay::ReadPlayerMove(){
	char flag_mode_check[8];
	std::cout << "Podaj wartosci x, y: " << std::endl;
	std::cin >> flag_mode_check;
	if (*flag_mode_check == 'F' || *flag_mode_check == 'f'){
		flag_mode = !flag_mode;
		if (flag_mode)
			std::cout << "Flagging mode activated!" << std::endl;
		else
			std::cout << "Flagging mode deactivated!" << std::endl;
		std::cin >> actual_x;
	}
	else actual_x = atoi(flag_mode_check);
	while (actual_x < 0 || actual_x >= myBoard.GetBoardWidth() || !std::cin.good()){
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		std::cout << "Nieprawidlowa wartosc x. Podaj nowe wspolrzedne: " << std::endl;
		std::cin >> actual_x;
	}
	std::cin >> actual_y;
	while (actual_y < 0 || actual_y >= myBoard.GetBoardHeight() || !std::cin.good()){
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		std::cout << "Nieprawidlowa wartosc y, podaj nowe wspolrzedne: " << std::endl;
		std::cin >> actual_x >> actual_y;
	}
	std::cout << "Odkryto pole o wspolrzednych (" << actual_x << ", " << actual_y << ")" << std::endl;
}

void Gameplay::UpdateBoardStatus(){
	if(flag_mode){
		myBoard.tileAt(actual_y, actual_x).SetFlag();
		return;
	}
	gameover = myBoard.tileAt(actual_y, actual_x).UncoverTile();
	myBoard.DecrementNumberOfCoveredTiles();
	if (gameover){
		myBoard.PrintBoard();
		return;
	}
	if(!myBoard.tileAt(actual_y, actual_x).PrintBombsSurroundingValue())
		myBoard.UncoverArea(actual_y, actual_x);
}

void Gameplay::Play(){
	while (!gameover && !win){
		ReadPlayerMove();
		UpdateBoardStatus();
		myBoard.PrintBoard();
		std::cout << "Pozostalo zakrytych plytek: " << myBoard.GetCoveredTilesLeft() << std::endl;
		CheckWinCondition();
	}
	PrintEndStatement();

}

void Gameplay::CheckWinCondition(){
	if(myBoard.GetCoveredTilesLeft() == myBoard.GetNumberOfBombs())
		win = true;
}

void Gameplay::PrintEndStatement(){
	std::string win_text = "CONGRATULATIONS!";
	if (gameover) std::cout << "You lose!" << std::endl;
	else if(win){
		for (unsigned int tmp = 0; tmp < win_text.size(); tmp++)
			std::cout << win_text[tmp] << std::endl;
	}
}
