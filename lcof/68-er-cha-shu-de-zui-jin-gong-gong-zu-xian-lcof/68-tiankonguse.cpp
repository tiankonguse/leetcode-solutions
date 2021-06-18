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
// vector/array: upper_bound(vec.begin(), vec.end(), v)
// map: m.upper_bound(v)
// reserve vector预先分配内存
// reverse(v.begin(), v.end()) 反转
// sum = accumulate(a.begin(), a.end(), 0);
// unordered_map / unordered_set
// 排序，小于是升序：[](auto&a, auto&b){ return a < b; })
// 优先队列 priority_queue<Node>：大于是升序
// struct Node{
//     int t;
//     bool operator<(const Node & that)const { return this->t > that.t; }
// };

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
    // 2: find ans
    // 1: find one node
    // 0: no find node 
    pair<int, TreeNode*> Dfs(TreeNode* root, TreeNode* p, TreeNode* q){
        if(root == NULL){
            return {0, NULL};
        }
        int flag = 0;
        if(root == p || root == q){
            flag = 1;
        }

        auto left = Dfs(root->left, p, q);
        if(left.first == 2){
            return {2, left.second};
        }
        if(left.first == 1 && flag) {
            return {2, root}; // 左子树找到
        }

        auto right = Dfs(root->right, p, q);
        if(right.first == 2){
            return {2, right.second};
        }
        if(right.first == 1 && flag) {
            return {2, root}; // 左子树找到
        }

        if(left.first == 1 && right.first == 1){
            return {2, root};
        }

        return {flag + left.first + right.first, NULL};
    }
public:

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        auto ans = Dfs(root, p, q);
        return ans.second;
    }
};

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
