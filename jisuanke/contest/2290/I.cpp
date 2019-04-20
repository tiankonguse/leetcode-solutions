/*************************************************************************
    > File Name: I.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sat Apr 20 12:07:57 2019
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

const int N = 500010;
LL val[N];
LL sum[N];

struct Mydeq{
    vector<int> vec;
    int backPos, frontPos;
    int maxPos;
    Mydeq(){
        backPos = frontPos = -1;
        maxPos = -1;
        vec.resize(N);
    }
    void push_back(int val){
        if(frontPos==-1){
            frontPos = 0;
        }
        vec[++backPos] = val;
    }
    int back(){
        return vec[backPos];
    }
    void pop_back(){
        backPos--;
        if(backPos < frontPos){
            backPos = frontPos = -1;
        }
    }
    int front(){
        return vec[frontPos];
    }
    void pop_front(){
        frontPos++;
        if(backPos < frontPos){
            backPos = frontPos = -1;
        }
    }
    bool empty(){
        return frontPos > 0;
    }
};

int main() {
//#ifndef ONLINE_JUDGE
//    freopen("in.txt", "r", stdin);
//    if(debug == 0)freopen("out.txt", "w", stdout);
//#endif

    int n;
    scanf("%d", &n);
    LL ans = 0;

    sum[0] = 0;
    for(int i=0; i<n; i++) {
        scanf("%lld", &val[i]);
        sum[i+1] = val[i] + sum[i];
    }


    vector<int> deq;
    map<int,int> left;
    deq.push_back(0);
    left[0] = 0;
    ans = val[0] * val[0];

    int pos, tmpMinValPos;
    LL nowSum, tmpSum;
    for(int i=1; i<n; i++) {
        int minValPos = i;
        int minValLeft = i;
        nowSum = val[i];

        //update minVal up
        while(!deq.empty() && val[deq.back()] >= val[i]) {
            tmpMinValPos = deq.back();
            deq.pop_back();
            tmpSum = sum[i+1] - sum[left[tmpMinValPos]];
            if(val[i] < 0) {
                if(tmpSum < nowSum) {
                    nowSum = tmpSum;
                    minValLeft = left[tmpMinValPos];
                }
            } else {
                if(tmpSum > nowSum) {
                    nowSum = tmpSum;
                    minValLeft = left[tmpMinValPos];
                }
            }
            left.erase(tmpMinValPos);
        }
        ans = max(ans, nowSum * val[minValPos]);

        //update val*sum down
        while(!deq.empty()) {
            tmpMinValPos = deq.back();
            tmpSum = sum[i+1] - sum[left[tmpMinValPos]];
            if(tmpSum * val[tmpMinValPos] <= nowSum * val[minValPos]) {
                deq.pop_back();
                left.erase(tmpMinValPos);
            } else {
                break;
            }
        }

        if(!deq.front()) {
            tmpMinValPos = deq.front();
            tmpSum = sum[i+1] - sum[left[tmpMinValPos]];
            ans = max(ans, tmpSum * val[tmpMinValPos]);
        }


        deq.push_back(minValPos);
        left[minValPos] = minValLeft;

    }


    printf("%lld\n",ans);



    return 0;
}
