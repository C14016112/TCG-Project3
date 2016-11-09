#include "stdafx.h"
#include "Fib2x3Solver.h"
static int ro = 0;
Fib2x3Solver::Fib2x3Solver()
{
	iTableSize = iUpperbound*iUpperbound*iUpperbound*iUpperbound*iUpperbound*iUpperbound;
	table = new double[iTableSize];
	for (int i = 0; i < iTableSize; i++)
		table[i] = -1;
	srand(time(NULL));

	mapFibOrder[0] = 0;
	mapFibOrder[1] = 1;
	mapFibOrder[2] = 2;
	mapFibOrder[3] = 3;
	mapFibOrder[5] = 4;
	mapFibOrder[8] = 5;
	mapFibOrder[13] = 6;
	mapFibOrder[21] = 7;
	mapFibOrder[34] = 8;
	mapFibOrder[55] = 9;
	mapFibOrder[89] = 10;
	mapFibOrder[144] = 11;
	mapFibOrder[233] = 12;
	mapFibOrder[377] = 13;
	mapFibOrder[610] = 14;
	mapFibOrder[987] = 15;
	mapFibOrder[1597] = 16;
	mapFibOrder[2584] = 17;
	mapFibOrder[4181] = 18;
	mapFibOrder[6765] = 19;
	mapFibOrder[10946] = 20;
	mapFibOrder[17711] = 21;
	mapFibOrder[28657] = 22;
	mapFibOrder[46368] = 23;
	mapFibOrder[75025] = 24;
	mapFibOrder[121393] = 25;
	mapFibOrder[196418] = 26;
	mapFibOrder[317811] = 27;
	mapFibOrder[514229] = 28;
	mapFibOrder[832040] = 29;
	mapFibOrder[1346269] = 30;
	mapFibOrder[2178309] = 31;
}

void Fib2x3Solver::initialize(int argc, char* argv[])
{
}

double Fib2x3Solver::evaluteExpectedScore(int board[2][3])
{
	
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			if ( 0 > board[i][j] || board[i][j] > iUpperbound) {
				return -1;
			}
		}
	}

	double score = LookTable(board);
	if (score != -1)
		return score;

	/* check that whether the game is end or not*/
	if (isFull(board) == true) {
		bool isend = true;
		for (int i = 0; i < 4; i++) {
			int tmpb[2][3] = {};
			setBoard(tmpb, board);
			double score = Move.Move(i, tmpb);
			
			if (isSame(tmpb, board) == false) {
				isend = false;
				break;
			}
				
		}
		if (isend == true) {
			SetTable(board, 0);
			int tmpboard[2][3] = {};
			setBoard(tmpboard, board);
			Move.Mirror(tmpboard);
			SetTable(tmpboard, 0);
			setBoard(tmpboard, board);
			Move.Rotate(tmpboard);
			SetTable(tmpboard, 0);
			setBoard(tmpboard, board);
			Move.UpSideDown(tmpboard);
			SetTable(tmpboard, 0);
			return 0;
		}
	}

#ifndef __TESTMODE__
	ro++;
	std::cout << ro << " ";
	if (ro % 100000 == 0 && ro > 0)
		WriteTable();
#endif
	score = 0;
	int bestdir = 0;
	for (int i = 0; i < 4; i++) {
		int movedboard[2][3] = {};
		setBoard(movedboard, board);

		double expectedscore = 0;
		double award = Move.Move(i, movedboard);
		if (isSame(movedboard, board) == true)
			continue;
		int empty_count = 0;
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 3; k++) {
				if (movedboard[j][k] == 0) {
					empty_count++;
					int tmpmovedboard1[2][3] = {};
					int tmpmovedboard3[2][3] = {};
					setBoard(tmpmovedboard1, movedboard);
					setBoard(tmpmovedboard3, movedboard);
					tmpmovedboard1[j][k] = 1;
					tmpmovedboard3[j][k] = 3;
					expectedscore += 0.75 * evaluteExpectedScore(tmpmovedboard1);
					expectedscore += 0.25 * evaluteExpectedScore(tmpmovedboard3);
				}
			}
		}
		if (empty_count > 0)
			expectedscore = expectedscore / empty_count;
		expectedscore += award;
		
		if (expectedscore > score) {
			score = expectedscore;
			bestdir = i;
		}
	}
	/* write the expected score into table, including rotate, upsidedown and mirror*/
	int tmpboard[2][3] = {};
	SetTable(board, score);
	setBoard(tmpboard, board);
	Move.Mirror(tmpboard);
	SetTable(tmpboard, score);
	setBoard(tmpboard, board);
	Move.Rotate(tmpboard);
	SetTable(tmpboard, score);
	setBoard(tmpboard, board);
	Move.UpSideDown(tmpboard);
	SetTable(tmpboard, score);
	return score;
}

// 0: up
// 1: right
// 2: down
// 3: left
// -1: cannot move
int Fib2x3Solver::findBestMove(int arrayboard[2][3])
{
	double score = 0;
	int bestdir = -1;
	for (int i = 0; i < 4; i++) {
		int movedboard[2][3] = {};
		setBoard(movedboard, arrayboard);

		double expectedscore = 0;
		double award = Move.Move(i, movedboard);
		if (isSame(movedboard, arrayboard) == true)
			continue;
		int empty_count = 0;
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 3; k++) {
				if (movedboard[j][k] == 0) {
					empty_count++;
					int tmpmovedboard1[2][3] = {};
					int tmpmovedboard3[2][3] = {};
					setBoard(tmpmovedboard1, movedboard);
					setBoard(tmpmovedboard3, movedboard);
					tmpmovedboard1[j][k] = 1;
					tmpmovedboard3[j][k] = 3;
					expectedscore += 0.75 * evaluteExpectedScore(tmpmovedboard1);
					expectedscore += 0.25 * evaluteExpectedScore(tmpmovedboard3);
				}
			}
		}
		if (empty_count > 0)
			expectedscore = expectedscore / empty_count;
		expectedscore += award;

		if (expectedscore > score) {
			score = expectedscore;
			bestdir = i;
		}
	}
	return bestdir;
}

void Fib2x3Solver::addRandomTile(int board[2][3])
{
	int zero_count = 0;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == 0)
				zero_count++;
		}
	}
	if (zero_count == 0)
		return;
	else {
		int new_tile_position = rand() % zero_count;
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 3; j++) {
				if (board[i][j] == 0 && new_tile_position == 0) {
					if (rand() % 4 < 3)
						board[i][j] = 1;
					else
						board[i][j] = 3;
					return;
				}
				else if(board[i][j] == 0)
					new_tile_position--;
			}
		}
	}
}

bool Fib2x3Solver::isSame(int board1[2][3], int board2[2][3])
{
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 3; j++)
			if (board1[i][j] != board2[i][j])
				return false;
	return true;
}

double Fib2x3Solver::Evaluate(int board[2][3])
{
	int position = board[0][0] + iUpperbound*board[0][1] + iUpperbound*iUpperbound*board[0][2] + iUpperbound*iUpperbound*iUpperbound*board[0][3]
		+ iUpperbound*iUpperbound*iUpperbound*iUpperbound*board[0][4] + iUpperbound*iUpperbound*iUpperbound*iUpperbound*iUpperbound*board[0][5];
	if (position > iTableSize)
		return -1;
	return table[position];
}

double Fib2x3Solver::LookTable(int board[2][3])
{
	
	int tmpboard[2][3] = {};
	if (Evaluate(board) >= 0)
		return Evaluate(board);
	setBoard(tmpboard, board);
	Move.Mirror(tmpboard);
	if (Evaluate(tmpboard) >= 0)
		return Evaluate(tmpboard);
	setBoard(tmpboard, board);
	Move.Rotate(tmpboard);
	if (Evaluate(tmpboard) >= 0)
		return Evaluate(tmpboard);
	setBoard(tmpboard, board);
	Move.UpSideDown(tmpboard);
	if (Evaluate(tmpboard) >= 0)
		return Evaluate(tmpboard);

	return -1;
}

void Fib2x3Solver::setBoard(int newboard[2][3], const int board[2][3])
{
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			newboard[i][j] = board[i][j];
		}
	}
}

void Fib2x3Solver::WriteTable()
{
	std::ofstream fout;
	fout.open("Table", std::ios::out | std::ios::binary );
	if (!fout.is_open()) {
		printf("Error to open table!\n");
		return;
	}
	fout.write(reinterpret_cast<char *>(table), iTableSize * sizeof(double));
	fout.close();

	/*FILE *data; 
	fopen_s(&data, "Table.txt", "w");
	for (int i = 0; i < iTableSize; i++)
		fprintf(data, "%lf \n", table[i]);
	fclose(data);*/
}

bool Fib2x3Solver::isFull(const int board[2][3])
{
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 3; j++)
			if (board[i][j] == 0) return false;
	return true;
}

void Fib2x3Solver::SetTable(const int board[2][3], const double score)
{
	int position = board[0][0] + iUpperbound*board[0][1] + iUpperbound*iUpperbound*board[0][2] + iUpperbound*iUpperbound*iUpperbound*board[0][3]
		+ iUpperbound*iUpperbound*iUpperbound*iUpperbound*board[0][4] + iUpperbound*iUpperbound*iUpperbound*iUpperbound*iUpperbound*board[0][5];
	table[position] = score;
}

void Fib2x3Solver::ReadTable()
{
	/*FILE *data;
	fopen_s(&data, "Table.txt", "w");
	for (int i = 0; i < iTableSize; i++)
		fscanf_s(data, "%lf \n", &table[i]);
	fclose(data);*/
	std::ifstream fin;
	fin.open("Table", std::ios::in | std::ios::binary );
	if (!fin.is_open()) {
		printf("Error to Read Table");
		return;
	}
	fin.read(reinterpret_cast<char*>(table), (iTableSize)* sizeof(double));
	fin.close();
}

int Fib2x3Solver::Simulation()
{
	for (int k = 0; k < 4; k++) {
		for (int i = 0; i < 6; i++) {
			for (int j = i; j < 6; j++) {
				int board[2][3] = {};
				/*solver.addRandomTile(board);
				solver.addRandomTile(board);*/
				if (k == 0) {
					board[i / 3][i % 3] = 1;
					board[j / 3][j % 3] = 1;
				}
				else if (k == 1) {
					board[i / 3][i % 3] = 1;
					board[j / 3][j % 3] = 3;
				}
				else if (k == 2) {
					board[i / 3][i % 3] = 3;
					board[j / 3][j % 3] = 1;
				}
				else {
					board[i / 3][i % 3] = 3;
					board[j / 3][j % 3] = 3;
				}
				for (;;) {
					int originalboard[2][3] = {};
					setBoard(originalboard, board);

					int dir = evaluteExpectedScore(board);

					if (isFull(board) == true)
						break;
					addRandomTile(board);
				}

			}
		}
	}
	std::cout << "start write table" << std::endl;
	WriteTable();
	std::cout << "end write table" << std::endl;
	std::cout << "finish" << std::endl;
	return 0;
}