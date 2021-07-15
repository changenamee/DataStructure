#include<stdio.h>
#include<stdlib.h>

typedef struct Poly{
    float coef;   //系数
    int expon;  //指数
    struct Poly *next;
}Poly,*PolyPoin;

PolyPoin createPoly(PolyPoin *p,int m);
void printPoly(PolyPoin p);
PolyPoin addPoly(PolyPoin p1,PolyPoin p2);
//创建多项式
PolyPoin createPoly(PolyPoin *p,int m){
    PolyPoin t,r;
    r = *p = (Poly*)malloc(sizeof(Poly));
    (*p)->next = NULL;
    while(m--){
        t = (Poly*)malloc(sizeof(Poly));
        printf("输入系数和指数：");
        scanf("%f %d",&t->coef,&t->expon);
        r->next = t;
        t->next = NULL;
        r = t;
    }
    r->next = NULL;
    return *p;
}
//输出多项式
void printPoly(PolyPoin p){
    PolyPoin t = p->next;
    if(!t){
        printf("0\n");
        return;
    }
    while(t){
        if(t->expon==0){
            printf("%.2f",t->coef);
        }else
            printf("%.2fX^%d",t->coef,t->expon);
        t = t->next;
        if(t!=NULL)
            if(t->coef>0) printf("+");
    }
    printf("\n");
}

//多项式相加
PolyPoin addPoly(PolyPoin p1,PolyPoin p2){
    PolyPoin head,end;
    PolyPoin x,y;
    x = p1->next;
    y = p2->next;
    head = end = (Poly*)malloc(sizeof(Poly));
    head->next = NULL;
    while(x && y){
        //x指数小于y，x存到尾指针，x向后移
        if(x->expon < y->expon){
            end->next = x;
            end = x;
            x = x->next;
        }//x指数大于y，y存到尾指针，y向后移
        else if(x->expon > y->expon){
            end->next = y;
            end = y;
            y = y->next;
        }else{
            //两指数相等，系数相加,都往后移动
            if(0!=(x->coef+y->coef)){
                x->coef = x->coef+y->coef;
                end->next = x;
                end = x;
            }
            x = x->next;
            y = y->next;
        }
    }
    //将剩余项添加到尾指针
    if(x){
        end->next = x;
        end = x;
        x = x->next;
    }
    if(y){
        end->next = y;
        end = y;
        y = y->next;
    }
    return head;
}

int main(void){
    PolyPoin p,q,result;
    int m,n;
    printf("第一个多项式个数：");
    scanf("%d",&m);
    createPoly(&p,m);
    printPoly(p);
    printf("第二个多项式个数：");
    scanf("%d",&n);
    createPoly(&q,n);
    printPoly(q);
    result = addPoly(p,q);
    printf("相加结果：");
    printPoly(result);
}