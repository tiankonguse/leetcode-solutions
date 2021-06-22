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

const LL INF = 0x3f3f3f3f3f3f3f3fll;
const double PI = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;


class Solution {
    vector<pair<char, int>> vec;
    int n;
    int N;

    vector<string> ans;

    void Dfs(string& s){
        if(s.length() == N) {
            ans.push_back(s);
            return;
        }
        for(int i=0;i<n;i++){
            if(vec[i].second == 0) continue;
            s.push_back(vec[i].first);
            vec[i].second--;;
            Dfs(s);
            vec[i].second++;
            s.pop_back();
        }
    }
    int Cal(int n){
        int l = 1;
        while(n > 0){
            l *= n;
            n--;
        }
        return l;
    }

public:
    vector<string> permutation(string& s) {
        unordered_map<char, int> h;
        vec.reserve(s.length());
        for(auto c: s){
            if(h.count(c)){
                vec[h[c]].second++;
            }else{
                h[c] = vec.size();
                vec.push_back({c, 1});
            }
        }

        n = vec.size();
        N = s.length();
        ans.reserve(Cal(N));
        string tmp;
        Dfs(tmp);

        return ans;
    }
};

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
