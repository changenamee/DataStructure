#include<iostream>
#include<unordered_map>
using namespace std;

struct DLinkedList{
    int key,val;
    DLinkedList* prev;
    DLinkedList* next;
    DLinkedList():key(0),val(0),prev(nullptr),next(nullptr){}
    DLinkedList(int _key,int _val):key(_key),val(_val),prev(nullptr),next(nullptr){}
};
class LRU{
private:
    int size;
    int capacity;
    DLinkedList* head;
    DLinkedList* tail;
    unordered_map<int,DLinkedList*> cache;
public:
    LRU(int cap):size(0),capacity(cap){
        head = new DLinkedList();   //哑结点
        tail = new DLinkedList();
        head->next=tail;
        tail->prev=head;
    }
    int get(int key);
    void put(int key,int val);
    void moveHead(DLinkedList*);
    void removeNode(DLinkedList*);
    void addHead(DLinkedList*);
    DLinkedList* delTail();
};
int LRU::get(int key){
    //不存在
    if(!cache.count(key)){
        return -1;
    }
    DLinkedList* node=cache[key];
    moveHead(node);
    return node->val;
}
void LRU::put(int key,int value){
    //不存在
    if(!cache.count(key)){
        DLinkedList* node=new DLinkedList(key,value);
        cache[key]=head;
        addHead(node);
        ++size;
        if(size>capacity){
            DLinkedList* del = delTail();
            cache.erase(del->key);
            --size;
            delete del;
        }
    }else{  //存在
        DLinkedList* node=cache[key];
        node->val = value;
        moveHead(node);
    }
}
void LRU::addHead(DLinkedList* node){
    node->next = head->next;
    head->next->prev=node;
    head->next=node;
}
void LRU::removeNode(DLinkedList* node){
    node->prev->next = node->next;
    node->next->prev = node->prev;
}
void LRU::moveHead(DLinkedList* node){
    removeNode(node);
    addHead(node);
}
DLinkedList* LRU::delTail(){
    DLinkedList* node = tail->prev;
    removeNode(node);
    return node;
}