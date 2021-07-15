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

typedef struct{
    EleType *elem;
    int top;
    int size;
    int incre;
}SeqStack;

//初始化
Status initSeqStack(SeqStack& sq,int size,int inc) {
    sq.elem = (EleType*)malloc(sizeof(EleType)*size);
    if(sq.elem==NULL)   return OVERFLOW;
    sq.size = size;
    sq.top = 0;
    sq.incre = inc;
    return OK;
}
//入栈
Status push(SeqStack& sq,EleType val){

    EleType* newbase;
    if(sq.top>=sq.size){
        newbase = (EleType*)realloc(sq.elem,sizeof(EleType)*(sq.size+sq.incre));
        if(newbase==NULL)   return OVERFLOW;
        sq.elem = newbase;
        sq.size += sq.incre;
    }
    sq.elem[sq.top++] = val;
    return OK;
}

//判断栈空
Status empty(SeqStack& sq){
    if(0==sq.top)   return TRUE;
    return FALSE;
}

//清空栈
Status clear(SeqStack& sq){
    if(sq.top==0)   return OK;
    sq.size=0;
    sq.top=0;
    return OK;
}
//销毁栈
Status destroy(SeqStack& sq){
    free(sq.elem);
    sq.elem = NULL;
    return OK;
}
//取栈顶
EleType top(SeqStack& sq){
    if(0==sq.top)   return ERROR;
    return sq.elem[sq.top-1];
}
//出栈
void pop(SeqStack& sq){
    if(0==sq.top)   return;
    sq.top--;
    return;
}

int main(void){
    SeqStack s;
    EleType arr[LONGTH] = {1,2,3,4,5};
    if(!initSeqStack(s,LONGTH,LONGTH))
        return -1;
    for(int i=0;i<LONGTH;++i){
        push(s,arr[i]);
    }
    while(!empty(s)){
        cout<<top(s)<<" ";
        pop(s);
    }
    cout<<endl;
    if(empty(s))    cout<<"stack is empty"<<endl;
    else cout<<"stack is not empty"<<endl;
    destroy(s);
}