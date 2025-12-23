#define _USE_MATH_DEFINES
#include <bits/extc++.h>
#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono_literals;

// using namespace __gnu_pbds;
// template <class T>
// using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,
// tree_order_statistics_node_update>; template <class T> using ordered_multiset
// = tree<T, null_type, less_equal<T>, rb_tree_tag,
// tree_order_statistics_node_update>;

#define MOD 998244353
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

typedef unsigned int uint;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

const ld ROT_HALF = 3.14159265358979323846L;
const ld ROT_FULL = ROT_HALF * 2.L;
const ld ROT_QUARTER = ROT_HALF * 0.5L;

template <typename T, typename U>
pair<T, U> operator+(const pair<T, U>& l, const pair<T, U>& r) {
  return {l.first + r.first, l.second + r.second};
}
template <typename T, typename U>
pair<T, U> operator-(const pair<T, U>& l, const pair<T, U>& r) {
  return {l.first - r.first, l.second - r.second};
}
template <typename A, typename B>
ostream& operator<<(ostream& os, const pair<A, B>& p) {
  return os << '(' << p.first << ", " << p.second << ')';
}
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
  os << "[";
  for (size_t i = 0; i < v.size(); ++i) {
    os << v[i];
    if (i != v.size() - 1) os << ", ";
  }
  os << "]";
  return os;
}

const ll INF = LLONG_MAX >> 2;

#define EPS 1e-9
#define each(i, x) for (auto& i : x)
#define vcin(x) \
  for (auto& _e : x) cin >> _e;
#define mp(a, b) make_pair(a, b)
#define pause() this_thread::sleep_for(10ms)

using ui = __uint128_t;
using bi = __int128_t;

template<typename T>
string i2s(T v) {
  string res;
  while (v) {
    res += ('0' + (char)(v % 10));
    v /= 10;
  }
  reverse(all(res));
  if (res.empty()) res += '0';
  return res;
}
