#include "../template.h"

ll trans(ll sn, int loop) {
  ll v = 1;
  for (int i = 0; i < loop; ++i) {
    v = (v * sn) % 20201227LL;
  }
  return v;
}

ll calcPK(ll sk) {
  return trans(7LL, sk);
}

ll bashSK(ll pk) {
  ll sk = 0;
  ll v = 1;
  while (v != pk) {
    v = (v * 7) % 20201227LL;
    ++sk;
  }
  return sk;
}

void partA() {
  ll a, b; cin >> a >> b;
  ll skA = bashSK(a);
  ll enc = trans(b, skA);
  cout << enc << endl;
}

void partB() {
  partA();
}

