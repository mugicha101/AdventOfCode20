#include "../template.h"

const int S = 15;
const int64_t DX = 1ULL;
const int64_t DY = 1ULL << S;
const int64_t DZ = 1ULL << S*2;
const int64_t DT = 1ULL << S*3;

inline int64_t key(int x, int y, int z, int t) {
  const int64_t O = 1ULL << S-1;
  return ((int64_t)x + O) | (((int64_t)y + O) << S) | (((int64_t)z + O) << S*2) | (((int64_t)t + O) << S*3);
}

void solve(bool is4d) {
  vector<string> grid(1);
  while (cin >> grid.back()) grid.emplace_back();
  grid.pop_back();

  unordered_set<int64_t> state;

  for (int r = 0; r < grid.size(); ++r) {
    for (int c = 0; c < grid[0].size(); ++c) {
      if (grid[r][c] == '#') state.insert(key(r, c, 0, 0));
    }
  }

  for (int i = 0; i < 6; ++i) {
    unordered_set<int64_t> next;
    auto consider = [&](int64_t s) {
      bool alive = state.count(s);
      int nbs = alive ? -1 : 0;
      for (int8_t dx = -1; dx <= 1; ++dx) {
        for (int8_t dy = -1; dy <= 1; ++dy) {
          for (int8_t dz = -1; dz <= 1; ++dz) {
            for (int8_t dt = -(int8_t)is4d; dt <= (int8_t)is4d; ++dt) {
              nbs += state.count(s + DX * dx + DY * dy + DZ * dz + DT * dt);
            }
          }
        }
      }

      if (alive ? nbs >= 2 && nbs <= 3 : nbs == 3) {
        next.insert(s);
      }
    };
    for (int64_t s : state) {
      for (int8_t dx = -1; dx <= 1; ++dx) {
        for (int8_t dy = -1; dy <= 1; ++dy) {
          for (int8_t dz = -1; dz <= 1; ++dz) {
            for (int8_t dt = -(int8_t)is4d; dt <= (int8_t)is4d; ++dt) {
              consider(s + DX * dx + DY * dy + DZ * dz + DT * dt);
            }
          }
        }
      }
    }
    swap(next, state);
  }
  cout << state.size() << endl;
}

void partA() {
  solve(false);
}

void partB() {
  solve(true);
}

