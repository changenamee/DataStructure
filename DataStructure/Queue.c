#include<stdio.h>
#include<stdlib.h>

typedef struct n{
    int data;
    struct n *next;
}QueueNode;
typedef struct nn{
    QueueNode *front,*rear; //队首，队尾
}Queue;

//初始化队列
Queue *InitQueue(){
    Queue *q;
    QueueNode *p;
    q = (Queue*)malloc(sizeof(Queue));
    p = (QueueNode*)malloc(sizeof(QueueNode));
    p->next = NULL;
    q->front = p;
    q->rear = p;
    return q;
}
//入队
int PushQueue(Queue *q,int data){
    QueueNode *p;
    p = (QueueNode*)malloc(sizeof(QueueNode));
    if(!p) return -1;
    p->data = data;
    p->next = NULL;
    q->rear->next = p;
    q->rear = p;
    return 1;
}

//判断队空
int EmptyQueue(Queue *q){
    if(q->rear == q->front){
        return 1;
    }
    return 0;
}
//出队
int PopQueue(Queue *q,int *data){
    if(EmptyQueue(q)){
        printf("队空\n");
        return -1;
    }
    QueueNode *p;
    p = q->rear->next;
    q->rear->next = p->next;
    *data = p->data;
    free(p);
    if(q->front->next == NULL){
        q->rear = q->front;
    }
    return 1;
}