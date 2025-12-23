#include "../template.h"

vector<int> getInput() {
  vector<int> input(1);
  while (cin >> input.back()) input.push_back(0);
  input.pop_back();
  return input;
}

int findInvalid(const vector<int> &input) {
  for (int i = 25; i < input.size(); ++i) {
    unordered_set<int> seen;
    bool valid = false;
    for (int j = i-25; !valid && j < i; ++j) {
      valid = seen.count(input[i] - input[j]);
      seen.insert(input[j]);
    }
    if (!valid) return input[i];
  }
  return -1;
}

void partA() {
  vector<int> input = getInput();
  cout << findInvalid(input) << endl;
}

void partB() {
  vector<int> input = getInput();
  int t = findInvalid(input);
  for (int i = 0; i < input.size(); ++i) {
    int sum = input[i];
    pair<int,int> bound = {sum, sum};
    for (int j = i+1; j < input.size() && sum < t; ++j) {
      sum += input[j];
      bound.first = min(bound.first, input[j]);
      bound.second = max(bound.second, input[j]);
      if (sum == t) {
        cout << bound.first + bound.second << endl;
        return;
      }
    }
  }
}

