#include "../template.h"

void partA() {
  string s;
  int res = 0;
  while (cin >> s) {
    int r = 0;
    for (int i = 0; i < 7; ++i) {
      if (s[i] == 'B') r += (64 >> i);
    }
    int c = 0;
    for (int i = 0; i < 3; ++i) {
      if (s[i+7] == 'R') c += (4 >> i);
    }
    int id = r * 8 + c;
    res = max(res, id);
  }
  cout << res << endl;
}

void partB() {
  string s;
  vector<uint8_t> seats(128);
  while (cin >> s) {
    int r = 0;
    for (int i = 0; i < 7; ++i) {
      if (s[i] == 'B') r += (64 >> i);
    }
    int c = 0;
    for (int i = 0; i < 3; ++i) {
      if (s[i+7] == 'R') c += (4 >> i);
    }
    seats[r] |= (uint8_t)1 << c;
  }
  int r = 0;
  while (seats[r++] == 0);
  while (seats[++r] == 0b11111111);
  int c = 0;
  while ((seats[r] >> c) & 1) ++c;
  cout << r * 8 + c << endl;
}

