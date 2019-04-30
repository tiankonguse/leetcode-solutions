/*************************************************************************
    > File Name: merge-k-sorted-lists.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2015年04月11日 星期六 20时30分45秒
***********************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<queue>
#include<vector>
#include<time.h>
using namespace std;


/**
 Definition for singly-linked list.
*/
 
struct ListNode {
    int val;
    ListNode* next;
    ListNode(){}
    ListNode(int x) : val(x), next(NULL) {}
};
struct ListCmp{
    bool operator() (const ListNode* t1,  const ListNode* t2)const {
        return t1->val > t2->val;
    }
};

void printList(ListNode* list){
    printf("\tbegin list\n");
    while(list != NULL){
        printf("\taddr=%p val=%d next=%p\n", list, list->val, list->next);
        list = list->next;
    }
    printf("\taddr=%p\n", list);
    printf("\tend list\n");
}


void printVector(vector<ListNode*> vec){
    printf("begin vector\n");
    for(int i=0;i<vec.size();i++){
        printList(vec[i]);
    }
    printf("end vector\n");
}


class Solution {
    int debug;

    bool less(ListNode*list){
        while(list != NULL && list->next != NULL){
            if(list->val > list->next->val){
                return false;
            }
            list = list->next;
        }
        return true;
    }

    void sort(ListNode* &list){
        if(list == NULL || list->next == NULL){
            return;
        }

        if(less(list)){
            return;
        }

        ListNode head(0);
        ListNode* next;
        while(list != NULL){
            next = list->next;
            list->next = head.next;
            head.next = list;
            list = next;
        }
        list = head.next;
    }
public:
    Solution(int debug=0):debug(debug){

    }
    ListNode* mergeKLists(vector<ListNode*> &lists) {
        ListNode ans(0);
        priority_queue<ListNode*, vector<ListNode*>, ListCmp> heap;

        for(int i=0;i<lists.size();i++){
            sort(lists[i]);
        }

        if(debug){
            printf("------sorf list\n");
            printVector(lists);
        }

        for(int i=0;i<lists.size();i++){
            if(lists[i] != NULL){
                heap.push(lists[i]);
            }
        }

        ListNode* now;
        ListNode* tail = &ans;
        while(!heap.empty()){
            now = heap.top();heap.pop();
            if(now->next != NULL){
                heap.push(now->next);
            }

            now->next = NULL;
            tail->next = now;
            tail = tail->next;
        }
        
        return ans.next;
    }
};



void testRand(vector<ListNode*>&list, ListNode* data, int size){
    int vecSize = rand()%10;
    ListNode root;
    int listSize;
    int index = 0;
    int step,firstVal;

    list.clear();
    for(int i=0;i<vecSize;i++){
        listSize = rand()%10;
        firstVal = rand()%100;
        step = (rand()%3) - 1;
        root.next = NULL;
        for(int j=0;j<listSize;j++,firstVal+=step,index++){
            data[index].val = firstVal;
            data[index].next = root.next;
            root.next = data + index;
        }
        list.push_back(root.next);
    }
}


void bornTest1(vector<ListNode*>&list, ListNode* data, int size){
    list.clear();
    
    data[0].val = 1; data[0].next = data + 1;
    data[1].val = 2; data[1].next = data + 2;
    data[2].val = 2; data[2].next = NULL;
    list.push_back(data);

    data[3].val = 1;data[3].next = data + 4;
    data[4].val = 1;data[4].next = data + 5;
    data[5].val = 2;data[5].next = NULL;
    list.push_back(data+3);
}

void test(){
    srand(time(NULL));
    Solution work(1);
    vector<ListNode*>lists;
    ListNode* ans = NULL;

    printf("\n>>>>>first test\n");
    printf("<<<<test data\n");
    printVector(lists);
    ans = work.mergeKLists(lists); 
    printf("<<<<ans\n");
    printList(ans);
    
    printf("\nsecond test\n");
    lists.push_back(NULL);
    printf("<<<<test data\n");
    printVector(lists);
    ans = work.mergeKLists(lists); 
    printf("<<<<ans\n");
    printList(ans);
    
    int SIZE = 100;
    ListNode data[SIZE];

    testRand(lists, data, 100);
    printf("<<<<test data\n");
    printVector(lists);
    ans = work.mergeKLists(lists); 
    printf("<<<<ans\n");
    printList(ans);

    bornTest1(lists, data, 100); 
    printf("<<<<test data\n");
    printVector(lists);
    ans = work.mergeKLists(lists); 
    printf("<<<<ans\n");
    printList(ans);
}

int main(){
    test();
    return 0;
}
