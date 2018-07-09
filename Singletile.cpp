/*
 * Singletile.cpp
 *
 *  Created on: Jun 28, 2018
 *      Author: szymon
 */

#include "Singletile.h"

Single_tile::Single_tile():
	bomb (false),
	flag (false),
	cover (true),
	bombs_surrounding (0)
{
}

Single_tile::~Single_tile(){
}

Single_tile::Single_tile(const Single_tile & tile){
	bomb = tile.bomb;
	flag = tile.flag;
	cover = tile.cover;
	bombs_surrounding = tile.bombs_surrounding;
}

bool Single_tile::CheckIfExploded(){
	if (bomb == 1){
		return true;
		}
	else return false;
}

bool Single_tile::UncoverTile(){
	cover = false;
	return CheckIfExploded();
}
