#ifndef __MAKEMOVETABLE_H__
#define __MAKEMOVETABLE_H__
#pragma once
#include "assert.h"
#include "Fib2584/MoveDirection.h"
#include "stdio.h"
#include "math.h"
#include "ModeDefintion.h"

class MakeMoveTable
{
public:
	MakeMoveTable();
	~MakeMoveTable();
	int Move(int, int CurrentBoard[2][3]);
	void Rotate(int board[2][3]);
	void UpSideDown(int board[2][3]);
	void Mirror(int board[2][3]);
private:
	int MoveLeft(int CurrentBoard[2][3]);
	int MoveUp(int CurrentBoard[2][3]);
	int MoveDown(int CurrentBoard[2][3]);
	int MoveRight(int CurrentBoard[2][3]);
};

#endif
