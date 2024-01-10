#include <iostream>
#include <vector>
using namespace std;

bool isSafe(const vector<vector<int>> &board, int row, int col, int n) {
  for (int i = 0; i < col; i++) {
    if (board[row][i])
      return false;
  }

  for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
    if (board[i][j])
      return false;
  }

  for (int i = row, j = col; j >= 0 && i < n; i++, j--) {
    if (board[i][j])
      return false;
  }

  return true;
}

int solveNQ(vector<vector<int>> &board, int col, int n) {
  if (col >= n) {
    return 1;
  }

  int count = 0;
  for (int i = 0; i < n; i++) {
    if (isSafe(board, i, col, n)) {
      board[i][col] = 1;

      count += solveNQ(board, col + 1, n);

      board[i][col] = 0;
    }
  }

  return count;
}

int main() {
  for (int i = 8; i <= 14; i++) {
    int n = i;
    vector<vector<int>> board(n, vector<int>(n, 0));
    cout << "Number of solutions for " << n
         << "-queens is: " << solveNQ(board, 0, n) << endl;
  }

  return 0;
}
