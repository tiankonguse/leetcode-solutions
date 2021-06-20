/*************************************************************************
    > File Name: M.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sat Apr 20 12:08:18 2019
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

const int N = 100010;
int seqNext[N][26]; //从当前下标开始，第一个等于当前字符的位置
char first[N];
char second[N];
int last[26];


bool isSeq() {
    int len = strlen(second);
    int pos = 0;
    for(int i=0; i<len; i++) {
        if(pos == -1) {
            return false;
        }
        pos = seqNext[pos][second[i]-'a'];
        if(pos == -1) {
            return false;
        }
        pos = pos + 1;
    }
    return true;

}


void init() {
    memset(seqNext, -1, sizeof(seqNext));
    memset(last, -1, sizeof(last));

    //init seqNext
    int n = strlen(first);
    for(int i=n-1; i>=0; i--) {
        last[first[i] - 'a'] = i;
        memcpy(seqNext[i], last, sizeof(last));
    }
}
int main() {
//#ifndef ONLINE_JUDGE
//    freopen("in.txt", "r", stdin);
//    if(debug == 0)
//        freopen("out.txt", "w", stdout);
//#endif

    scanf("%s", first);
    init();

    //read N
    int N;
    scanf("%d", &N);
    while(N--) {
        scanf("%s", second);
        printf("%s\n", isSeq()?"YES":"NO");

    }

    return 0;
}
