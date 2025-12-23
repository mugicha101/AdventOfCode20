#include "../template.h"

bool dfs(const vector<vector<vector<int>>> &adj, const vector<char> &val, const string &s, vector<vector<vector<char>>> &memo, int curr, int start, int end) {
  assert(start < end);

  // in input, each transition is x <= 3 or 2|2
  // chars are binary
  // dp[i][j][k] = true iff s[j..<k] matches rule i
  // dp[i][j][k] = true iff for some rule r with [a, b] exists dp[a][j][l] && dp[b][l+1][k]
  // cout << curr << " " << start << " " << end << endl;
  if (val[curr] != '-') return end-start == 1 && s[start] == val[curr];
  assert(memo[curr][start][end] != 3);
  if (memo[curr][start][end] != 2) return memo[curr][start][end];

  memo[curr][start][end] = 3;
  const vector<vector<int>> &trans = adj[curr];
  for (const auto &t : trans) {
    assert(t.size() <= 3);
    if (t.size() == 1) {
      // forward seg
      if (dfs(adj, val, s, memo, t[0], start, end)) {
        return memo[curr][start][end] = 1;
      }
    } else if (t.size() == 2) {
      // split seg in 2
      for (int div = start+1; div < end; ++div) {
        if (dfs(adj, val, s, memo, t[0], start, div) && dfs(adj, val, s, memo, t[1], div, end)) {
          return memo[curr][start][end] = 1;
        }
      }
    } else {
      // split seg in 3
      for (int div1 = start+1; div1 < end; ++div1) {
        if (!dfs(adj, val, s, memo, t[0], start, div1)) continue;
        
        for (int div2 = div1+1; div2 < end; ++div2) {
          if (dfs(adj, val, s, memo, t[1], div1, div2) && dfs(adj, val, s, memo, t[2], div2, end)) {
            return memo[curr][start][end] = 1;
          }
        }
      }
    }
  }

  return memo[curr][start][end] = 0;
}

void getRules(vector<char> &val, vector<vector<vector<int>>> &adj) {
  auto resize = [&](int i) {
    while (i >= adj.size()) {
      val.push_back('-');
      adj.emplace_back();
    }
  };

  string s;
  while (getline(cin, s), !s.empty()) {
    int colon = s.find(':');
    int src = stoi(s.substr(0, colon));
    resize(src);
    size_t q = s.find('"');
    if (q != string::npos) {
      val[src] = s[q+1];
      continue;
    }

    adj[src].emplace_back();
    for (int i = colon+2; i < s.size(); ++i) {
      if (s[i] == ' ') continue;
      if (s[i] == '|') {
        adj[src].emplace_back();
        continue;
      }
      if (s[i] < '0' || s[i] > '9') continue;

      int dst = 0;
      while (s[i] >= '0' && s[i] <= '9') {
        dst = dst * 10 + (s[i++] - '0');
      }
      adj[src].back().push_back(dst);
    }
  }
}

void partA() {
  vector<char> val;
  vector<vector<vector<int>>> adj;
  getRules(val, adj);

  string s;
  int res = 0;
  int n = adj.size();
  while (getline(cin, s)) {
    int m = s.size();
    vector<vector<vector<char>>> memo(n, vector<vector<char>>(m, vector<char>(m+1, 2)));
    res += dfs(adj, val, s, memo, 0, 0, s.size());
  }
  cout << res << endl;
}

void partB() {
  vector<char> val;
  vector<vector<vector<int>>> adj;
  getRules(val, adj);

  adj[8] = {{42}, {42, 8}};
  adj[11] = {{42, 31}, {42, 11, 31}};

  string s;
  int res = 0;
  int n = adj.size();
  while (getline(cin, s)) {
    int m = s.size();
    vector<vector<vector<char>>> memo(n, vector<vector<char>>(m, vector<char>(m+1, 2)));
    res += dfs(adj, val, s, memo, 0, 0, s.size());
  }
  cout << res << endl;
}

