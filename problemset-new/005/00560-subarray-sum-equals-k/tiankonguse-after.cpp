/*************************************************************************
    > File Name: tiankonguse-after.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2020年05月15日 19:43:35
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

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        vector<int> pre_sum;
        map<int, vector<int>> sum_to_index;

        pre_sum.push_back(0);
        for(int i = 0, sum = 0; i< nums.size(); i++){
            sum += nums[i];
            pre_sum.push_back(sum);
            sum_to_index[sum].push_back(i);
        }

        int ans = 0;
        for(int i = 0; i < nums.size(); i++){
            int target = pre_sum[i] + k;
            if(sum_to_index.count(target) == 0){
                continue;
            }

            //计算答案个数
            vector<int>& indexs = sum_to_index[target];
            auto low = std::lower_bound (indexs.begin(), indexs.end(), i);
            ans += indexs.end() - low;
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
