#include "../template.h"

void partA() {
  string s;
  int res = 0;
  while (getline(cin, s)) {
    int dash = s.find('-');
    int col = s.find(':');
    int cnt = 0;
    int lo = stoi(s.substr(0, dash));
    int hi = stoi(s.substr(dash+1, col-dash-3));
    char t = s[col-1];
    for (int i = col+1; i < s.size(); ++i) {
      cnt += s[i] == t;
    }
    res += cnt >= lo && cnt <= hi;
  }
  cout << res << endl;
}

void partB() {

  string s;
  int res = 0;
  while (getline(cin, s)) {
    int dash = s.find('-');
    int col = s.find(':');
    int cnt = 0;
    int a = stoi(s.substr(0, dash));
    int b = stoi(s.substr(dash+1, col-dash-3));
    char t = s[col-1];
    res += s[col+a+1] == t ^ s[col+b+1] == t;
  }
  cout << res << endl;
}

