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
// struct Node{
//     int t;
//     bool operator<(const Node & that)const { return this->t > that.t; }
// };

const LL INF = 0x3f3f3f3f3f3f3f3fll;
const double PI = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;


class ThroneInheritance {
    string king;
    unordered_map<string, pair<int, int>> h;
    vector<string> names;
    unordered_map<int, set<int>> edge;

    vector<string> ans;

    
    int Get(const string& name){
        if(h.count(name) == 0) {
            names.push_back(name);
            h[name] = {names.size(), 1};
        }
        return h[name].first;
    }

    void Del(const string& name){
        h[name].second = 0;
    }

    void AddAns(int pos){
        string& name = names[pos - 1];
        auto p = h[name];
        if(p.second){
            ans.push_back(name);
        }
    }

    void Dfs(int pos){
        AddAns(pos);
        for(auto p: edge[pos]){
            Dfs(p);
        }
    }
public:


    ThroneInheritance(const string& kingName) {
        king = kingName;
        edge[Get(king)];
    }
    
    void birth(const string& parentName, const string& childName) {
        edge[Get(parentName)].insert(Get(childName));
    }
    
    void death(const string& name) {
        Del(name);
    }
    
    vector<string> getInheritanceOrder() {
        ans.clear();
        ans.reserve(names.size());
        Dfs(1);
        return ans;
    }
};

/**
 * Your ThroneInheritance object will be instantiated and called as such:
 * ThroneInheritance* obj = new ThroneInheritance(kingName);
 * obj->birth(parentName,childName);
 * obj->death(name);
 * vector<string> param_3 = obj->getInheritanceOrder();
 */

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
