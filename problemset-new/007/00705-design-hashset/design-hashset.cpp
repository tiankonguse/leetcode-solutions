/*************************************************************************
    > File Name: design-hashset.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年04月19日 16:24:27
 ************************************************************************/

#include "../../include/base.h"

class MyHashSet {
    struct Node {
        int val;
        Node* next;
        Node(int val=0):val(val),next(NULL) {}
    };
    vector<Node> hashSet;

    int myhash(int key) {
        if(key < 0)
            key = -key;
        return key % hashSet.size();
    }


public:
    /** Initialize your data structure here. */
    MyHashSet() {
        hashSet.resize(101);
    }



    void add(int key) {
        if(contains(key))
            return;
        int index = myhash(key);
        Node* pre = &hashSet[index];
        while(pre->next) {
            pre = pre->next;
        }
        pre->next = new Node(key);
    }

    void remove(int key) {
        if(!contains(key))
            return;
        int index = myhash(key);
        Node* pre = &hashSet[index];
        while(pre->next) {
            if(pre->next->val == key) {
                Node* now = pre->next;
                pre->next = now->next;
                delete now;
                return ;
            }
            pre = pre->next;
        }
    }

    /** Returns true if this set contains the specified element */
    bool contains(int key) {
        int index = myhash(key);
        Node* pre = &hashSet[index];
        while(pre->next) {
            if(pre->next->val == key) {
                return true;
            }
            pre = pre->next;
        }
        return false;
    }
};

template <class AnsType, class OpreateType, class InitType, class DataType1 = int>
void test_qa(AnsType& expectAns, OpreateType& opreateParam, InitType& initData, DataType1 firstData = DataType1()) {
    AnsType ans;
    MyHashSet work;
    //MyStack work(initData); //按需修改

    for(int i=0; i<opreateParam.size(); i++) {
        int ansTmp = -1;
        if(opreateParam[i] == "add") {
            work.add(firstData[i]);
        }
        if(opreateParam[i] == "remove") {
            work.remove(firstData[i]);
        }
        if(opreateParam[i] == "contains") {
            ansTmp = work.contains(firstData[i]);
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

    opreateParam= {"add","add","contains","contains","add","contains","remove","contains"};
    initData = {};
    firstData = {{1},{2},{1},{3},{2},{2},{2},{2}};
    expectAns = {{-1},{-1},{1},{0},{-1},{1},{-1},{0}};
    test_qa(expectAns, opreateParam, initData, firstData);

    return 0;
}
