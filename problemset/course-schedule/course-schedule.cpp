/*************************************************************************
  > File Name: course-schedule.cpp
  > Author: tiankonguse(skyyuan)
  > Mail: i@tiankonguse.com 
  > Created Time: 2015年06月 7日 20:35:54
***********************************************************************/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<string>
#include<queue>
#include<map>
#include<cmath>
#include<stack>
#include<algorithm>
#include<functional>
#include<stdarg.h>
using namespace std;
#ifdef __int64
typedef __int64 LL;
#else
typedef long long LL;
#endif
class Solution {
    int findMin(vector<int>&pre, vector<int>&finish, vector<int>&vecOK){
        int size = finish.size();
        for(int i=0;i<size;i++){
            if(vecOK[i]){
                continue;
            }
            if(pre[i] == finish[i]){
                return i;
            }
        }

        return -1;
    }
    void learn(int pos, vector<int>&vecPreFinish, vector<vector<int> >&vecCoursePre, vector<int>&vecOK){
        int size = vecPreFinish.size();
       for(int i=0;i<size;i++){
            if(vecOK[i]){
                continue;
            }
           vector<int>& course = vecCoursePre[i];
            for(int j=0;j<course.size();j++){
                if(course[j] == pos){
                    vecPreFinish[i]++;
                }
            } 
       } 
    }
public:
    bool canFinish(int numCourses, vector<pair<int, int> >& prerequisites) {
        vector<vector<int> >vecCoursePre(numCourses);
        vector<int>vecPreNum(numCourses, 0);
        vector<int>vecPreFinish(numCourses, 0);
        vector<int>vecOK(numCourses, 0);

        int tmpNum = prerequisites.size();
        int first, second, pos;
        for(int i=0;i<tmpNum;i++){
            first = prerequisites[i].first;
            second = prerequisites[i].second;
            vecCoursePre[first].push_back(second);
            vecPreNum[first]++;
        }

        for(int i=0;i<numCourses;i++){
            pos = findMin(vecPreNum, vecPreFinish, vecOK);    
            if(pos == -1){
                return false;
            }
            vecOK[pos] = 1;
            learn(pos, vecPreFinish, vecCoursePre, vecOK);
        }
        return true;     
    }
};
int main() {
    Solution work;
    int n;
    vector<pair<int, int> >data;
    int ans;

    n=2;
    data.push_back(make_pair(1,0));
    ans = work.canFinish(n, data);
    printf("ans=%d\n",ans);

    return 0;
}
