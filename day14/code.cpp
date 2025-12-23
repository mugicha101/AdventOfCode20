#include "../template.h"

void partA() {
  string mask(36, '0');
  unordered_map<ll,ll> mem;
  string s;
  while (getline(cin, s)) {
    int eq = s.find("=");
    if (s.substr(0, 3) == "mem") {
      int idx = stoi(s.substr(4, eq-6));
      ll v = stoll(s.substr(eq+2));
      ll r = 0;
      for (int i = 0; i < 36; ++i) {
        switch (mask[35-i]) {
          case 'X': r |= (v & (1LL << i)); break;
          case '1': r |= 1LL << i; break;
        }
      }
      mem[idx] = r;
    } else {
      mask = s.substr(eq+2);
    }
  }
  ll sum = 0;
  for (auto &[k,v] : mem) {
    sum += v;
  }
  cout << sum << endl;
}

void asn(unordered_map<ll,ll> &mem, const string &mask, ll val, ll idx, int i) {
  if (i == 36) {
    mem[idx] = val;
    return;
  }

  char m = mask[35-i];
  if (m == 'X') {
    asn(mem, mask, val, idx, i+1);
    asn(mem, mask, val, idx ^ (1LL << i), i+1);
  } else if (m == '1') {
    asn(mem, mask, val, idx | (1LL << i), i+1);
  } else {
    asn(mem, mask, val, idx, i+1);
  }
}

void partB() {
  string mask(36, '0');
  unordered_map<ll,ll> mem;
  string s;
  while (getline(cin, s)) {
    int eq = s.find("=");
    if (s.substr(0, 3) == "mem") {
      int idx = stoi(s.substr(4, eq-6));
      ll v = stoll(s.substr(eq+2));
      asn(mem, mask, v, idx, 0);
    } else {
      mask = s.substr(eq+2);
    }
  }
  ll sum = 0;
  for (auto &[k,v] : mem) {
    sum += v;
  }
  cout << sum << endl;
}

