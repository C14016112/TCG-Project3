#ifndef __FIB2X3SOLVER_H__
#define __FIB2X3SOLVER_H__

#include "ModeDefintion.h"
#include "MakeMoveTable.h"
#include <iostream>
#include <fstream>
#include "math.h"
#include "time.h"
#include "stdlib.h"
#include <map>
// include anything you might use

class Fib2x3Solver
{
public:
	Fib2x3Solver();
	// initialize solver
	void initialize(int argc, char* argv[]);
	// do some action when game over
	double evaluteExpectedScore(int board[2][3]);
	int findBestMove(int board[2][3]);
	void addRandomTile(int board[2][3]);
	bool isSame(int board1[2][3], int board2[2][3]);
	double Evaluate(int board[2][3]);
	double LookTable(int board[2][3]);
	void setBoard(int newboard[2][3], const int board[2][3]);
	void WriteTable();
	void ReadTable();
	bool isFull(const int board[2][3]);
	void SetTable(const int board[2][3], const double score);
	int Simulation();
	std::map<int, int> mapFibOrder;
	/**********************************
	You can implement any additional functions
	or define any variables you may need.
	**********************************/
private:
	double *table;
	int iTableSize;
	MakeMoveTable Move;
	
};

#endif