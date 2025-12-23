#include "../template.h"

vector<int> split(string s) {
  if (s.empty()) return {};
  vector<int> res(1);
  for (char c : s) {
    if (c == ',') res.push_back(0);
    else res.back() = res.back() * 10 + (c-'0');
  }
  return res;
}

void partA() {
  string s;
  auto parseRange = [](string s) -> pair<int,int> {
    int sp = s.find('-');
    return {stoi(s.substr(0, sp)), stoi(s.substr(sp+1))};
  };
  vector<pair<int,int>> ranges;
  while (getline(cin, s), !s.empty()) {
    int colon = s.find(':');
    int split = s.find(" or ");
    ranges.push_back(parseRange(s.substr(colon+2, split-colon-2)));
    ranges.push_back(parseRange(s.substr(split+4)));
  }

  for (int i = 0; i < 4; ++i) getline(cin, s);
  int res = 0;
  while (getline(cin, s)) {
    vector<int> t = split(s);
    for (int x : t) {
      bool valid = false;
      for (int i = 0; !valid && i < ranges.size(); ++i) {
        valid = ranges[i].first <= x && ranges[i].second >= x;
      }
      if (!valid) res += x;
    }
  }
  cout << res << endl;
}

bool dfs(const vector<vector<bool>> &valid, const vector<int> &order, vector<int> &mapping, vector<bool> &used, int i) {
  int n = mapping.size();
  if (i == n) return true;

  for (int j = 0; j < n; ++j) {
    if (used[j] || !valid[i][j]) continue;

    used[j] = true;
    mapping[i] = j;
    if (dfs(valid, order, mapping, used, i+1)) return true;
    used[j] = false;
  }
  return false;
}

void partB() {
  string s;
  auto parseRange = [](string s) -> pair<int,int> {
    int sp = s.find('-');
    return {stoi(s.substr(0, sp)), stoi(s.substr(sp+1))};
  };
  vector<array<pair<int,int>,2>> ranges;
  vector<string> names;
  while (getline(cin, s), !s.empty()) {
    int colon = s.find(':');
    int split = s.find(" or ");
    ranges.push_back({parseRange(s.substr(colon+2, split-colon-2)), parseRange(s.substr(split+4))});
    names.push_back(s.substr(0, colon));
  }
  int n = ranges.size();
  vector<vector<bool>> valid(n, vector<bool>(n, true)); // valid[i][j] = true iff label i valid for all field j

  getline(cin, s);
  getline(cin, s);
  vector<int> yt = split(s);

  getline(cin, s);
  getline(cin, s);
  
  auto handleTicket = [&](const vector<int> &t) {
    // for each field, determine which labels it's invalid for
    // if ticket contains field with no valid labels, ticket is thrown out
    vector<vector<int>> invalid(t.size()); // invalid[i] contains all labels j for which i is invalid
    bool invalidTicket = false;
    for (int i = 0; !invalidTicket && i < t.size(); ++i) {
      int x = t[i];
      for (int j = 0; j < n; ++j) {
        if ((ranges[j][0].first <= x && ranges[j][0].second >= x) || (ranges[j][1].first <= x && ranges[j][1].second >= x)) continue;

        invalid[i].push_back(j);
      }
      invalidTicket = invalid[i].size() == n;
    }
    if (invalidTicket) return;

    // if field not valid for label, remove it from that labels possible fields
    for (int i = 0; i < t.size(); ++i) {
      for (int l : invalid[i]) {
        valid[l][i] = false;
      }
    }
  };
  handleTicket(yt);
  while (getline(cin, s)) {
    vector<int> t = split(s);
    handleTicket(t);
  }
  
  // handle smallest options first
  vector<int> numValid(n);
  for (int i = 0; i < n; ++i) {
    numValid[i] = accumulate(valid[i].begin(), valid[i].end(), 0);
  }
  vector<int> order(n);
  iota(all(order), 0);
  sort(all(order), [&](int i, int j) {
    return numValid[i] < numValid[j];
  });
  vector<bool> used(n, false);
  vector<int> mapping(n); // label -> field
  assert(dfs(valid, order, mapping, used, 0));
  
  ll res = 1;
  for (int i = 0; i < n; ++i) {
    if (!(names[i].size() >= 9 && names[i].substr(0, 9) == "departure")) continue;

    res *= yt[mapping[i]];
  }
  cout << res << endl;
}

