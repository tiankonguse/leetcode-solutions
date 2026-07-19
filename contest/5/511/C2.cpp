class Solution {
 public:
  vector<bool> transformStr(const string& s, vector<string>& strs) {
    int n = s.size();

    vector<int> preOne(n + 1, 0);
    for (int i = 0; i < n; i++) preOne[i + 1] = preOne[i] + (s[i] == '1');

    int totalOne = preOne[n];

    vector<bool> ans;

    for (auto& t : strs) {
      vector<int> sufOne(n + 1, 0), sufQ(n + 1, 0);

      for (int i = n - 1; i >= 0; i--) {
        sufOne[i] = sufOne[i + 1] + (t[i] == '1');
        sufQ[i] = sufQ[i + 1] + (t[i] == '?');
      }

      int one = 0;
      int q = 0;
      bool ok = true;

      for (int i = 0; i < n; i++) {
        if (t[i] == '1')
          one++;
        else if (t[i] == '?')
          q++;

        int suffixOne = sufOne[i + 1];
        int suffixQ = sufQ[i + 1];

        int low = max(one, totalOne - (suffixOne + suffixQ));
        int high = one + q;

        if (low > min(high, preOne[i + 1])) {
          ok = false;
          break;
        }
      }

      int fixedOne = sufOne[0];
      int totalQ = sufQ[0];
      if (!(fixedOne <= totalOne && totalOne <= fixedOne + totalQ)) ok = false;

      ans.push_back(ok);
    }

    return ans;
  }
};