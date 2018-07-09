/*
 * Singletile.h
 *
 *  Created on: Jun 28, 2018
 *      Author: szymon
 */

#ifndef SINGLETILE_H_
#define SINGLETILE_H_

#include <iostream>

class Single_tile {
	bool bomb;
	bool flag;
	bool cover;
	int bombs_surrounding;
public:
	Single_tile();
	Single_tile(const Single_tile & tile);
	virtual ~Single_tile();
	void SetBomb(){ bomb = true;}
	void SetFlag(){ flag = !flag;}
	bool CheckIfExploded();
	bool CheckIfCovered(){ return cover; }
	bool CheckIfFlagged(){ return flag; };
	bool UncoverTile();
	int PrintBombsSurroundingValue(){ return bombs_surrounding;}
	void SetBombsSurroundingValue(int number_of_bombs){ bombs_surrounding = number_of_bombs;}
};

#endif /* SINGLETILE_H_ */
