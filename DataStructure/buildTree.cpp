#include <iostream>
#include<queue>
using namespace std;

typedef struct node{
    int val;
    struct node *left,*right;
}Node,*BST;

bool insert(Node* &p,int v){
    if(!p){
        p = new Node;
        p->val = v;
        p->left = p->right = nullptr;
        return true;
    }
    if(p->val==v)   return false;
    if(p->val<v)    return insert(p->right,v);
    else return insert(p->left,v);
}

void create(Node* &p,int a[],int n){
    p=nullptr;
    for(int i=0;i<n;++i){
        insert(p,a[i]);
    }
}

void per(BST T){
    if(!T)  return ;
    cout<<T->val<<"\t";
    per(T->left);
    per(T->right);
}
void in(BST T){
    if(!T)  return;
    in(T->left);
    cout<<T->val<<"\t";
    in(T->right);
}

int main(void){
    int a[10] = {4, 5, 2, 1, 0, 9, 3, 7, 6, 8};
    Node* p;
    create(p,a,10);
    per(p);
    cout<<endl;
    in(p);
}