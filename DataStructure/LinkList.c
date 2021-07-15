/* #include<stdio.h>
#include<stdlib.h>
//链表结构
typedef struct node{
  int data;
  struct node *next;
}Node;
//插入数据
void InsertData(Node **n,int data){
  Node *t;
  t = (Node*)malloc(sizeof(Node));
  if(!t)
    return;
  t->data = data;
  t->next = NULL;
  if(!*n){ //链表为空
    *n = t;
    return;
  }
  Node *cur = *n;
  while(cur->next)  //找到尾节点
    cur = cur->next;
  cur->next = t;
}
//遍历链表
void PrintList(Node *n){
  while(n){
    printf("%d\t",n->data);
    n = n->next;
  }
  printf("\n");
}
//链表长度
int lengthList(Node *n){
  int cnt = 0;
  while(n){
    cnt++;
    n = n->next;
  }
  return cnt;
}
//查找节点
Node *FindNode(Node* n,int data){
  Node *t = NULL;
  while(n && !t){
    if(n->data == data)
      t = n;
    n = n->next;
  }
  return t;
}
//得到中间节点
Node *GetMiddleNode(Node *n){
  Node *mid = n,*cnt = n;
  while(cnt){
    cnt = cnt->next;
    if(cnt)
      cnt = cnt->next;
    if(cnt)
      mid = mid->next;
  }
  return mid;
}
//删除节点
int DeleteNode(Node *n,int c){
  int i=1;
  Node *t = n,*p;
  while(i<c && t){
    i++;
    t = t->next;
  }
  p = t->next;
  t->next = p->next;
  free(p);
  return 1;
}

//合并两个链表
Node * MergeList(Node *n1,Node *n2){
  Node *cur1 = n1,*cur2 = n2; 
  Node *newlist = NULL,*newlistCur = NULL,*selected;
  while(cur1 && cur2){
    if(cur1->data < cur2->data){
      selected = cur1;
      cur1 = cur1->next;
    }else{
      selected = cur2;
      cur2 = cur2->next;
    }

    if(!newlist){
      newlist = selected;
      newlistCur = newlist;
    }else{
      newlistCur->next = selected;
      newlistCur = newlistCur->next;
    }
  }
  if(cur1){
    if(!newlistCur){
      newlist = cur1;
    }else{
      newlistCur->next = cur1;
    }
  }
  if(cur2){
    if(!newlistCur){
      newlist = cur2;
    }else{
      newlistCur->next = cur2;
    }
  }
  return newlist;
}
int main(void){
  Node *n = NULL,*f,*mid;
  for(int i=0;i<11;i++)
    InsertData(&n,i);
  PrintList(n);
  printf("length:%d\n",lengthList(n));
  f = FindNode(n,2);
  printf("f data:%d\n",f->data);
  mid = GetMiddleNode(n);
  printf("mid data:%d\n",mid->data);
  DeleteNode(n,2);
  PrintList(n);
  return 0;
} */

#include<stdio.h>
#include<stdlib.h>

typedef struct n{
  int data;
  struct n *next;
}List;

List *AddNode(List *l){
  List *temp = NULL,*p = l;
  temp = (List*)malloc(sizeof(List));
  if(!l){
    l = temp;
  }else{
    while(p->next != NULL)
      p = p->next;
    p->next = temp;
  }
  temp->data = 1;
  temp->next = NULL;
  return l;
}

void ShowList(List *l){
  while(l != NULL){
    printf("%d\n",l->data);
    l = l->next;
  }
}
int main(void){
  List *l = NULL;
  l = AddNode(l);
  l = AddNode(l);
  l = AddNode(l);
  ShowList(l);
}