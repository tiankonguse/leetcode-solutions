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

// int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
// int dir[8][2] = {{0,1},{1, 1},{1,0},{1,-1}, {0,-1}, {-1, -1}, {-1,0}, {-1, 1}};
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
// __builtin_popcount 快速得到 1 的个数
// struct Node{
//     int t;
//     bool operator<(const Node & that)const { return this->t > that.t; }
// };

// mutex mtx;       // 互斥量，锁，定义一个即可
// condition_variable cv; // 条件变量
// cv.notify_one(); // 事件通知
// unique_lock<mutex> lck(mtx); 
// cv.wait(lck); //等待事件

// atomic_int tick; // 原子计数
// this_thread::yield();  // 线程 sleep

// #include <semaphore.h> // 需要手动包含信号量头文件
// sem_t sem_done;
// sem_init(&bar_done, 0 , 1);
// sem_wait(&bar_done);
// sem_post(&foo_done);

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
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */


class Solution {
    int n;
    
    struct Node{
        int index = -1;
        TreeNode* tree = nullptr;
        int pre = -1;
        int flag = 0;
    };
    unordered_map<int, Node> treeInfos;
    
    bool InitChild(TreeNode*& tree, int pre) {
        if(tree == nullptr) return true;
        int val = tree->val;
        if(treeInfos.count(val) == 0) {
            return true;
        }

        Node& treeinfo = treeInfos[val];
        if(treeinfo.pre != -1) return false; // 三个顶点

        treeinfo.pre = pre;
        tree = treeinfo.tree;
        return true;
    }
    bool Init(vector<TreeNode*>& trees){
        for(int i = 0; i < trees.size(); i++){
            TreeNode* tree = trees[i];
            Node& treeinfo = treeInfos[tree->val];
            treeinfo.index = i;
            treeinfo.tree = tree;
        }
        
        
        for(int i = 0; i < trees.size(); i++){
            TreeNode* tree = trees[i];
            
            if(!InitChild(tree->left, i)){
                return false;
            }
            
            if(!InitChild(tree->right, i)){
                return false;
            }
        }
        return true;
    }
    
    int root_num = 0;
    bool dfs(TreeNode* root, int min_val, int max_val){ // [min, max]
        if(root == nullptr) return true;
        int val = root->val;
        //printf("val=%d min=%d max=%d\n", val, min_val, max_val);
        if(val < min_val || val > max_val) return false;
        
        if(treeInfos.count(val) == 0) {
            return true;
        }
        
        Node& treeinfo = treeInfos[root->val];
        if(treeinfo.flag == 1) return false;
        treeinfo.flag = 1;
        root_num++;
        
        if(!dfs(root->left, min_val, val -1)) {
            return false;
        }
        if(!dfs(root->right, val + 1, max_val)) {
            return false;
        }
        return true;
    }
    
public:
    TreeNode* canMerge(vector<TreeNode*>& trees) {
        n = trees.size();
        if(!Init(trees)) {
            return nullptr;
        }
        
        TreeNode* root = nullptr;
        for(int i=0;i<n;i++){
            TreeNode* tree = trees[i];
            Node& treeinfo = treeInfos[tree->val];
            if(treeinfo.pre == -1) {
                if(root != nullptr) return nullptr; // more root
                root = tree;
            }
        }
        
        if(root == nullptr) return nullptr; // no root
        
        if(!dfs(root, 1, 5555555)){
            return nullptr;
        }
        
        if(root_num < n) return nullptr;
        
        return root;
    }
};
int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
