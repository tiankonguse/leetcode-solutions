#include "base.h"

typedef long long ll;
typedef long long LL;
typedef unsigned long long ull;
typedef unsigned long long ULL;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
// const int mod = 1e9 + 7;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

// lower_bound 大于等于
// upper_bound 大于
// reserve vector预先分配内存
// reverse(v.begin(), v.end()) 反转
// sum = accumulate(a.begin(), a.end(), 0);

const LL INF = 0x3f3f3f3f3f3f3f3fll;
const double PI = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;

class Solution {
public:
    int dp[110][110];
    vector<pair<int, int>> e[110];
    void init() {
        memset(dp, 0x3f3f3f3f, sizeof dp);
        for (int i = 0; i < 110; i++) {
            e[i].clear();
        }
    }
    int electricCarPlan(vector<vector<int>>& paths, int cnt, int start, int end, vector<int>& charge) {
        init();
        for (int i = 0; i < paths.size(); i++) {
            int a = paths[i][0];
            int b = paths[i][1];
            int c = paths[i][2];
            e[a].push_back({b, c});
            e[b].push_back({a, c});
        }
        dp[start][0] = 0;
        queue<pair<int, int>> que;
        que.push({start, 0});
        int ans = 0x3f3f3f3f;
        while (!que.empty()) {
            int idx = que.front().first;
            int eng = que.front().second;
            que.pop();
            // printf("%d %d %d\n", idx, eng, dp[idx][eng]);
            if (idx == end) {
                ans = min(ans, dp[idx][eng]);
            }
            for (int i = eng + 1; i <= cnt; i++) {
                int tcost = (i - eng) * charge[idx] + dp[idx][eng];
                if (dp[idx][i] <= tcost) continue;
                dp[idx][i] = tcost;
                // printf("%d %d %d\n", idx, i, tcost);
                que.push({idx, i});
            }
            for (int i = 0; i < e[idx].size(); i++) {
                if (e[idx][i].second > eng) continue;
                int tcost = dp[idx][eng] + e[idx][i].second;
                int nextidx = e[idx][i].first;
                int nexteng = eng - e[idx][i].second;
                if (dp[nextidx][nexteng] <= tcost) continue;
                if (tcost >= ans) continue;
                dp[nextidx][nexteng] = tcost;
                que.push({nextidx, nexteng});
            }
        }
        return ans;
    }
};

int main() {
//   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
//   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
//   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
