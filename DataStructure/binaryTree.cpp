/* 
    全是递归
 */
#include<iostream>
using namespace std;
typedef char treeType;
//二叉树结构
typedef struct n{
    treeType data;
    struct n *lchild;
    struct n *rchild;
}BTree;

//二叉树初始化
void InitTree(BTree **t){
    if(t == NULL) return;
    *t = NULL;
}
//先序遍历
void PreOrder(BTree *t){
    //空树
    if(t == NULL){
        printf("##\n");
        return;
    }
    printf("%c->",t->data);
    PreOrder(t->lchild);
    PreOrder(t->rchild);
}
//中序遍历
void InOrder(BTree *t){
    //空树
    if(t == NULL){
        printf("##\n");
        return;
    }
    InOrder(t->lchild);
    printf("%c->",t->data);
    InOrder(t->rchild);
}
//后序遍历
void PostOrder(BTree *t){
    if(t == NULL){
        printf("##\n");
        return;
    }
    PostOrder(t->lchild);
    PostOrder(t->rchild);
    printf("%c->",t->data);
}
// 求二叉树节点个数
int GetNodeCount(BTree *t){
    int count = 0;
    if(t == NULL){
        printf("tree is null\n");
        return -1;
    }
    count++;
    GetNodeCount(t->lchild);
    GetNodeCount(t->rchild);
    return count;
}

//求叶子节点个数
int GetLeafNodeCount(BTree *t){
    int count = 1;
    if(t == NULL) return -1;
    if(t->rchild == NULL && t->lchild == NULL){
        count++;
    }
    GetLeafNodeCount(t->lchild);
    GetLeafNodeCount(t->rchild);
    return count;
}
//求第k层节点个数
int KNodeCount(BTree *t,int k){
    if(k<1) return -1;
    if(t == NULL) return -1;
    if( k == 1){
        return 1;
    }
    return KNodeCount(t->lchild,k-1) + KNodeCount(t->rchild,k-1);
}

//求树的深度
int DepthTree(BTree *t){
    if(t == NULL) return -1;
    if(t->lchild == NULL && t->rchild == NULL){
        return 1;
    }
    int ldepth = DepthTree(t->lchild);
    int rdepth = DepthTree(t->rchild);
    return ldepth>rdepth ? ldepth : rdepth;
}

//查找指定节点的地址
BTree *FindAdd(BTree *t,int data){
    if(t == NULL) return NULL;
    if(t->data == data){
        return t;
    }
    BTree *lf = FindAdd(t->lchild,data);
    BTree *rf = FindAdd(t->rchild,data);
    return lf == NULL ? rf : lf;
}
//查找指定节点的双亲节点
BTree *FindPar(BTree *t,BTree *node){
    if(t == NULL) return NULL;
    if(t->lchild == node || t->rchild == NULL) return t;

    BTree *lp = FindPar(t->lchild,node);
    BTree *rp = FindPar(t->rchild,node);
    return lp==NULL ? rp : lp;
}

//销毁一棵树
void DestroyTree(BTree **t){
    if(t == NULL)   return;
    if(*t == NULL)  return;
    DestroyTree(&(*t)->lchild);
    DestroyTree(&(*t)->rchild);
    free(*t);
    *t = NULL;
}