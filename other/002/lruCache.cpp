/*************************************************************************
    > File Name: lruCache.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年04月23日 21:40:12
 ************************************************************************/

#include "../../include/base.h"

class MyHashMap {
    struct Node {
        Node* next, *lurNext, *lurPrev;
        int key, val;
        Node(int k = 0, int v = 0) {
            key = k, val = v;
            next = lurNext = lurPrev = NULL;
        }
    };

    int cacheMax;
    int cacheSize;
    vector<Node> hashVec;
    Node lruNode;
    Node* lruHead;

    int myhash(int key) {
        if(key < 0)
            key = -key;
        return key % hashVec. size();
    }

    Node* getPre(int key) {
        int index = myhash(key);
        Node* linkHead = &hashVec[index];
        Node* pre = linkHead;
        while(pre->next) {
            if(pre->next->key == key) {
                //update link
                Node* now = pre->next;
                pre->next = pre->next->next;
                //add to link head
                now->next = linkHead->next;
                linkHead->next = now;
                updateLur(pre->next);
                return pre;
            }
            pre = pre->next;
        }
        return pre;
    }

    void insertLru(Node*  now) {
        now->lurNext = lruHead->lurNext;
        now->lurPrev = lruHead->lurNext->lurPrev;
        lruHead->lurNext->lurPrev = now;
        lruHead->lurNext = now;
    }

    void updateLur(Node* now) {
        //del from lru link
        now->lurPrev->lurNext = now->lurNext;
        now->lurNext->lurPrev = now->lurPrev;
        insertLru(now);
    }
public:

    MyHashMap() {
        cacheSize = 0;
        cacheMax = 101 * 1.5;
        hashVec.resize(101);
        lruHead = &lruNode;
        lruHead->lurNext = lruHead->lurPrev = lruHead;
    }
    int lru() {
        int key = -1;
        if(cacheSize > 0) {
            key = lruHead->lurPrev->key;
            this->del(lruHead->lurPrev->key);
        }
        return key;
    }

    void del(int key) {
        Node* pre = getPre(key);
        if(pre->next != NULL) {
            Node* now = pre->next;
            //del from hash link
            pre->next = pre->next->next;

            //del from lur link
            now->lurPrev->lurNext = now->lurNext;
            now->lurNext->lurPrev = now->lurPrev;
            delete now;
            cacheSize--;
        }
    }

    void set(int key, int value) {
        Node* pre = getPre(key);
        if(pre->next == NULL) {
            if(cacheSize == cacheMax) {
                lru();
            }
            cacheSize++;
            pre->next = new Node(key, value);
            insertLru(pre->next);
        }
        pre->next->val = value;

    }

    int get(int key) {
        Node* pre = getPre(key);
        if(pre->next != NULL) {
            return pre->next->val;
        }
        return -1;
    }
};



/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */
template <class AnsType, class OpreateType, class InitType, class DataType1 = int>
void test_qa(AnsType& expectAns, OpreateType& opreateParam, InitType& initData, DataType1 firstData = DataType1()) {
    AnsType ans;
    MyHashMap work;
    //MyStack work(initData); //按需修改

    for(int i=0; i<opreateParam.size(); i++) {
        int ansTmp = -1;
        if(opreateParam[i] == "get") {
            ansTmp = work.get(firstData[i][0]);
        }
        if(opreateParam[i] == "set") {
            work.set(firstData[i][0], firstData[i][1]);
        }
        if(opreateParam[i] == "del") {
            work.del(firstData[i][0]);
        }
        if(opreateParam[i] == "lru") {
           ansTmp =  work.lru();
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

    opreateParam= {"get","set","get","set","lru","get","get"};
    initData = {};
    firstData = {{1} ,{100,101},{100} ,{200, 201},{}    ,{100},{200}};
    expectAns = {{-1},{-1}     ,{101} ,{-1}      ,{100} ,{-1} ,{201}};
    test_qa(expectAns, opreateParam, initData, firstData);

    return 0;
}
