/*************************************************************************
    > File Name: design-linked-list.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Thu Apr 11 23:21:26 2019
 ************************************************************************/

#include "../../include/base.h"

class MyLinkedList {
    struct DoublyListNode {
        int val;
        DoublyListNode *next, *prev;
        DoublyListNode(int x) : val(x), next(NULL), prev(NULL) {}
    };
    DoublyListNode* head;
    int iNodeNum;

    DoublyListNode* getNode(int index){
        DoublyListNode* node = head;
        while(index-- > 0){
            node = node->next;
        }
        return node;
    }
public:
    MyLinkedList() {
        head = nullptr;
        iNodeNum = 0;
    }
    int get(int index) {
        if(index >= iNodeNum || index < 0)return -1;
        DoublyListNode* node = getNode(index);
        return node->val;
    }
    void addAtHead(int val) {
        DoublyListNode* node = new DoublyListNode(val);
        if(head)head->prev = node;
        node->next = head;

        head = node;
        iNodeNum++;
    }
    void addAtTail(int val) {
        if(iNodeNum == 0){
            addAtHead(val);
        }else{
            addAtIndex(iNodeNum, val);
        }
    }
   void addAtIndex(int index, int val) {
        if(index <= 0){
            addAtHead(val);
        }else if(index <= iNodeNum && index > 0){
            DoublyListNode* node = new DoublyListNode(val);
            DoublyListNode* pre = getNode(index-1);

            node->prev = pre;
            node->next = pre->next;


            pre->next = node;
            if(node->next)node->next->prev = node;

            iNodeNum++;
        }
    }
    void deleteAtIndex(int index) {
        if(index >= iNodeNum || index < 0)return ;
        DoublyListNode* node = nullptr;
        if(index == 0){
            node = head;
            head = head->next;
            if(head)head->prev = NULL;
        }else{
            DoublyListNode* pre =  getNode(index-1);
            node = pre->next;

            pre->next = node->next;
            if(node->next)pre->next->prev = pre;
        }
        iNodeNum--;
        delete node;
    }
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */

template <class AnsType, class OpreateType, class InitType, class DataType1 = int>
void test_qa(AnsType& expectAns, OpreateType& opreateParam, InitType& initData, DataType1 firstData = DataType1()) {
    AnsType ans;
    MyLinkedList work;

    for(int i=0; i<opreateParam.size(); i++) {
        if(opreateParam[i] == "addAtHead"){
            work.addAtHead(firstData[i][0]);
            ans.push_back(null);
        }
        if(opreateParam[i] == "addAtTail"){
            work.addAtTail(firstData[i][0]);
            ans.push_back(null);
        }
        if(opreateParam[i] == "addAtIndex"){
            work.addAtIndex(firstData[i][0], firstData[i][1]);
            ans.push_back(null);
        }
        if(opreateParam[i] == "get"){
            ans.push_back(work.get(firstData[i][0]));
        }
        if(opreateParam[i] == "deleteAtIndex"){
            work.deleteAtIndex(firstData[i][0]);
            ans.push_back(null);
        }
        //work.output();
    }
    int index = getIndex();
    bool check = eq(ans, expectAns);
    if(!check) {
        printf("index %d: NO\n", index);
        output("opreateParam", opreateParam);
        output("    initData", initData);
        output("   firstData", firstData);
        output("         ans", ans);
        output("   expectAns", expectAns);

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

    opreateParam= { "addAtHead","addAtTail","addAtIndex","get","deleteAtIndex","get" };
    initData = {};
    firstData = {{1},{3},{1,2},{1},{1},{1}};
    expectAns = {null,null,null,2,null,3};
    test_qa(expectAns, opreateParam, initData, firstData);

    opreateParam= { "addAtIndex","get","deleteAtIndex"};
    initData = {};
    firstData = {{-1,0},{0},{-1}};
    expectAns = {null, -1,null};
    test_qa(expectAns, opreateParam, initData, firstData);



    return 0;
}

