// OBST
#include <iostream>
#include <limits>
#include <math.h>
#include <queue>
#include <vector>
using namespace std;

int main() {
  vector<double> p({-1.0, 0.04, 0.06, 0.08, 0.02, 0.10, 0.12, 0.14});
  vector<double> q({0.06, 0.06, 0.06, 0.06, 0.05, 0.05, 0.05, 0.05});
  int n = p.size() - 1;
  vector<vector<double>> E(n + 2, vector<double>(n + 1));
  vector<vector<double>> W(n + 2, vector<double>(n + 1));
  vector<vector<int>> R(n + 2, vector<int>(n + 1));

  for (int i = 0; i <= n; ++i) {
    E[i + 1][i] = q[i];
    W[i + 1][i] = q[i];
  }

  for (int length = 0; length < n; ++length) {
    for (int i = 1; i <= n - length; ++i) {
      int j = i + length;
      W[i][j] = W[i][j - 1] + p[j] + q[j];
      double tmp = numeric_limits<double>::max();
      for (int r = i; r <= j; ++r) {
        if (tmp > E[i][r - 1] + E[r + 1][j] + W[i][j]) {
          tmp = E[i][r - 1] + E[r + 1][j] + W[i][j];
          R[i][j] = r;
        }
      }
      E[i][j] = tmp;
    }
  }
  printf("Minimum cost: %.2lf\n", E[1][n]);

  queue<tuple<int, int, int, int>> myQ;
  printf("OBST sturcture by level-order:\n");
  myQ.push({1, n, R[1][n], -1});
  while (!myQ.empty()) {
    int qSize = myQ.size();
    while (qSize--) {
      auto [i, j, r, p] = myQ.front();
      myQ.pop();
      printf("%d(p=%d) ", r, p);
      if (r > i)
        myQ.push({i, r - 1, R[i][r - 1], R[i][j]});
      if (r < j)
        myQ.push({r + 1, j, R[r + 1][j], R[i][j]});
    }
    cout << endl;
  }

  exit(0);
}