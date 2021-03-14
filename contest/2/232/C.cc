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
// reserve
// sum = accumulate(a.begin(), a.end(), 0);

const LL INF = 0x3f3f3f3f3f3f3f3fll;
const double PI = acos(-1.0), eps = 1e-7;
// const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;
// template <class T>
// using min_queue = priority_queue<T, vector<T>, greater<T>>;
// template <class T>
// using max_queue = priority_queue<T>;
double mod = 1000000007.0;

class Solution {
public:
    double maxAverageRatio(vector<vector<int>>& classes, int extraStudents) {
        max_queue<pair<double, int>> que;
        for(int i=0;i<classes.size();i++){
            auto& v = classes[i];
            int a = v[0], n = v[1];
            
            double rate = mod * (n-a) / (1.0 * n * (n+1));
            que.push({rate, i});
        }
        
        while(extraStudents--){
            auto p = que.top(); que.pop();
            int i = p.second;
            auto& v = classes[i];
            int& a = v[0];
            int& n = v[1];
            a++, n++;
            
            double rate = mod * (n-a) / (1.0 * n * (n+1));
            que.push({rate, i});
        }
        
        double sum = 0;
        
        for(int i=0;i<classes.size();i++){
            auto& v = classes[i];
            int a = v[0], n = v[1];
            
            sum += 1.0 * a / n;
        }
        
        return sum/classes.size();
    }
};

int main() {
//   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
//   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
//   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
