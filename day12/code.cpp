#include "../template.h"

void partA() {
  int dx = 1;
  int dy = 0;
  int x = 0;
  int y = 0;
  string s;
  while (cin >> s) {
    char d = s[0];
    int v = stoi(s.substr(1));
    switch (d) {
      case 'F': x += dx * v; y += dy * v; break;
      case 'N': y += v; break;
      case 'S': y -= v; break;
      case 'E': x += v; break;
      case 'W': x -= v; break;
      case 'L': while (v) { int t = dx; dx = -dy; dy = t; v -= 90; }
      case 'R': while (v) { int t = dx; dx = dy; dy = -t; v -= 90; }
    }
  }
  cout << abs(x) + abs(y) << endl;
}

void partB() {
  int x = 10;
  int y = 1;
  int sx = 0;
  int sy = 0;
  string s;
  while (cin >> s) {
    char d = s[0];
    int v = stoi(s.substr(1));
    switch (d) {
      case 'F': sx += x * v; sy += y * v; break;
      case 'N': y += v; break;
      case 'S': y -= v; break;
      case 'E': x += v; break;
      case 'W': x -= v; break;
      case 'L': while (v) { int t = x; x = -y; y = t; v -= 90; }
      case 'R': while (v) { int t = x; x = y; y = -t; v -= 90; }
    }
  }
  cout << abs(sx) + abs(sy) << endl;
}

