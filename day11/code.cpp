#include "../template.h"

void partA() {
  vector<string> grid(1);
  while (cin >> grid.back()) grid.emplace_back();
  grid.pop_back();
  int rows = grid.size();
  int cols = grid[0].size();
  vector<string> next = grid;
  bool changed = true;
  int occ = 0;
  while (changed) {
    changed = false;
    occ = 0;
    for (int r = 0; r < rows; ++r) {
      for (int c = 0; c < cols; ++c) {
        if (grid[r][c] == '.') continue;
        next[r][c] = grid[r][c];
        int nbs = -(int)(grid[r][c] == '#');
        for (int dr = max(r-1, 0); dr <= min(r+1, rows-1); ++dr) {
          for (int dc = max(c-1, 0); dc <= min(c+1, cols-1); ++dc) {
            nbs += grid[dr][dc] == '#';
          }
        }
        if (grid[r][c] == 'L' && nbs == 0) {
          changed = true;
          next[r][c] = '#';
        }
        if (grid[r][c] == '#' && nbs >= 4) {
          changed = true;
          next[r][c] = 'L';
        }
        occ += next[r][c] == '#';
      }
    }
    swap(next, grid);
  }
  cout << occ << endl;
}

void partB() {
  vector<string> grid(1);
  while (cin >> grid.back()) grid.emplace_back();
  grid.pop_back();
  int rows = grid.size();
  int cols = grid[0].size();
  vector<string> next = grid;
  bool changed = true;
  int occ = 0;
  while (changed) {
    changed = false;
    occ = 0;
    for (int r = 0; r < rows; ++r) {
      for (int c = 0; c < cols; ++c) {
        if (grid[r][c] == '.') continue;

        next[r][c] = grid[r][c];
        int nbs = 0;
        for (int dr = -1; dr <= 1; ++dr) {
          for (int dc = -1; dc <= 1; ++dc) {
            if (dr == 0 && dc == 0) continue;

            int nr = r+dr;
            int nc = c+dc;
            while (nr >= 0 && nc >= 0 && nr < rows && nc < cols && grid[nr][nc] == '.') {
              nr += dr;
              nc += dc;
            }
            nbs += nr >= 0 && nc >= 0 && nr < rows && nc < cols && grid[nr][nc] == '#';
          }
        }
        if (grid[r][c] == 'L' && nbs == 0) {
          changed = true;
          next[r][c] = '#';
        }
        if (grid[r][c] == '#' && nbs >= 5) {
          changed = true;
          next[r][c] = 'L';
        }
        occ += next[r][c] == '#';
      }
    }
    swap(next, grid);
  }
  cout << occ << endl;
}

