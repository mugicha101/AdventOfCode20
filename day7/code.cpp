#include "../template.h"

void partA() {
  string s;
  unordered_map<string, int> idMap;
  vector<vector<pair<int,int>>> inv;
  auto getId = [&](string s) {
    auto it = idMap.find(s);
    if (it == idMap.end()) {
      inv.emplace_back();
      return idMap[s] = idMap.size();
    } else {
      return it->second;
    }
  };

  while (getline(cin, s)) {
    int delim = s.find(" bags contain ");
    int src = getId(s.substr(0, delim));
    s = s.substr(delim + 14);
    if (s == "no other bags.") continue;

    s.back() = ',';
    int j = 0;
    for (int i = 0; i < s.size(); ++i) {
      if (s[i] != ',') continue;

      string seg = s.substr(j, i-j);
      j = i+2;

      int sp = seg.find(' ');
      int amt = stoi(seg.substr(0, sp));
      int dst = getId(seg.substr(sp+1, seg.size()-sp-(seg.back() == 's')-5));

      inv[dst].emplace_back(src, amt);
    }
  }

  queue<int> q;
  vector<bool> visited(idMap.size());
  q.push(getId("shiny gold"));
  int res = 0;
  while (!q.empty()) {
    int curr = q.front(); q.pop();
    ++res;
    for (auto [next, _] : inv[curr]) {
      if (visited[next]) continue;
      visited[next] = true;
      q.push(next);
    }
  }
  cout << res-1 << endl;
}

void partB() {
  string s;
  unordered_map<string, int> idMap;
  vector<vector<pair<int,int>>> adj;
  vector<int> indeg;
  auto getId = [&](string s) {
    auto it = idMap.find(s);
    if (it == idMap.end()) {
      adj.emplace_back();
      indeg.push_back(0);
      return idMap[s] = idMap.size();
    } else {
      return it->second;
    }
  };

  while (getline(cin, s)) {
    int delim = s.find(" bags contain ");
    int src = getId(s.substr(0, delim));
    s = s.substr(delim + 14);
    if (s == "no other bags.") continue;

    s.back() = ',';
    int j = 0;
    for (int i = 0; i < s.size(); ++i) {
      if (s[i] != ',') continue;

      string seg = s.substr(j, i-j);
      j = i+2;

      int sp = seg.find(' ');
      int amt = stoi(seg.substr(0, sp));
      int dst = getId(seg.substr(sp+1, seg.size()-sp-(seg.back() == 's')-5));

      adj[src].emplace_back(dst, amt);
      ++indeg[dst];
    }
  }

  queue<int> q;
  vector<ll> cnt(idMap.size());
  int t = getId("shiny gold");
  cnt[t] = 1;
  for (int i = 0; i < idMap.size(); ++i) {
    if (indeg[i] == 0) q.push(i);
  }
  while (!q.empty()) {
    int curr = q.front(); q.pop();
    for (auto [next, amt] : adj[curr]) {
      cnt[next] += cnt[curr] * amt;
      if (--indeg[next]) continue;
      q.push(next);
    }
  }
  cout << accumulate(cnt.begin(), cnt.end(), 0LL)-1 << endl;
}

