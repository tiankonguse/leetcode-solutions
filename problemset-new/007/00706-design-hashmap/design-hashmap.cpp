/*************************************************************************
    > File Name: design-hashmap.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sun Apr 21 17:46:12 2019
    > link: https://leetcode.com/problems/design-hashmap/
    > No: 706
 ************************************************************************/

#include "../../include/base.h"

class MyHashMap {
    struct Node {
        int key;
        int val;
        Node* next;
        Node(int key=0, int val=0):key(key),val(val),next(NULL) {}
    };
    vector<Node> hashVec;

    int myhash(int key) {
        if(key < 0)
            key = -key;
        return key % hashVec.size();
    }
    Node* getPre(int key){
        int index = myhash(key);
        Node* pre = &hashVec[index];
        while(pre->next) {
            if(pre->next->key == key) {
                return pre;
            }
            pre = pre->next;
        }
        return pre;
    }
public:
    MyHashMap() {
        hashVec.resize(101);
    }
    void put(int key, int value) {
        Node* pre = getPre(key);
        if(pre->next != NULL){
            pre->next->val = value;
        }else{
            pre->next = new Node(key, value);
        }
    }

    void remove(int key) {
        Node* pre = getPre(key);
        if(pre->next != NULL){
            Node* now = pre->next;
            pre->next = now->next;
            delete now;
        }
    }
    int get(int key) {
        Node* pre = getPre(key);
        if(pre->next != NULL){
            return pre->next->val;
        }
        return -1;
    }
};

template <class AnsType, class OpreateType, class InitType, class DataType1 = int>
void test_qa(AnsType& expectAns, OpreateType& opreateParam, InitType& initData, DataType1 firstData = DataType1()) {
    AnsType ans;
    MyHashMap work;
    //MyStack work(initData); //°´ÐèÐÞ¸Ä

    for(int i=0; i<opreateParam.size(); i++) {
        int ansTmp = -1;
        if(opreateParam[i] == "put") {
            work.put(firstData[i][0], firstData[i][1]);
        }
        if(opreateParam[i] == "get") {
            ansTmp = work.get(firstData[i][0]);
        }
        if(opreateParam[i] == "remove") {
            work.remove(firstData[i][0]);
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
    vector<vector<int>> firstData;
    vector<int> expectAns;

    opreateParam= {"put","put","get","get","put","get", "remove", "get"};
    initData = {};
    firstData = {{1,1},{2,2},{1},{3},{2,1},{2},{2},{2}};
    expectAns = {{-1},{-1},{1},{-1},{-1},{1},{-1},{-1}};
    test_qa(expectAns, opreateParam, initData, firstData);

    return 0;
}
