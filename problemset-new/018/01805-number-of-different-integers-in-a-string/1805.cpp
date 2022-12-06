class Solution {
 public:
  int numDifferentIntegers(string word) {
    set<string> s;
    string num;
    word.push_back('a');
    for (auto c : word) {
      if (c >= '0' && c <= '9') {
        if (num.size() == 1 && num.back() == '0') {
          num.pop_back();
        }
        num.push_back(c);
      } else {
        if (!num.empty()) {
          s.insert(num);
          num.clear();
        }
      }
    }
    return s.size();
  }
};