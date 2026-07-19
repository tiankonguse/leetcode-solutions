// 997 / 998 个通过的测试用例
class Solution {
public:
    vector<bool> transformStr(const string& s, vector<string>& strs) {
        int n = s.size();

        vector<int> pre0(n + 1, 0);
        for (int i = 0; i < n; i++)
            pre0[i + 1] = pre0[i] + (s[i] == '0');

        int need0 = pre0[n];

        vector<bool> ans;

        for (auto &t : strs) {
            vector<char> dp(need0 + 1), ndp(need0 + 1);
            dp[0] = 1;

            for (int i = 0; i < n; i++) {
                fill(ndp.begin(), ndp.end(), 0);

                for (int k = 0; k <= need0; k++) {
                    if (!dp[k]) continue;

                    if (t[i] != '1') {
                        if (k + 1 <= need0 && k + 1 >= pre0[i + 1])
                            ndp[k + 1] = 1;
                    }

                    if (t[i] != '0') {
                        if (k >= pre0[i + 1])
                            ndp[k] = 1;
                    }
                }

                dp.swap(ndp);
            }

            ans.push_back(dp[need0]);
        }

        return ans;
    }
};