#include "../template.h"

set<pair<int,int>> getInput() {
  // represent hex as just alternating grid
  string s;
  set<pair<int,int>> black;
  while (getline(cin, s)) {
    int x = 0;
    int y = 0;
    for (int i = 0; i < s.size(); ++i) {
      if (s[i] == 'e') {
        x += 2;
      } else if (s[i] == 'w') {
        x -= 2;
      } else {
        y += s[i] == 'n' ? 1 : -1;
        x += s[++i] == 'e' ? 1 : -1;
      }
    }
    pair<int,int> p = {x,y};
    if (black.count(p)) black.erase(p);
    else (black.insert(p));
  }
  return black;
}

void partA() {
  set<pair<int,int>> black = getInput();
  cout << black.size() << endl;
}

void partB() {
  set<pair<int,int>> black = getInput();
  for (int i = 0; i < 100; ++i) {
    set<pair<int,int>> next;

    auto consider = [&](int x, int y) {
      int nbs = black.count({x-2,y}) + black.count({x+2,y}) + black.count({x-1,y-1}) + black.count({x+1,y-1}) + black.count({x-1,y+1}) + black.count({x+1,y+1});
      if (black.count({x,y}) ? nbs >= 1 && nbs <= 2 : nbs == 2) {
        next.insert({x,y});
      }
    };
    
    for (auto &[x, y] : black) {
      consider(x-2,y);
      consider(x+2,y);
      consider(x-1,y-1);
      consider(x+1,y-1);
      consider(x-1,y+1);
      consider(x+1,y+1);
    }
    swap(next, black);
    cout << black.size() << endl;
  }
}

