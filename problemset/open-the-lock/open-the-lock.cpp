/*************************************************************************
    > File Name: open-the-lock.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Tue Apr  2 00:02:51 2019
 ************************************************************************/

#include "../../include/base.h"

class Solution {
public:
    int openLock(vector<string>& deadends, string target) {
        set<string> have;
        have.insert(deadends.begin(),deadends.end());

        if(have.find("0000") != have.end()){
            return -1;
        }
        if(target == "0000"){
            return 0;
        }

        queue<pair<string, int>> que;
        que.push(make_pair("0000", 0));
        have.insert("0000");

        while(!que.empty()){
            auto p = que.front();
            que.pop();
            for(int i=0;i<4;i++){
                for(int j=-1; j<=1;j++){
                    string from = p.first;
                    from[i] += j;
                    if(from[i]<'0')from[i]='9';
                    if(from[i]>'9')from[i]='0';
                    if(from == target){
                        return p.second + 1;
                    }
                    if(have.find(from) != have.end()){
                        continue;
                    }
                    que.push(make_pair(from, p.second + 1));
                    have.insert(from);
                }
            }
        }
        return -1;
    }
};
/*
    TEST_SMP1(ClassName, FunNAme, expectAns, firstData)
    TEST_SMP2(ClassName, FunNAme, expectAns, firstData, secondData)

    int first;
    int expectAns;


    first = 1;
    expectAns = 1;
    TEST_SMP1(Solution, smallestRepunitDivByK, expectAns, first);
*/
int main() {
    vector<string> first;
    string second;
    int expectAns;

    first = {"0201","0101","0102","1212","2002"};
    second = "0202";
    expectAns = 6;
    TEST_SMP2(Solution, openLock, expectAns, first, second);



    first = {"8888"};
    second = "0009";
    expectAns = 1;
    TEST_SMP2(Solution, openLock, expectAns, first, second);


    first = {"8887","8889","8878","8898","8788","8988","7888","9888"};
    second = "8888";
    expectAns = -1;
    TEST_SMP2(Solution, openLock, expectAns, first, second);



    first = {"0000"};
    second = "8888";
    expectAns = -1;
    TEST_SMP2(Solution, openLock, expectAns, first, second);


    return 0;
}
