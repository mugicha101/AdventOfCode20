#include "../template.h"

void partA() {
  string s; cin >> s;
  deque<int> a; for (char c : s) a.push_back(c-'0');
  auto rotLeft = [&]() {
    a.push_back(a.front());
    a.pop_front();
  };
  auto rotRight = [&]() {
    a.push_front(a.back());
    a.pop_back();
  };
  for (int i = 0; i < 100; ++i) {
    int curr = a[0];
    rotLeft();
    int x = a[0];
    int y = a[1];
    int z = a[2];
    a.pop_front();
    a.pop_front();
    a.pop_front();
    int target = curr == 1 ? 9 : curr - 1;
    while (target == x || target == y || target == z) target = target == 1 ? 9 : target - 1;
    while (a.back() != target) rotLeft();
    a.push_front(z);
    a.push_front(y);
    a.push_front(x);
    while (a.back() != curr) rotLeft();
  }
  while (a.back() != 1) rotLeft();
  a.pop_back();
  for (int x : a) cout << x;
  cout << endl;
}

void partB() {
  string s; cin >> s;

  // linked list
  const int C = 1000000;
  static int next[C+1];
  for (int i = 0; i < s.size()-1; ++i) next[s[i]-'0'] = s[i+1]-'0';
  next[s.back()-'0'] = 10;
  for (int x = 10; x < C; ++x) next[x] = x+1;
  next[C] = s.front()-'0';
  int curr = s[0]-'0';
  for (int _ = 0; _ < 10000000; ++_) {
    int x = next[curr];
    int y = next[x];
    int z = next[y];
    int target = curr == 1 ? C : curr - 1;
    while (target == x || target == y || target == z) target = target == 1 ? C : target - 1;
    int t = next[z];
    next[curr] = next[z];
    next[z] = next[target];
    next[target] = x;
    curr = t;
  }
  ll a = next[1];
  ll b = next[a];
  cout << a * b << endl;
}

