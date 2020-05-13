/*************************************************************************
    > File Name: tiankonguse-bfs-pair.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2020年05月13日 13:46:01
 ************************************************************************/

#include<bits/stdc++.h>
using namespace std;
template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T> >
template <class T>
using max_queue = priority_queue<T>

typedef long long LL;
const double PI = acos(-1.0), eps = 1e-7;
const int INF = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 4100, max4 = 11100, max5 = 200100, max6 = 2000100;
const int debug = 0;
const int inf = 0x3f3f3f3f;
#define  myprintf(fmt,args...) do{if(debug)printf(fmt, ##args);}while(0)

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
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        queue<pair<TreeNode*, int>> baseQue;
        baseQue.push(pair(root, 0));

        while(!baseQue.empty()){
            auto p = baseQue.front(); baseQue.pop();
            TreeNode* now = p.first;

            if(now == NULL) {
                continue;
            }

            if(p.second >= ans.size()){
                ans.push_back({});
            }

            ans[p.second].push_back(now->val);
            baseQue.push(pair(now->left, p.second + 1));
            baseQue.push(pair(now->right, p.second + 1));
        }

        return ans;
    }
};


int main(){
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    if(debug == 0)freopen("out.txt", "w", stdout);
#endif

    return 0;
}
