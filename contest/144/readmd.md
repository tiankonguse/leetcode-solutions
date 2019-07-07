# Weekly Contest 144  

地址： https://leetcode.com/contest/weekly-contest-144  



## [Chinese/C++] 1108. O(n) 扫描一遍完成ip替换  


题意：对 IP 地址的`.`替换为`[.]`。  


思路：扫描一遍判断即可。  


```
string defangIPaddr(string address) {
    string ans;
    for(auto& v: address){
        if(v == '.'){
            ans.append("[.]");
        }else{
            ans.push_back(v);
        }
    }
    return ans;
}
```


## [Chinese/C++] 1109. O(n) 左加右减代替线段树区间操作  


题意：一条指令的含义是区间加上指定值，有很多指令，求最终区间每个位置的值。  


思路：最原始的方法是线段树区间操作。  


但是这道题不存在查询，只是求最终结果。  
那就可以使用标记的方法，区间的开始位置加上指定值，区间结束的下个位置减去指定值。  
然后从左到右累加即可。  


```
vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
    vector<int> dp;
    dp.resize(n+2, 0);
    for(auto& v: bookings){
        dp[v[0]] += v[2];
        dp[v[1]+1] -= v[2];
    }
    vector<int> ans;
    int now = 0;
    for(int i=1;i<=n;i++){
        now += dp[i];
        ans.push_back(now);
    }
    return ans;
}
```
## [Chinese/C++] 1110. O(n) 递归DFS得到森林  


题意：给一个二叉树，节点的值互不相同。给一个集合代表这些树的节点要被删除。  
一个数删除一个节点后，会形成多个树，称之为森林。  
求删除节点后的森林（数之间顺序不做要求）。  


思路：直接递归即可。  


需要特殊处理的地方就是传递一个标记，代表当前节点是否可能是树根。  
如果是树根的话，需要加入答案。不是树根的话，直接递归即可。  


```
class Solution {
    set<int> detSet;
    vector<TreeNode*> ans;
    
    void dfs(TreeNode* & root, int isRoot){
        if(root == NULL) return;
        
        if(detSet.find(root->val) != detSet.end()){
            dfs(root->left, 1);
            dfs(root->right, 1);
            root = NULL; //使用引用，解除树的关系
        }else{
            if(isRoot){
                ans.push_back(root); //当前节点就是根
            }
            dfs(root->left, 0);
            dfs(root->right, 0);
        }
    }
    
public:
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        detSet.insert(to_delete.begin(), to_delete.end());
        dfs(root, 1);
        return ans;
    }
};
```


当然，比赛的时候，我是使用队列加递归实现的。  
队列里面保存当前可能是答案的树。  
如果当前树的根没有删除，则找到一个答案。  
之后递归处理每一颗树，判断是否有子节点被删除，从而拆分出两颗树。  


```
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
    set<int> detSet;
    queue<TreeNode*> que;
    
    void dfs(TreeNode* & root){
        if(root == NULL) return;
        
        if(detSet.find(root->val) != detSet.end()){
            que.push(root->left);
            que.push(root->right);
            root = NULL;
        }else{
            dfs(root->left);
            dfs(root->right);
        }
    }
    
public:
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        detSet.insert(to_delete.begin(), to_delete.end());
        vector<TreeNode*> ans;
                        
        
        que.push(root);
        while(!que.empty()){
            TreeNode* now = que.front();que.pop();
            if(now == NULL) continue;
            if(detSet.find(now->val) == detSet.end()){
                ans.push_back(now);
            }
            dfs(now);
        }
        return ans;
    }
};
```

## [Chinese/C++] 1111. O(n) 扫描一遍完成括号拆分  


题意：需要先对有括号与括号的深度的定义达成一致。  
有效括号的定义：空字符串是有效括号，`A`和`B`是有效括号，则`AB` 和 `(A)`都是有效括号。  
括号深度的定义：空字符串的深度为`0`，`AB`的深度为`max(d(A), d(B))`，`(A)`的深度为`1 + d(A)`。  


现在需要对一个有效括号进行拆分，拆分为两个有效括号，目标是拆分后两个有效括号的最大深度最小。  
问该如何拆分？  


拆分定义：从一个有效括号序列中删除一些字符，则剩余的可以组成一个有效括号，删除的字符也可以组成一个有效括号。  


既然是为了最大深度最小，那就应该对深度对半分。  
即如果一个括号的深度是`2n`，那拆分后的两个括号的深度应该都是`n`。  
同理，如果一个的深度是`2n+1`，那拆分后的两个括号的深度分别是`n`和`n+1`。  


如果能够想到这里，这道题就很简单了。  
对用栈来遍历有效括号序列，按照奇偶性，深度每增加一次，就打上删除标记。  


而对于多个平行的有效括号，比如`AB`，其实的标记需要不同。  
不然对于`()()`我们就没有删除任何括号。  


具体可以看代码  


```
vector<int> maxDepthAfterSplit(string seq) {
    stack<int> sta;
    vector<int> ans;
    int flag = 0;
    for(int i=0;i<seq.size();i++){
        if(seq[i] == '('){
            int nextVal = 0;
            if(!sta.empty()){
                nextVal = !sta.top();
            }else{
                flag = !flag;
                nextVal = flag;
            }
            ans.push_back(nextVal);
            sta.push(nextVal);
        }else{
            ans.push_back(sta.top());
            sta.pop();
        }
    }
    return ans;
}
```

















