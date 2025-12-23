#include "../template.h"

void partA() {
  string s;
  bitset<26> qs;
  int res = 0;
  while (getline(cin, s)) {
    if (s.empty()) {
      qs.reset();
      continue;
    }
    for (char c : s) {
      res += !qs[c-'a'];
      qs[c-'a'] = true;
    }
  }
  cout << res << endl;
}

void partB() {
  string s;
  int qs[26] = {};
  int gsize = 0;
  int res = 0;
  auto handleGroup = [&]() {
    for (int v : qs) {
      res += v == gsize;
    }
  };
  while (getline(cin, s)) {
    if (s.empty()) {
      handleGroup();
      memset(qs, 0, sizeof(qs));
      gsize = 0;
      continue;
    }
    for (char c : s) ++qs[c-'a'];
    ++gsize;
  }
  handleGroup();
  cout << res << endl;
}

