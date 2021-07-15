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
    LinkList p,q;
    if(n<0) return ERROR;
    L=NULL;
    p = L;
    for(int i=0;i<n;++i){
        q = (LNode*)malloc(sizeof(LNode));
        q->data = data[i];
        q->next = NULL;
        if(!q)  return ERROR;
        if(p==NULL) L = q;
        else    p->next = q;
        p = q;
    }
    return OK;
}

Status push(LinkList &L,EleType val){
    if(L==nullptr){
        L = (LNode*)malloc(sizeof(LNode));
        L->data = val;
        L->next = nullptr;
    }else{
        LNode* p,*q;
        p = (LNode*)malloc(sizeof(LNode));
        p->data = val;
        p->next = nullptr;
        q = L;
        while(q->next!=nullptr){
            q = q->next;
        }
        q->next = p;
    }
    return OK;
}

Status pop(LinkList &L,EleType& val){
    if(L==nullptr)  return ERROR;
    //LinkList p;
    //p = L;
    val = L->data;
    L = L->next;
    //free(p);
    return OK;
}

void print(LinkList &L){
    if(L==nullptr)  return;
    LinkList p = L;
    while(p){
        cout<<p->data<<" ";
        p = p->next;
    }
    cout<<endl;
}

int main(void){
    EleType arr[LONGTH] = {1,2,3,4,5};
    LinkList L;
    EleType val = 0;
    init(L,arr,5);
    push(L,18);
    print(L);
    pop(L,val);
    cout<<val<<endl;
    print(L);
}