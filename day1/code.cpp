#include "../template.h"

void partA() {
  unordered_set<int> s;
  int x;
  int v;
  while (cin >> x) {
    if (s.count(2020-x)) {
      v = x;
    }
    s.insert(x);
  }
  cout << v * (2020-v) << endl;
}

void partB() {
  int x;
  vector<int> vals;
  while (cin >> x) {
    vals.push_back(x);
  }
  int n = vals.size();
  for (int i = 0; i < n; ++i) {
    for (int j = i+1; j < n; ++j) {
      for (int k = j+1; k < n; ++k) {
        if (vals[i] + vals[j] + vals[k] == 2020) {
          cout << (ll)vals[i] * (ll)vals[j] * (ll)vals[k] << endl;
          return;
        }
      }
    }
  }
}

