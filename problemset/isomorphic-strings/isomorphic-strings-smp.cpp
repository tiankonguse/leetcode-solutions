/*************************************************************************
    > File Name: isomorphic-strings-smp.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Tue Apr 23 23:01:52 2019
 ************************************************************************/

#include "../../include/base.h"

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        int m_s_t[257];
        int m_t_s[257];
        memset(m_s_t, -1, sizeof(m_s_t));
        memset(m_t_s, -1, sizeof(m_t_s));
        int l = s.length();

        for(int i=0;i<l;i++){
            if(m_s_t[s[i]] == -1 && m_t_s[t[i]] == -1){
                m_s_t[s[i]] = t[i];
                m_t_s[t[i]] = s[i];
            }else if(m_s_t[s[i]] == t[i] && m_t_s[t[i]] == s[i]) {
                continue;
            }else{
                return false;
            }
        }

        return true;
    }
};
/*
    //ListNode* root = vecToList({1,2,3,4});
    // vecToTree({});

    TEST_SMP1(ClassName, FunNAme, expectAns, firstData)
    TEST_SMP2(ClassName, FunNAme, expectAns, firstData, secondData)

    int first;
    int expectAns;


    first = 1;
    expectAns = 1;
    TEST_SMP1(Solution, smallestRepunitDivByK, expectAns, first);
*/
int main() {
    string first;
    string second;
    bool expectAns;

    first = "egg";
    second = "add";
    expectAns = true;
    TEST_SMP2(Solution, isIsomorphic, expectAns, first, second);

    first = "foo";
    second = "bar";
    expectAns = false;
    TEST_SMP2(Solution, isIsomorphic, expectAns, first, second);

    first = "paper";
    second = "title";
    expectAns = true;
    TEST_SMP2(Solution, isIsomorphic, expectAns, first, second);

    return 0;
}
