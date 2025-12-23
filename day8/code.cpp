#include "../template.h"

pair<int,int> sim(const vector<pair<int,int>> &il) {
  int ip = 0;
  int v = 0;
  vector<bool> seen(il.size());
  while (ip < il.size() && !seen[ip]) {
    seen[ip] = true;
    auto [id, x] = il[ip];
    switch (id) {
      case 0: {
        v += x;
        ++ip;
      } break;
      case 1: {
        ip += x;
      } break;
      case 2: {
        ++ip;
      } break;
    }
  }
  return {v, ip};
}

vector<pair<int,int>> input() {
  vector<pair<int,int>> il;
  string s;
  while (getline(cin, s)) {
    int sp = s.find(' ');
    string type = s.substr(0, sp);
    int id = type == "acc" ? 0 : type == "jmp" ? 1 : 2;
    il.emplace_back(id, stoi(s.substr(sp+2)) * (s[sp+1] == '-' ? -1 : 1));
  }
  return il;
}

void partA() {
  vector<pair<int,int>> il = input();
  cout << sim(il).first << endl;
}

void partB() {
  vector<pair<int,int>> il = input();
  for (auto &[id, x] : il) {
    if (id == 0) continue;

    id = 3 - id;
    auto [v, ip] = sim(il);
    if (ip == il.size()) {
      cout << v << endl;
      return;
    }
    id = 3 - id;
  }
}

