#include <iostream>
using namespace std;
const int n = 8;
int board[n][n] = { 0 };
int solution = 0;
bool isSafe(int row, int col) {
	for (int i = 0; i < row; i++) {
		if (board[i][col] == 1) {
			return false;
		}
		if (col - (row - i) >= 0 && board[i][col - (row - i)] == 1) {
			return false;
		}
		if (col + (row - i) < n && board[i][col + (row - i)] == 1) {
			return false;
		}
	}
	return true;
}
void QueenSolve(int row) {
	if (row == n) {
		solution++;
		return;
	}
	for (int col = 0; col < n; col++) {
		if (isSafe(row, col)) {
			board[row][col] = 1;
			QueenSolve(row + 1);
			board[row][col] = 0;
		}
	}
}
int main() {
	QueenSolve(0);
	cout << "Solution: " << solution;
}