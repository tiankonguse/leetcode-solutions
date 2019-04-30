/*************************************************************************
    > File Name: find-the-town-judge.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019��02��27�� 20:29:02
 ************************************************************************/

#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<string>
#include<stack>
#include<map>
#include<set>
#include<queue>
#include<vector>
#include<cmath>
#include<algorithm>
#include<functional>
#include<time.h>
using namespace std;


#ifdef __int64
typedef __int64 LL;
#else
typedef long long LL;
#endif

const int debug = 0;
typedef unsigned uint;
typedef unsigned char uchar;

class Solution {
    const int N = 1010;
public:
    int findJudge(int n, vector<vector<int> >& trust) {

        int trustTo[N]; //����������
        int trustFrom[N]; //���α��˵�����
        memset(trustTo, 0, sizeof(trustTo));
        memset(trustFrom, 0, sizeof(trustFrom));

        //����ͳ��
        for(int i=0; i< trust.size(); i++) {
            trustTo[trust[i][1]]++;
            trustFrom[trust[i][0]]++;
        }

        //���Ҳ����ε�����
        //���ұ�����Ϊn-1�ĸ���
        int ans = -1;
        for(int i=1; i<=n; i++) {
            if(trustFrom[i] == 0 && trustTo[i] == n - 1) {
                ans = i;
            }
        }
        return ans;
    }
};

void output(char const* name,int data) {
    printf("%s:", name);
    printf("%d ", data);
    printf("\n");
}

void output(char const* name, vector<int>&data) {
    printf("%s[%d]:", name, data.size());
    for(int i=0; i<data.size(); i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
}

void output(char const* name, vector<vector<int> >&data) {
    printf("%s[%d]:\n", name, data.size());
    for(int i=0; i<data.size(); i++) {
        output("    ", data[i]);
    }
}


void test(int n, vector<vector<int> >& data) {
    Solution work;
    int ans;
    ans = work.findJudge(n, data);
    output("data", data);
    output("ans", ans);
}

int main() {
    vector<vector<int> > data;

    data = {{1,2}};
    test(2, data);

    data = {{1,3},{2,3}};
    test(3, data);

    data = {{1,3},{2,3},{3,1}};
    test(3, data);

    data = {{1,2},{2,3}};
    test(3, data);

    data = {{1,3},{1,4},{2,3},{2,4},{4,3}};
    test(4, data);
    return 0;
}
