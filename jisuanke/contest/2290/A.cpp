/*************************************************************************
    > File Name: A.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sat Apr 20 12:06:31 2019
 ************************************************************************/

#include<bits/stdc++.h>
using namespace std;
template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T> >;

template <class T>
using max_queue = priority_queue<T>;

typedef long long LL;
const double PI = acos(-1.0), eps = 1e-7;
const int INF = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 4100, max4 = 11100, max5 = 200100, max6 = 2000100;
const int debug = 0;
const int inf = 0x3f3f3f3f;
#define  myprintf(fmt,args...) do{if(debug)printf(fmt, ##args);}while(0)

bool check(int n){
    int sum = 0;

    int right = n;
    for(int i=1;i<right;i++){
        if(n%i==0){
            right = n/i;
            sum += i;
            if(i != right && right != n){
                sum += right;
            }
            if(sum > n){
                return false;
            }
        }
    }

    return sum == n;
}

int main(){
//#ifndef ONLINE_JUDGE
//    freopen("in.txt", "r", stdin);
//    if(debug == 0)freopen("out.txt", "w", stdout);
//#endif

    vector<int>ans;
    ans.push_back(6);
    ans.push_back(28);
    ans.push_back(496);
    ans.push_back(8128);
    ans.push_back(33550336);
    for(int i=0;i<ans.size();i++){
        printf("%d\n",ans[i]);
    }


    return 0;
}
