#include "../template.h"

void partA() {
  string s; getline(cin, s);
  vector<int> vals(1);
  for (char c : s) {
    if (c == ',') vals.push_back(0);
    else vals.back() = vals.back() * 10 + (c-'0');
  }

  int turn;
  unordered_map<int,int> last;
  for (turn = 0; turn < vals.size(); ++turn) {
    last[vals[turn]] = turn;
  }
  int x = 0;
  while (turn < 2019) {
    auto it = last.find(x);
    int t = it == last.end() ? 0 : turn - last[x];
    last[x] = turn++;
    x = t;
  }
  cout << x << endl;
}

void partB() {
  string s; getline(cin, s);
  vector<int> vals(1);
  for (char c : s) {
    if (c == ',') vals.push_back(0);
    else vals.back() = vals.back() * 10 + (c-'0');
  }

  int turn;
  unordered_map<int,int> last;
  for (turn = 0; turn < vals.size(); ++turn) {
    last[vals[turn]] = turn;
  }
  int x = 0;
  while (turn < 30000000-1) {
    auto it = last.find(x);
    int t = it == last.end() ? 0 : turn - last[x];
    last[x] = turn++;
    x = t;
  }
  cout << x << endl;
}

