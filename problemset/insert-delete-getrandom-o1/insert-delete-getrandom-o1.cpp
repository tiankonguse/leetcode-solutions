/*************************************************************************
    > File Name: insert-delete-getrandom-o1.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Thu Apr 25 23:37:19 2019
    > link:
    > No:
    > Contest:
 ************************************************************************/

#include "../../include/base.h"

class RandomizedSet {
    vector<int> nums;
    unordered_map<int, int> m;
public:
    /** Initialize your data structure here. */
    RandomizedSet() {
    }

    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        bool ans = false;
        if(m.find(val) == m.end()) {
            ans = true;
            m[val] = nums.size();
            nums.push_back(val);
        }
        return ans;
    }

    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val1) {
        bool ans = false;
        if(m.find(val1) != m.end()) {
            ans = true;
            int index1 = m[val1];
            int index2 = nums.size() - 1;
            int val2 = nums[index2];

            nums[index1] = val2;
            m[val2] = index1;

            m.erase(val1);
            nums.pop_back();
        }
        return ans;
    }

    /** Get a random element from the set. */
    int getRandom() {
        return nums[rand() % nums.size()];
    }
};

template <class AnsType, class OpreateType, class InitType, class DataType1 = int>
void test_qa(AnsType& expectAns, OpreateType& opreateParam, InitType& initData, DataType1 firstData = DataType1()) {
    AnsType ans;
    RandomizedSet work;
    //MyStack work(initData); //°´ÐèÐÞ¸Ä

    for(int i=0; i<opreateParam.size(); i++) {
        int ansTmp = -1;
        if(opreateParam[i] == "insert") {
            ansTmp = work.insert(firstData[i]);
        }
        if(opreateParam[i] == "remove") {
            ansTmp = work.remove(firstData[i]);
        }
        if(opreateParam[i] == "getRandom") {
            ansTmp = work.getRandom();
        }
        ans.push_back(ansTmp);
    }
    int index = getIndex();
    bool check = eq(ans, expectAns);
    if(!check) {
        printf("index %d: NO\n", index);
        output("opreateParam", opreateParam);
        output(" initData", initData);
        output("firstData", firstData);
        output("      ans", ans);
        output("expectAns", expectAns);

    } else {
        printf("index %d: YES\n", index);
    }
    printf("\n");
}

int main() {
    vector<string> opreateParam;
    vector<int> initData;
    vector<int> firstData;
    vector<int> expectAns;

    opreateParam= {"insert","remove","insert","getRandom","remove","insert","getRandom"};
    initData = {};
    firstData = {{1},{2},{2},{-1} ,{1},{2},{-1}};
    expectAns = {{1},{0},{1},{1}  ,{1},{0},{2} };
    test_qa(expectAns, opreateParam, initData, firstData);

    return 0;
}
