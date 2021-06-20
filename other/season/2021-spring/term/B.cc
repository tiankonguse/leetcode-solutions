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
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
    map<pair<TreeNode*, int>, int> m;
    int K;
    int dfs(TreeNode* root, int k){
        if(!root) return 0;
        
        pair<TreeNode*, int> p = {root, k};
        if(m.count(p)){
            return m[p];
        }
        
        int ans = dfs(root->left, K) + dfs(root->right, K); // 当前不染色
        for(int l=0;l < k;l++){
            int r = k - 1 - l;
            int tmp = dfs(root->left, l) + dfs(root->right, r) + root->val;
            ans = max(ans, tmp);
        }
        return m[p] = ans;
    }
public:
    int maxValue(TreeNode* root, int k) {
        K = k;
        return dfs(root, K);
    }
};

int main() {
//   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
//   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
//   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
