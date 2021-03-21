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
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;
const int kKind = 2, N=20005 * 20, kMixBit = 15;
int tire[N][kKind], word[N];
int maxNum = 0;

void Init() {
    memset(word,0,sizeof(word));
    memset(tire[0], 0, sizeof(tire[0]));
    maxNum=1;
}
void Insert(const int val) {
    int p = 0;
    //printf("insert val[%d] :", val);
    for(int i = kMixBit; i >= 0; i--){
        int bit = (val >> i) & 1;
        if(!tire[p][bit]){
            memset(tire[maxNum], 0, sizeof(tire[maxNum]));
            tire[p][bit]= maxNum++;
        }
        
        word[p]++; // 当前路径节点元素的个数
       // printf("%d ", bit);
        p = tire[p][bit];
    }
    //printf(", leaf[%d]\n", p);
    word[p]++;
}



int Query(const int val, const int high, const int index = kMixBit, const int pre = 0, const int p = 0) {
    if(index == -1){ // 叶子节点
        if( pre <= high){
            //printf("leaf, p[%d], pre[%d] num[%d]\n", p, pre, word[p]);
            return word[p];
        }else{
            return 0;
        }
    }
    
    
    if(pre > high) return 0; // 剪枝
    
    int fullVal = pre + (1 << (1+index)) - 1;
    if(fullVal <= high) { //剪枝，当前子树都满足
        //printf("subTree ok, p[%d], pre[%d] index[%d] num[%d]\n", p, pre, index, word[p]);
        return word[p];
    }
    
    int bit = (val >> index) & 1;
    int ans = 0;
    
    for(int i = 0; i < kKind; i++){
        if(!tire[p][i]) continue;
        ans += Query(val, high, index - 1, pre + (i ^ bit) * (1 << index), tire[p][i]);
    }
    
    return ans;
}


class Solution {
public:
    int countPairs(vector<int>& nums, int low, int high) {
        int ans = 0;
        
        
        Init();
        
        for(auto v: nums){
            //printf("next:\n");
            Insert(v);
            ans += Query(v, high) - Query(v, low-1);
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
