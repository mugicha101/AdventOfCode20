#include "../template.h"

void partA() {
  string s;
  int p = 0;
  int res = 0;
  while (cin >> s) {
    res += s[p] == '#';
    p = (p + 3) % s.size();
  }
  cout << res << endl;
}

void partB() {
  vector<string> grid(1);
  while (cin >> grid.back()) grid.emplace_back();
  grid.pop_back();
  int rows = grid.size();
  int cols = grid[0].size();
  auto check = [&](int dr, int dc) -> ll {
    int r = 0;
    int c = 0;
    int res = 0;
    while (r < rows && c < cols) {
      res += grid[r][c] == '#';
      r += dr;
      c = (c + dc) % cols;
    }
    return res;
  };
  ll res = check(1, 1) * check(1, 3) * check(1, 5) * check(1, 7) * check(2, 1);
  cout << res << endl;
}

