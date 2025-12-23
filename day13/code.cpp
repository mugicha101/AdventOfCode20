#include "../template.h"

pair<vector<int>,int> getInput() {
  int t; cin >> t;
  vector<int> bus(1);
  string s; cin >> s;
  for (char c : s) {
    if (c == ',') {
      bus.push_back(0);
    } else if (c == 'x') {
      bus.back() = -1;
    } else {
      bus.back() = bus.back() * 10 + (c-'0');
    }
  }
  return {bus, t};
}

void partA() {
  auto [bus, t] = getInput();
  int bestWait = INT_MAX;
  int bestBus = -1;
  for (int x : bus) {
    if (x == -1) continue;
    
    int wait = x - ((t + x - 1) % x) - 1;
    if (wait >= bestWait) continue;

    bestWait = wait;
    bestBus = x;
  }
  cout << bestBus * bestWait << endl;
}

ui modmul(ui a, ui b, ui c) {
    bi ret = a * b - c * ull(ld(a) * ld(b) / ld(c));
    return ret + c * (ret < 0) - c * (ret >= (bi)c);
}
ui invmod(ui a, ui p) {
    ull ex = p-2, result = 1;
    while (ex > 0) {
        if (ex % 2 == 1) {
            result = (result*a) % p;
        }
        a = (a*a) % p;
        ex /= 2;
    }
    return result;
}

void partB() {
  auto [bus, t] = getInput();
  // given ith bus x (i 0-indexed)
  // t+i mod x = 0 mod x
  // t mod x = -i mod x

  // CRT Chinese Remainder Theorem:
  // given pairwise coprime m_1, m_2, ...
  // find x mod m_1 * m_2 * ... where x mod m_i = a_i mod m_i
  // M = m_1 * m_2 * ...
  // M_i = M / m_i
  // N_i = modinv(M_i mod m_i)
  // x mod M = sum(a_i * M_i * N_i) mod M
  vector<pair<ui,ui>> eqs; // (m, a) where t mod m = a (0 <= a < m)
  for (int i = 0; i < bus.size(); ++i) {
    if (bus[i] == -1) continue;

    int m = bus[i];
    eqs.emplace_back(m, (((-i) % m) + m) % m);
  }
  
  ui M = 1;
  for (auto &[m, a] : eqs) {
    M *= m;
  }
  ui x = 0;
  for (auto &[m, a] : eqs) {
    ui Mi = M / m;
    ui Ni = invmod(Mi, m);
    x = (x + a * Mi * Ni) % M;
  }
  cout << i2s(x) << endl;
}

