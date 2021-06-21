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
    unordered_map<string, int> h;
    vector<string> indexName;
    int l, r, num, len;

    vector<int> ans;
    void Check(int n){
        if(num == n) {
            //printf("l=%d r=%d num=%d\n", l, r, num);
            ans.push_back(l);
            h[indexName[l]]++;
            l += len;
            num--;
        }
    }

public:
    vector<int> findSubstring(string& s, vector<string>& words) {
        indexName.resize(s.size());

        for(auto& v: words){
            h[v]++;
        }
        len = words[0].size();

        for(int i = 0; i < len; i++){
            l = r = i;
            num = 0;

            while(l <= r && r + len <= s.size()){
                if(indexName[r].empty()){
                    indexName[r] = s.substr(r, len);
                }
                if(h.count(indexName[r]) == 0 || h[indexName[r]] == 0) { // 没找到
                    if(num == 0) { // 还没找到匹配的, l == r
                        l = r = r + len;
                    }else{
                        h[indexName[l]]++;
                        l += len;
                        num--;
                    }
                }else{
                    num++;
                    h[indexName[r]]--;
                    r += len;
                    Check(words.size());
                }
            }
            while(num > 0){
                h[indexName[l]]++;
                l += len;
                num--;
            }
        }
        sort(ans.begin(), ans.end());
        return ans;
    }
};

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
