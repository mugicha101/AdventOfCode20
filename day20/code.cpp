#include "../template.h"

int n, m;

uint16_t flip(uint16_t x) {
  uint16_t t = 0;
  for (int i = 0; i < m; ++i) {
    t |= ((x >> i) & 1) << (m-1-i);
  }
  return t;
}

struct Edge {
  int nid = -1; // neighbor tile
  uint16_t v = 0; // value
  void fl() {
    v = flip(v);
  }
};

struct Tile {
  int id;
  array<Edge, 4> edges; // T, R, B, L note: tile order follows clockwise (so bottom is reversed)
  vector<string> grid;
  void rotCCW() {
    auto f = edges[0];
    edges[0] = edges[1];
    edges[1] = edges[2];
    edges[2] = edges[3];
    edges[3] = f;
    vector<string> t = grid;
    for (int r = 0; r < m; ++r) {
      for (int c = 0; c < m; ++c) {
        t[m-c-1][r] = grid[r][c];
      }
    }
    grid = t;
  }
  void flipH() {
    edges[0].fl();
    edges[1].fl();
    edges[2].fl();
    edges[3].fl();
    swap(edges[1], edges[3]);
    for (auto &r : grid) reverse(all(r));
  }
  int nbs() {
    int c = 0;
    for (auto &e : edges) c += e.nid != -1;
    return c;
  }
};

void solve(bool isB) {
  vector<Tile> tiles;
  string s;
  while (getline(cin, s)) {
    s.pop_back();
    tiles.emplace_back();
    Tile &t = tiles.back();
    t.id = stoi(s.substr(s.find(' ') + 1));
    while (getline(cin, s) && !s.empty()) {
      t.grid.push_back(s);
    }
    m = t.grid.size();
    for (int i = 0; i < m; ++i) {
      t.edges[0].v |= (uint16_t)(t.grid[0][i] == '#') << i;
      t.edges[1].v |= (uint16_t)(t.grid[i][m-1] == '#') << i;
      t.edges[2].v |= (uint16_t)(t.grid[m-1][m-1-i] == '#') << i;
      t.edges[3].v |= (uint16_t)(t.grid[m-1-i][0] == '#') << i;
    }
  }

  // by input invariant, each edge only connects to one other edge
  // try all corners, brute force
  // due to rotation and flipping, guaranteed to find solution by putting any corner at top left as long as 0 conn sides point out

  for (int i = 0; i < tiles.size(); ++i) {
    for (auto &a : tiles[i].edges) {
      for (int j = i+1; j < tiles.size(); ++j) {
        for (auto &b : tiles[j].edges) {
          if (a.v == b.v || a.v == flip(b.v)) {
            assert(a.nid == -1 && b.nid == -1);
            a.nid = j;
            b.nid = i;
          }
        }
      }
    }
  }

  n = 1;
  while (n * n < tiles.size()) ++n;
  vector<bool> used(tiles.size());
  vector<vector<int>> board(n, vector<int>(n, -1));

  // find corner
  int cid = 0;
  while (tiles[cid].nbs() != 2) ++cid;
  Tile &corner = tiles[cid];
  while (corner.edges[0].nid != -1 || corner.edges[3].nid != -1) corner.rotCCW();
  board[0][0] = cid;

  // greedy
  for (int r = 0; r < n; ++r) {
    for (int c = 0; c < n; ++c) {
      Tile &t = tiles[board[r][c]];
      if (c == 0 && r+1 < n) {
        board[r+1][c] = t.edges[2].nid;
        assert(board[r+1][c] != -1);
        Tile &u = tiles[board[r+1][c]];
        for (int i = 0; t.edges[2].v != flip(u.edges[0].v) && i < 4; ++i) {
          u.rotCCW();
        }
        if (t.edges[2].v != flip(u.edges[0].v)) {
          u.flipH();
          for (int i = 0; t.edges[2].v != flip(u.edges[0].v) && i < 4; ++i) {
            u.rotCCW();
          }
        }
        assert(t.edges[2].v == flip(u.edges[0].v));
      }
      if (c+1 < n) {
        board[r][c+1] = t.edges[1].nid;
        assert(board[r][c+1] != -1);
        Tile &u = tiles[board[r][c+1]];
        for (int i = 0; t.edges[1].v != flip(u.edges[3].v) && i < 4; ++i) {
          u.rotCCW();
        }
        if (t.edges[1].v != flip(u.edges[3].v)) {
          u.flipH();
          for (int i = 0; t.edges[1].v != flip(u.edges[3].v) && i < 4; ++i) {
            u.rotCCW();
          }
        }
        assert(t.edges[1].v == flip(u.edges[3].v));
      }
    }
  }

  if (!isB) {
    cout << (ll)tiles[board[0][0]].id * (ll)tiles[board[n-1][0]].id * (ll)tiles[board[0][n-1]].id * (ll)tiles[board[n-1][n-1]].id << endl;
    return;
  }

  int l = n * (m-2);
  vector<string> grid(l, string(l, '.'));
  for (int tr = 0; tr < n; ++tr) {
    for (int tc = 0; tc < n; ++tc) {
    auto &g = tiles[board[tr][tc]].grid;
      for (int r = 0; r < m-2; ++r) {
        for (int c = 0; c < m-2; ++c) {
          grid[tr * (m-2) + r][tc * (m-2) + c] = g[r+1][c+1];
        }
      }
    }
  }
  auto rotGrid = [&]() {
    vector<string> t = grid;
    for (int r = 0; r < l; ++r) {
      for (int c = 0; c < l; ++c) {
        t[l-c-1][r] = grid[r][c];
      }
    }
    grid = t;
  };
  const vector<string> mon = {
    "                  # ",
    "#    ##    ##    ###",
    " #  #  #  #  #  #   "
  };
  int mr = mon.size();
  int mc = mon[0].size();
  int cnt = 0;
  auto countMonsters = [&]() {
    for (auto &row : grid) for (char &c : row) if (c == 'O') c = '#';

    cnt = 0;
    for (int r = 0; r <= l-mr; ++r) {
      for (int c = 0; c <= l-mc; ++c) {
        bool valid = true;
        for (int dr = 0; valid && dr < mr; ++dr) {
          for (int dc = 0; valid && dc < mc; ++dc) {
            valid = mon[dr][dc] == ' ' || grid[r+dr][c+dc] != '.';
          }
        }
        if (!valid) continue;

        ++cnt;
        for (int dr = 0; dr < mr; ++dr) {
          for (int dc = 0; dc < mc; ++dc) {
            if (mon[dr][dc] == '#') grid[r+dr][c+dc] = 'O';
          }
        }
      }
    }
  };
  countMonsters();
  for (int i = 0; i < 4 && cnt == 0; ++i) {
    rotGrid();
    countMonsters();
  }
  if (cnt == 0) {
    for (auto &s : grid) reverse(all(s));
    countMonsters();
    for (int i = 0; i < 4 && cnt == 0; ++i) {
      rotGrid();
      countMonsters();
    }
  }
  int res = 0;
  for (auto &s : grid) for (char c : s) res += c == '#';
  cout << res << endl;
}

void partA() {
  solve(false);
}

void partB() {
  solve(true);
}

