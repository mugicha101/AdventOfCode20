#include "../template.h"

void partA() {
  string s;
  getline(cin, s);
  deque<int> a, b;
  while (getline(cin, s) && !s.empty()) {
    a.push_back(stoi(s));
  }
  getline(cin, s);
  while (getline(cin, s) && !s.empty()) {
    b.push_back(stoi(s));
  }

  while (!(a.empty() || b.empty())) {
    int va = a.front(); a.pop_front();
    int vb = b.front(); b.pop_front();
    if (va > vb) {
      a.push_back(va);
      a.push_back(vb);
    } else {
      b.push_back(vb);
      b.push_back(va);
    }
  }
  if (!b.empty()) swap(a, b);
  int m = 0;
  int res = 0;
  while (!a.empty()) {
    res += a.back() * ++m;
    a.pop_back();
  }
  cout << res << endl;
}

// return true if a wins
bool rec(deque<int> &a, deque<int> &b) {
  set<string> seen;
  string key(a.size() + b.size() + 1, '.');
  while (!(a.empty() || b.empty())) {
    for (int i = 0; i < a.size(); ++i) {
      key[i] = a[i];
    }
    key[a.size()] = 0;
    for (int i = 0; i < b.size(); ++i) {
      key[a.size()+1+i] = b[i];
    }
    if (seen.count(key)) return true;
    seen.insert(key);

    int va = a.front(); a.pop_front();
    int vb = b.front(); b.pop_front();
    bool awins = va > vb;
    if (va <= a.size() && vb <= b.size()) {
      deque<int> na; for (int i = 0; i < va; ++i) na.push_back(a[i]);
      deque<int> nb; for (int i = 0; i < vb; ++i) nb.push_back(b[i]);
      awins = rec(na, nb);
    }
    if (awins) {
      a.push_back(va);
      a.push_back(vb);
    } else {
      b.push_back(vb);
      b.push_back(va);
    }
  }
  return b.empty();
}

void partB() {
  string s;
  getline(cin, s);
  deque<int> a, b;
  while (getline(cin, s) && !s.empty()) {
    a.push_back(stoi(s));
  }
  getline(cin, s);
  while (getline(cin, s) && !s.empty()) {
    b.push_back(stoi(s));
  }
  rec(a, b);
  if (!b.empty()) swap(a, b);
  int m = 0;
  int res = 0;
  while (!a.empty()) {
    res += a.back() * ++m;
    a.pop_back();
  }
  cout << res << endl;
}

