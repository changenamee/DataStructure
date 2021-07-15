#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<memory.h>
#include<iostream>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -1
using namespace std;
#define LONGTH 5    //测试长度
typedef int Status;
typedef int EleType;

typedef struct LNode{
    EleType data;
    struct LNode* next;
}LNode,*LinkList;

Status init(LinkList &L,EleType* data,int n){
    if(n<0) return ERROR;
    LinkList p,q;
    p = L = nullptr;
    q = (LNode*)malloc(sizeof(LNode));
    if(q==nullptr)  return OVERFLOW;
    p = L = q;
    for(int i=0;i<n;++i){
        q = (LNode*)malloc(sizeof(LNode));
        if(q==nullptr)  return OVERFLOW;
        q->data = data[i];
        q->next = nullptr;
        
        p->next = q;
        p = q;
    }
    return OK;
}
Status push(LinkList& L,EleType val){
    LinkList p,q;
    q = (LNode*)malloc(sizeof(LNode));
    q->data = val;
    q->next = nullptr;
    if(L==nullptr){
        L = (LNode*)malloc(sizeof(LNode));
        if(L==nullptr)  return OVERFLOW;
        L->next = q;
    }else if(L->next == nullptr){
        L->next = q;
    }else{
        p = L;
        while(p->next!=nullptr){
            p = p->next;
        }
        p->next = q;
    }
    return OK;
}
Status pop(LinkList& L,EleType &val){
    if(L==nullptr || L->next==nullptr)  return ERROR;
    LinkList p = L;
    val = p->next->data;
    L->next = p->next;
    free(p);
    return OK;
}

void print(LinkList& L){
    if(L==nullptr || L->next==nullptr)  return;
    LinkList p = L->next;
    while(p){
        cout<<p->data<<" ";
        p=p->next;
    }
    cout<<endl;
}

int main(void){
    EleType val[LONGTH] = {1,2,3,4,5};
    LinkList L;
    init(L,val,LONGTH);
    print(L);
    int cnt = 18;
    for(int i=0;i<LONGTH;++i)
        push(L,cnt++);
    print(L);
    EleType v;
    pop(L,v);
    cout<<v<<endl;
}