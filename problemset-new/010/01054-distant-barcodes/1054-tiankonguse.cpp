/*************************************************************************
    > File Name: 1054-distant-barcodes.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sun May 26 10:08:23 2019
    > link: https://leetcode.com/problems/distant-barcodes
    > No: 1054. Distant Barcodes
    > Contest: https://leetcode.com/contest/weekly-contest-138/problems/distant-barcodes/
 ************************************************************************/

#include "../../../include/base.h"

class Solution {
public:
    vector<int> rearrangeBarcodes(vector<int>& barcodes) {
        map<int, int> mapVal2Count;
        for(int i=0; i<barcodes.size(); i++) {
            mapVal2Count[barcodes[i]]++;
        }

        map<int, set<int>> mapCount2Vals;
        for(auto& it : mapVal2Count) {
            mapCount2Vals[it.second].insert(it.first);
        }
        vector<int> ans;

        while(mapCount2Vals.size() > 0) {
            auto it = mapCount2Vals.end();
            it--;
            set<int>& s = it->second;
            for(auto v: s) {
                ans.push_back(v);
            }
            if(s.size() == 1 && mapCount2Vals.size() > 1) {
                auto pre = it;
                pre--;
                int count = pre->first;
                set<int>& preSet = pre->second;
                int v = *preSet.begin();

                ans.push_back(v);
                preSet.erase(v);
                if(preSet.size() == 0) {
                    mapCount2Vals.erase(pre);
                }
                if(count>1) {
                    mapCount2Vals[count-1].insert(v);
                }
            }


            if(it->first > 1) {
                for(auto v: s) {
                    mapCount2Vals[it->first-1].insert(v);
                }
            }

            mapCount2Vals.erase(it);
        }

        return ans;
    }
};

/*
    //ListNode* root = vecToList({1,2,3,4});
    // vecToTree({});
    // std::reverse(a.begin(),a.end());
    //int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
*/
int main() {
#define CLASS Solution
#define FUNCTION smallestRepunitDivByK

    int first;
    int second;
    int expectAns;

    first = 113;
    second = 1;
    expectAns = -1;
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);
    //TEST_SMP2(Solution, FUNCTION, expectAns, first, second);

    return 0;
}
