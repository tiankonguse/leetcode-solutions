/*************************************************************************
    > File Name: minimum-index-sum-of-two-lists.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Tue Apr 23 23:09:54 2019
    > No: 599. Minimum Index Sum of Two Lists
    > Contest:
 ************************************************************************/

#include "../../include/base.h"

class Solution {
public:
    vector<string> findRestaurant(vector<string>& list1, vector<string>& list2) {
        map<string, int> m;
        for(int i=0; i<list1.size(); i++) {
            m[list1[i]] = i;
        }

        int minIndexSum = list1.size() + list2.size();
        vector<string> ans;
        for(int i=0; i<list2.size(); i++) {
            if(m.find(list2[i]) == m.end()) {
                continue;
            }
            if(i + m[list2[i]] < minIndexSum) {
                minIndexSum = i + m[list2[i]] ;
                ans.clear();
                ans.push_back(list2[i]);
            } else if(i + m[list2[i]] == minIndexSum) {
                ans.push_back(list2[i]);
            }
        }
        return ans;
    }
};

/*
    //ListNode* root = vecToList({1,2,3,4});
    // vecToTree({});

    TEST_SMP1(ClassName, FunNAme, expectAns, first)
    TEST_SMP2(ClassName, FunNAme, expectAns, first, second)

    int first;
    int second;
    int expectAns;


    first = 1;
    second = "";
    expectAns = 1;
    TEST_SMP1(Solution, smallestRepunitDivByK, expectAns, first);
*/
int main() {
    vector<string> first;
    vector<string> second;
    vector<string> expectAns;

    first = {"Shogun", "Tapioca Express", "Burger King", "KFC"};
    second = {"Piatti", "The Grill at Torrey Pines", "Hungry Hunter Steakhouse", "Shogun"};
    expectAns = {"Shogun"};
    TEST_SMP2(Solution, findRestaurant, expectAns, first, second);

    first = {"Shogun", "Tapioca Express", "Burger King", "KFC"};
    second = {"KFC", "Shogun", "Burger King"};
    expectAns = {"Shogun"};
    TEST_SMP2(Solution, findRestaurant, expectAns, first, second);

    return 0;
}
