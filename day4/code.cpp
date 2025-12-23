#include "../template.h"

void partA() {
  string s;
  vector<vector<pair<string,string>>> ppts(1);
  while (getline(cin, s)) {
    if (s.empty()) {
      ppts.emplace_back();
      continue;
    }

    s += ' ';
    int j = 0;
    for (int i = 0; i < s.size(); ++i) {
      if (s[i] != ' ') continue;

      string seg = s.substr(j, i-j);
      int col = seg.find(':');
      ppts.back().emplace_back(seg.substr(0, col), seg.substr(col+1));
      j = i+1;
    }
  }

  int res = 0;
  for (auto &pp : ppts) {
    set<string> keys;
    for (auto &[k,v] : pp) keys.insert(k);
    res += keys.count("byr") && keys.count("iyr") && keys.count("eyr") && keys.count("hgt") && keys.count("hcl") && keys.count("ecl") && keys.count("pid");
  }
  cout << res << endl;
}

void partB() {
string s;
  vector<vector<pair<string,string>>> ppts(1);
  while (getline(cin, s)) {
    if (s.empty()) {
      ppts.emplace_back();
      continue;
    }

    s += ' ';
    int j = 0;
    for (int i = 0; i < s.size(); ++i) {
      if (s[i] != ' ') continue;

      string seg = s.substr(j, i-j);
      int col = seg.find(':');
      ppts.back().emplace_back(seg.substr(0, col), seg.substr(col+1));
      j = i+1;
    }
  }
  auto isnum = [&](string s) {
    return all_of(s.begin(), s.end(), [](char c) {
      return c >= '0' && c <= '9';
    });
  };
  auto ishex = [&](string s) {
    return all_of(s.begin(), s.end(), [](char c) {
      return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f');
    });
  };
  auto checkHgt = [&](string s) {
    if (s.size() <= 2) return false;
    string numStr = s.substr(0, s.size()-2);
    string unit = s.substr(s.size()-2);
    if (!isnum(numStr)) return false;
    int num = stoi(numStr);
    return unit == "cm" ? num >= 150 && num <= 193 : unit == "in" ? num >= 59 && num <= 76 : false;
  };
  auto checkEcl = [](string s) {
    return s == "amb" || s == "blu" || s == "brn" || s == "gry" || s == "grn" || s == "hzl" || s == "oth";
  };

  int res = 0;
  for (auto &pp : ppts) {
    map<string,string> m;
    for (auto &[k,v] : pp) m[k] = v;
    res += m.count("byr") && isnum(m["byr"]) && stoi(m["byr"]) >= 1920 && stoi(m["byr"]) <= 2002
      && m.count("iyr") && isnum(m["iyr"]) && stoi(m["iyr"]) >= 2010 && stoi(m["iyr"]) <= 2020
      && m.count("eyr") && isnum(m["eyr"]) && stoi(m["eyr"]) >= 2020 && stoi(m["eyr"]) <= 2030
      && m.count("hgt") && checkHgt(m["hgt"])
      && m.count("hcl") && m["hcl"].size() == 7 && m["hcl"][0] == '#' && ishex(m["hcl"].substr(1))
      && m.count("ecl") && checkEcl(m["ecl"])
      && m.count("pid") && m["pid"].size() == 9 && isnum(m["pid"]);
  }
  cout << res << endl;
}

