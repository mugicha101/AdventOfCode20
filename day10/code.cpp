#include "../template.h"

vector<int> getInput() {
  vector<int> input(1);
  while (cin >> input.back()) input.emplace_back();
  input.back() = 0;
  sort(all(input));
  input.push_back(input.back() + 3);
  return input;
}

void partA() {
  vector<int> input = getInput();
  int d[4] = {};
  for (int i = 1; i < input.size(); ++i) {
    ++d[input[i] - input[i-1]];
  }
  cout << d[1] * d[3] << endl;
}

void partB() {
  vector<int> input = getInput();
  vector<ll> dp(input.size());
  dp[0] = 1;
  for (int i = 0; i < input.size(); ++i) {
    for (int j = i+1; j < input.size() && input[j] - input[i] <= 3; ++j) {
      dp[j] += dp[i];
    }
  }
  cout << dp.back() << endl;
}

