#include "../template.h"

enum struct TokenType {
  NUM, PLUS, MULT, LPAREN, RPAREN
};

struct Token {
  TokenType type;
  int val;

  Token(TokenType type, int val = 0) : type(type), val(val) {}
};

vector<Token> tokenize(const string &s) {
  vector<Token> res;
  for (int i = 0; i < s.size(); ++i) {
    if (s[i] == ' ') continue;
    else if (s[i] == '(') res.emplace_back(TokenType::LPAREN);
    else if (s[i] == ')') res.emplace_back(TokenType::RPAREN);
    else if (s[i] == '+') res.emplace_back(TokenType::PLUS);
    else if (s[i] == '*') res.emplace_back(TokenType::MULT);
    else if (s[i] >= '0' && s[i] <= '9') {
      int v = 0;
      while (s[i] >= '0' && s[i] <= '9') {
        v = v * 10 + (s[i] - '0'); ++i;
      }
      --i;
      res.emplace_back(TokenType::NUM, v);
    } else assert(false);
  }
  return res;
}

void partA() {
  string s;
  ll sum = 0;
  while (getline(cin, s)) {
    vector<Token> tokens = tokenize(s);
    stack<pair<ll,bool>> st; // (lhs, op is mult)
    st.emplace(0, false);
    for (const Token &t : tokens) {
      switch (t.type) {
        case TokenType::NUM: st.top().first = st.top().second ? st.top().first * t.val : st.top().first + t.val; break;
        case TokenType::PLUS: case TokenType::MULT: st.top().second = st.top().second = t.type == TokenType::MULT; break;
        case TokenType::LPAREN: st.emplace(0, false); break;
        case TokenType::RPAREN: {
          ll v = st.top().first;
          st.pop();
          st.top().first = st.top().second ? st.top().first * v : st.top().first + v;
        } break;
      }
    }
    ll res = st.top().first;
    sum += res;
  }
  cout << sum << endl;
}

void partB() {
  string s;
  ll sum = 0;
  while (getline(cin, s)) {
    vector<Token> tokens = tokenize(s);
    stack<vector<pair<ll,bool>>> st;
    st.emplace();
    
    // collapse top layer of stack
    // obey precedence
    auto collapse = [&]() {
      auto &l = st.top();
      ll total = 1;
      ll term = 0;
      for (auto &[v, isMult] : st.top()) {
        term += v;
        if (isMult) {
          total *= term;
          term = 0;
        }
      }
      l.clear();
      l.emplace_back(total, true);
    };
    for (const Token &t : tokens) {
      switch (t.type) {
        case TokenType::NUM:
          st.top().emplace_back(t.val, true);
          break;
        case TokenType::PLUS:
        case TokenType::MULT:
          st.top().back().second = st.top().back().second = t.type == TokenType::MULT;
          break;
        case TokenType::LPAREN:
          st.emplace();
          break;
        case TokenType::RPAREN: {
          collapse();
          ll v = st.top().back().first;
          st.pop();
          st.top().emplace_back(v, true);
        } break;
      }
    }
    collapse();
    ll res = st.top().back().first;
    sum += res;
  }
  cout << sum << endl;
}

