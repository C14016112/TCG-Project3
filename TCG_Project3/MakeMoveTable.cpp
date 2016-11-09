#include "stdafx.h"
#include "MakeMoveTable.h"
MakeMoveTable::MakeMoveTable()
{
}

MakeMoveTable::~MakeMoveTable()
{
}

int MakeMoveTable::MoveLeft(int CurrentBoard[2][3])
{
	int award = 0;
	for (int i = 0; i < 2; i++) {
		int index[3] = { CurrentBoard[i][0], CurrentBoard[i][1], CurrentBoard[i][2]};
		int head = 0;
		int tail = 0;
		while (tail < 3) {
			if (index[tail] != 0) {
				int tmp = index[head];
				index[head] = index[tail];
				index[tail] = tmp;
				head++;
				tail++;
			}
			else {
				tail++;
			}
		}

		int check_position = 0;
		while (check_position < 2) {
			int next_position = check_position + 1;
			if (index[check_position] != 0 && index[next_position] != 0
				&& (abs(index[check_position] - index[next_position]) == 1) || (index[check_position] == 1 && index[check_position + 1] == 1)) {
				if (index[check_position] == index[next_position] - 1) {
					index[check_position] = index[check_position] + 2;
					index[next_position] = 0;
					award += fibonacci_seq[index[check_position]]; // award
				}
				else {
					index[check_position] = index[check_position] + 1;
					index[next_position] = 0;
					award += fibonacci_seq[index[check_position]];// award

				}
				check_position = check_position + 2;
			}
			else {
				check_position = check_position + 1;
			}
		}

		// pull to left again
		head = 0;
		tail = 0;
		while (tail < 3) {
			if (index[tail] != 0) {
				int tmp = index[head];
				index[head] = index[tail];
				index[tail] = tmp;
				head++;
				tail++;
			}
			else {
				tail++;
			}
		}
		for (int j = 0; j < 3; j++) {
			CurrentBoard[i][j] = index[j];
		}
	}
	return award;
}

int MakeMoveTable::MoveRight(int CurrentBoard[2][3])
{
	int award = 0;
	Rotate(CurrentBoard);
	award = MoveLeft(CurrentBoard);
	Rotate(CurrentBoard);
	return award;
}

int MakeMoveTable::MoveUp(int CurrentBoard[2][3])
{
	int award = 0;
	for (int i = 0; i < 3; i++) {
		int index[2] = { CurrentBoard[0][i], CurrentBoard[1][i]};
		if (index[0] == 0 && index[1] != 0) {
			index[0] = index[1];
			index[1] = 0;
		}
			
		if (index[0] != 0 && index[1] != 0
			&& (abs(index[0] - index[1]) == 1) || (index[0] == 1 && index[1] == 1)) {
			if (index[0] == index[1] - 1) {
				index[0] = index[0] + 2;
				index[1] = 0;
				award += fibonacci_seq[index[0]]; // award
			}
			else {
				index[0] = index[0] + 1;
				index[1] = 0;
				award += fibonacci_seq[index[0]];// award

			}
		}


		if (index[0] == 0 && index[1] != 0) {
			index[0] = index[1];
			index[1] = 0;
		}
		for (int j = 0; j < 2; j++) {
			CurrentBoard[j][i] = index[j];
		}
	}
	return award;
}

int MakeMoveTable::MoveDown(int CurrentBoard[2][3])
{
	UpSideDown(CurrentBoard);
	int award = 0;
	award = MoveUp(CurrentBoard);
	UpSideDown(CurrentBoard);
	return award;
}

int MakeMoveTable::Move(int action, int CurrentBoard[2][3]){
#ifdef _DEBUG
	assert(action >= 0 && action < 4);
#endif
	switch (action) {
	case 2:
		return MoveDown(CurrentBoard);
	case 0:
		return MoveUp(CurrentBoard);
	case 1:
		return MoveRight(CurrentBoard);
	case 3:
		return MoveLeft(CurrentBoard);
	default:
		return -1;
	}

}

void MakeMoveTable::Rotate(int board[2][3])
{
	for (int i = 0; i < 3; i++) {
		int tmp = board[1][i];
		board[1][i] = board[0][2 - i];
		board[0][2 - i] = tmp;
	}
}
void MakeMoveTable::UpSideDown(int board[2][3])
{
	for (int i = 0; i < 3; i++) {
		int tmp = board[0][i];
		board[0][i] = board[1][i];
		board[1][i] = tmp;
	}
}

void MakeMoveTable::Mirror(int board[2][3])
{
	int tmp;
	tmp = board[0][0];
	board[0][0] = board[0][2];
	board[0][2] = tmp;
	tmp = board[1][0];
	board[1][0] = board[1][2];
	board[1][2] = tmp;
}