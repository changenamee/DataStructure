#include<stdio.h>
#include<stdlib.h>
typedef struct Node{
    int num;    //编号
    struct Node *next;
}List;
void Joseph(int n,int m,int k){
    List *head,*node,*p;
    if(n==0){
        printf("链表为空\n");
        return;
    }
    for(int i=1;i<=n;i++){
        if(i==1){   //头结点
            head = p = (List*)malloc(sizeof(List));
            if(!head) return;
        }else{
            node = (List*)malloc(sizeof(List));
            if(!node) return;
            p->next = node;
            p = node;
        }
        p->num = i;
    }
    p->next = head; //循环链表
    p = head;
    for(int j=1;j<k;j++,p=p->next); //从第k个人开始报数
    for(int i=1;i<=n;i++){    //n个人全部出队
        for(int j=1;j<m;j++,p=p->next); //报m的人出队
        printf("%d ",p->num);
        p->num = p->next->num;
        node = p->next; //删除报m的人节点
        p->next = node->next;
        free(node);
    }
    printf("\n\n全部出链表\n");
}

int main(void){
    int n,m,k;
    printf("人数:"); scanf("%d",&n);
    printf("上限值m:"); scanf("%d",&m);
    printf("开始报数的人:"); scanf("%d",&k);
    printf("出列顺序:");
    Joseph(n,m,k);
    return 0;
}
