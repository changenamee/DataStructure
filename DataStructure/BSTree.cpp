#include<iostream>
using namespace std;

//二叉树节点结构
template<class T>
class BSNode{
    public:
        T key;
        BSNode *left;
        BSNode *right;
        BSNode *parent;
        BSNode(T value,BSNode *p,BSNode *l,BSNode *r):
            key(value),parent(),left(l),right(r) {}
};

template<class T>
class BSTree{
    private:
        BSNode<T> *root;    //根节点
    public:
        //外部接口
        BSTree(){
            root = NULL;
        }
        ~BSTree();

        void preorder();    //前序遍历
        void inorder(); //中序遍历
        void postorder();   //后序遍历

        T min();    //查找最小值
        T max();    //查找最大值

        BSNode<T>* search(T x); //查找二叉树中节点key值为x的节点(递归)
        BSNode<T>* searchN(T x);    //非递归
        BSNode<T>* successsor(BSNode<T>* x);    //查找后继节点
        BSNode<T>* predecessor(BSNode<T>* x);   //查找前驱结点

        void insert(T x);   //插入
        void remove(T x);   //删除

        void destory(); //销毁二叉树
        void print();   //打印二叉树
    private:
        //内部接口
        void preorder(BSNode<T> *tree)  const;   //前序遍历
        void inorder(BSNode<T> *tree)   const;  //中序遍历
        void postorder(BSNode<T> *tree) const;  //后序遍历

        BSNode<T>* min(BSNode<T> *tree);    //返回最小值
        BSNode<T>* max(BSNode<T> *tree);    //返回最大值

        BSNode<T>* search(BSNode<T>* tree,T key) const;   //查找二叉树tree中值为key的节点（递归）
        BSNode<T>* searchN(BSNode<T>* tree,T key) const;   //查找二叉树tree中值为key的节点（非递归）

        void insert(BSNode<T>* &tree,BSNode<T>* t); //将节点t插入到二叉树tree中
        BSNode<T>* remove(BSNode<T>* &tree,BSNode<T>* t); //将节点t从二叉树tree中删除

        void destory(BSNode<T>* &tree);   //销毁二叉树tree
        void print(BSNode<T>*tree,T key,int directon);  //打印二叉树
};
//前序遍历
template<class T>
void BSTree<T>::preorder(BSNode<T> *tree) const{
    if(tree == NULL) return;
    cout<<tree->key<<" ";
    preorder(tree->left);
    preorder(tree->right);
}
template<class T>
void BSTree<T>::preorder(){
    preorder(root);
}

//中序遍历
template<class T>
void BSTree<T>::inorder(BSNode<T>* tree) const{
    if(tree == NULL) return;
    inorder(tree->left);
    cout<<tree->key<<" ";
    inorder(tree->right);
}
template<class T>
void BSTree<T>::inorder(){
    inorder(root);
}

//后序遍历
template<class T>
void BSTree<T>:: postorder(BSNode<T> *tree) const{
    if(tree == NULL)    return;
    postorder(tree->left);
    postorder(tree->right);
    cout<<tree->key<<" ";
}
template<class T>
void BSTree<T>::postorder(){
    postorder(root);
}

//递归查找
template<class T>
BSNode<T> * BSTree<T>::search(BSNode<T>* t,T key) const{
    if(t == NULL || t->key == key) return t;
    if(key < t->key)
        search(t->left,key);
    else
        search(t->right,key);
}
template<class T>
BSNode<T>* BSTree<T>::search(T key){
    search(root,key);
}

//非递归
template<class T>
BSNode<T>* BSTree<T>::searchN(BSNode<T>* t,T key) const{
    while(t != NULL && t->key != key){
        if(key < t->key)    t = t->left;
        else t = t->right;
    }
    return t;
}
template<class T>
BSNode<T>* BSTree<T>:: searchN(T key){
    search(root,key);
}
//最小值
template<class T>
BSNode<T>* BSTree<T>::min(BSNode<T>* t){
    if(t == NULL) return NULL;
    while(t->left)
        t = t->left;
    return t;
}
template<class T>
T BSTree<T>::min(){
    BSNode<T> *temp = min(root);
    if(temp != NULL)
        return temp->key;
    return 0;
}

//最大值
template<class T>
BSNode<T>* BSTree<T>::max(BSNode<T>* t){
    if(t == NULL) return NULL;
    while(t->right)
        t = t->right;
    return t;
}
template<class T>
T BSTree<T>::max(){
    BSNode<T> *temp = max(root);
    if(temp != NULL)
        return temp->key;
    return 0;
}

//前驱结点
template<class T>
BSNode<T>* BSTree<T>:: predecessor(BSNode<T>* x){
    //有左孩子，则它的前驱节点是以左孩子为根节点的二叉树中的最大值
    if(x->left)
        return max(x->left);
    //没有左孩子
    //(1)节点是一个”右孩子“，那么它的前驱结点是它的父节点
    //(2)节点是一个”左孩子“，那么它的前驱结点是它的父节点中有右孩子的节点
    BSNode<T> *y = x->parent;
    while(y!=NULL && x == y->left){
        x = y;
        y = y->parent;
    }
    return y;
}

//后继结点
template<class T>
BSNode<T>* BSTree<T>:: successsor(BSNode<T>* x){
    //有右孩子，则它的后继节点是以右孩子为根节点的二叉树中的最小值
    if(x->right)
        return min(x->right);
    //没有右孩子
    //(1)节点是一个”右孩子“，那么它的后继结点是它的父节点中有左孩子的节点
    //(2)节点是一个”左孩子“，那么它的后继结点是它的父节点
    BSNode<T> *y = x->parent;
    while(y!=NULL && x == y->right){
        x = y;
        y = y->parent;
    }
    return y;
}

//将z节点插入到以tree为根节点的二叉树中
template<class T>
void BSTree<T>::insert(BSNode<T> *&tree,BSNode<T>* z){
    BSNode<T> *x = tree;
    BSNode<T> *y = NULL;
    //查找要插入的节点
    while(x != NULL){
        y = x;
        if(z->key < x->key)
            x = x->left;
        else    x = x->right;
    }

    z->parent = y;
    if(y == NULL)   tree = z;
    else if(z->key < y->key)
        y->left = z;
    else y->right = z;
}
template<class T>
void BSTree<T>::insert(T key){
    BSNode<T> *z = NULL;
    if((z = new BSNode<T>(key,NULL,NULL,NULL)) == NULL) return;
    insert(root,z);
}
//删除节点
template<class T>
BSNode<T>* BSTree<T>::remove(BSNode<T>* &tree,BSNode<T>* z){
    BSNode<T>* x = NULL;
    BSNode<T>* y = NULL;

    //要删除的节点
    //如果z没有左右孩子，则直接删除
    //如果z有左孩子或右孩子则删除其后继节点，再将后继节点补到要删除的节点位置
    if(z->left==NULL || z->right==NULL)
        y = z;
    else y = successsor(z);

    //x表示要替代删除节点的节点
    if(y->left != NULL) x = y->left;
    else x = y->right;

    if(x != NULL)
        x->parent = y->parent;
    //要删除的节点是根节点
    if(y->parent == NULL)
        tree = y;
    else if(y == y->parent->left)   //要删除的节点是其父节点的左孩子
        y->parent->left = x;
    else y->parent->right = x;  //要删除的节点是其父节点的右孩子

    if(y != z)  y->key = z->key;    

    return y;

}

//打印二叉树
template<class T>
void BSTree<T>::print(BSNode<T>*tree,T key,int direction){
    if(tree != NULL){
        if(direction == 0) //根节点
            cout<<tree->key<<" is root\n";
        else    //子节点
            cout<<tree->key<<" is "<<key<<"'s "<<(direction==1? "right child" : "left child")<<endl;
        print(tree->left,tree->key,-1);
        print(tree->right,tree->key,1);
    }
}
template<class T>
void BSTree<T>::print(){
    if(root != NULL)
        print(root,root->key,0);
}

//销毁二叉树
template<class T>
void BSTree<T>::destory(BSNode<T>* &tree){
    if(tree == NULL)    return;
     
    if(tree->left != NULL)
        destory(tree->left);

    if(tree->right != NULL)
        detory(tree->right);
    
    delete tree;
    tree = NULL;
}
template<class T>
void BSTree<T>::destory(){
    destory(root);
}


int main(void){
    int arr[] = {1,2,13,23,44,7};
    int len = sizeof(arr)/sizeof(arr[0]);
    BSTree<int>* tree = new BSTree<int>();
    //
    cout<<"insert"<<endl;
    for(int i=0;i<len;i++)
        tree->insert(arr[i]);
    //前序遍历
    cout<<"preorder:";
    tree->preorder();
    //中序遍历
    cout<<"\ninorder:";
    tree->inorder();
    //后序遍历
    cout<<"\npostorder:";
    tree->postorder();
    
    cout<<"max:"<<tree->max()<<endl;
    cout<<"min:"<<tree->min()<<endl;

    cout<<"tree:"<<endl;
    tree->print();

    return 0;

}