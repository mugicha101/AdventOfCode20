#include "../template.h"

void solve(bool isB) {
  // for allergen a
  // if a in rhs, must be in lhs
  // thus intersection of all foods with a gives candidates for a
  // if a mapped to unique ingredient i, found its mapping, remove all instances of a and i
  // repeat until no more changes
  vector<set<string>> ingr; // ingr[i] = ingredients of food i
  vector<set<string>> aller; // aller[i] = listed allergens of food i
  set<string> allIngr;
  set<string> allAller;
  string s;
  while (getline(cin, s)) {
    ingr.emplace_back();
    aller.emplace_back();
    int del = s.find('(');
    int j = 0;
    for (int i = 0; i < del; ++i) {
      if (s[i] == ' ') {
        string ig = s.substr(j, i-j);
        ingr.back().insert(ig);
        allIngr.insert(ig);
        j = i+1;
      }
    }
    j = del+10;
    for (int i = del+10; i < s.size(); ++i) {
      if (s[i] == ',' || s[i] == ' ' || s[i] == ')') {
        if (i > j) {
          string al = s.substr(j, i-j);
          aller.back().insert(al);
          allAller.insert(al);
        }
        j = i+1;
      }
    }
  }
  bool changed = true;
  int n = ingr.size();
  vector<pair<string,string>> mappings;
  int next = 0;
  while (true) {
    for (string al : allAller) {
      queue<string> cand;
      for (string ig : allIngr) cand.push(ig);
      for (int i = 0; i < n; ++i) {
        if (!aller[i].count(al)) continue;

        for (int qi = cand.size(); qi > 0; --qi) {
          string ig = cand.front();
          cand.pop();
          if (ingr[i].count(ig)) cand.push(ig);
        }
      }
      if (cand.size() > 1) continue;
      mappings.emplace_back(cand.front(), al);
    }
    if (next == mappings.size()) break;

    while (next < mappings.size()) {
      for (auto &s : ingr) s.erase(mappings[next].first);
      for (auto &s : aller) s.erase(mappings[next].second);
      allIngr.erase(mappings[next].first);
      allAller.erase(mappings[next].second);
      ++next;
    }
  }
  if (!isB) {
    int res = 0;
    for (int i = 0; i < n; ++i) {
      assert(aller[i].empty());
      res += ingr[i].size();
    }
    cout << res << endl;
    return;
  }

  sort(mappings.begin(), mappings.end(), [](auto &a, auto &b) {
    return a.second < b.second;
  });
  cout << mappings[0].first;
  for (int i = 1; i < mappings.size(); ++i) {
    cout << "," << mappings[i].first;
  }
  cout << endl;
}

void partA() {
  solve(false);
}

void partB() {
  solve(true);
}

