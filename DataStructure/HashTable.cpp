#include<iostream>
#include<stdlib.h>
#define HASHSIZE 12
#define N -334
using namespace std;

typedef struct{
    int *elem;  //存储元素
    int count;  //哈希表中元素个数
}HashTable;

int InitHash(HashTable *h){
    h->elem = (int*)malloc(sizeof(int) * HASHSIZE);
    //初始化哈希表中元素
    for(int i=0;i<HASHSIZE;i++)
        h->elem[i] = N;
    h->count = HASHSIZE;
    return 1;
}

//线性构造函数
int Hash(int key){
    return key%HASHSIZE;
}

//插入元素
void InsertElem(HashTable *h,int key){
    int addr = Hash(key);
    //出现冲突,线性探测
    if(h->elem[addr] != N){
        addr = (addr+1)%HASHSIZE;
    }
    h->elem[addr] = key;
}

//查找元素
int SearchElem(HashTable *h,int key,int *addr){
    *addr = Hash(key);
    while(h->elem[*addr] != key){
        *addr = (*addr + 1) % HASHSIZE; //线性探测

        if(h->elem[*addr]==N || h->elem[*addr] == Hash(key)){
            return -1;
        }
    }
    return 1;
}