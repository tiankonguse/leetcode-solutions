/*************************************************************************
    > File Name: lru-cache.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2015年04月05日 星期日 14时06分15秒
 ************************************************************************/

#include<stdio.h>
#include<map>
using namespace std;

class LRUCache{

    int capacity;
    int length;

    struct Node{
        int key;
        int val;
        Node* next;
        Node* pre;
        Node(){
            next = NULL;
            pre = NULL;
        }
    }HEAD, TAIL;

    map<int, Node*>m;

    Node* head;
    Node* tail;

public:
    LRUCache(int capacity) {
        this->capacity = capacity;
        this->length = 0;
        head = &HEAD;
        tail = &TAIL;
        head->next = tail;
        tail->pre = head;
    }
   
    ~LRUCache(){

    }

    void remove(Node* now){
        now->pre->next = now->next;
        now->next->pre = now->pre;
    }

    void add(Node* now){
        now->next = head->next;
        now->pre = head;
        //
        now->next->pre = now;
        now->pre->next = now;
    }

    Node* find(int key){

        if(m.find(key) == m.end()){
            return tail;
        }
        return m[key];

        /*
        Node* now = head->next;
        tail->key = key;
        while(now->key != key){
            now = now->next;
        }
        return now;
        */
    }

    int get(int key) {
        Node* now = find(key);

        if(now == tail){
            return -1;
        }

        remove(now);
        add(now);

        return now->val;
    }
    
    Node* newNode(int key, int value){
        Node* now = NULL;
        if(this->length == this->capacity){
            now = tail->pre;
            remove(now);
            m.erase(now->key);
        }else{
            now = new Node;
            this->length++;
        }
        m[key] = now;
        now->key = key;
        now->val = value;

        return now;
    }

    void set(int key, int value) {
        Node* now = find(key);

        if(now != tail){
            remove(now);
            add(now);
            now->val = value;
            return;
        }

        now = newNode(key, value);
        add(now);
    }
};


void test(){
    LRUCache work(3);
    printf("find = %d\n", work.get(1));
    work.set(1,1);
    printf("find = %d\n", work.get(2));
    work.set(2,2);
    printf("find = %d\n", work.get(1));
    work.set(3,3);
    work.set(4,4);
    printf("find = %d\n", work.get(4));
    printf("find = %d\n", work.get(1));


}

int main(){
    
    test();

   return 0;
}
