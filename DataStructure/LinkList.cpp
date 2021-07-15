#include<iostream>
#include<vector>
#include"Node.h"
using namespace std;
template<typename T>
class LinkList{
    public:
        LinkList(); //默认构造函数
        LinkList(const T *d,int n); //把数组d复制给链表
        LinkList(const LinkList &list); //拷贝
        LinkList & operator =(const LinkList &list);    //赋值
        ~LinkList();
        void Clear();   //清空链表空间
        int GetLength();    //链表长度
        int AddData(const T &d);    //在链表末尾加数据
        int InsertData(int i,const T &d); //在第I个位置上插入数据
        int ChangeData(const T &d,int i);   //在第i位置上data设置为d
        int GetData(T &d,int i);    //查找第i个位置上的数据
        int DeleteData(int i);  //删除第i个节点
        void ShowList();    //遍历链表
    private:
        NODE<T> *head;  //链表头结点
        int length; //链表长度

};

template<typename T>
LinkList<T>::LinkList(){
    head = new NODE<T>;
    length = 0;
}

template<typename T>
LinkList<T>::LinkList(const T *d,int n){
    head = new NODE<T>;
    NODE<T> *p = head;
    for(int i=0;i<n;i++){
        p->next = new NODE<T>(d[i]);
        p = p->next;
    }
    length = n;
}
//赋值
template<typename T>
LinkList<T> & LinkList<T>:: operator =(const LinkList &list){
    Clear();
    length = list.length;

    NODE<T> *q = list.head->next,*p = head;
    while(q){
        p->next = new NODE<T>(q->data);
        q = q->next;
        p = p->next;
    }
    return *this;
}
//拷贝
template<typename T>
LinkList<T>::LinkList(const LinkList &list){
    length = list.length;
    head = new NODE<T>;
    NODE<T> *q = list.head->next,*p = head;
    while(q){
        p->next = new NODE<T>(p->data);
        q = q->next;
        p = p->next;
    }
}
//得到链表长度
template<typename T>
int LinkList<T>::GetLength(){
    return length;
}
//清空链表空间
template<typename T>
void LinkList<T>::Clear(){
    NODE<T> *p = head->next;
    while(p){
        head->next = p->next;
        delete p;
        p = head->next;
    }
}
//析构函数，释放空间 
template<typename T>
LinkList<T>::~LinkList(){
    Clear();
    delete head;
}
template<typename T>
int LinkList<T>::AddData(const T &d){
    NODE<T> *p = head;
    while(p->next)  //在末尾添加数据
        p = p->next;
    p->next = new NODE<T>(d);
    length++;
    return 1;

}
template<typename T>
int LinkList<T>::ChangeData(const T &d,int i){
    NODE<T> *p = head->next;
    if(i<1||i>length){
        cout<<"改变的位置错误\n";
        return -1;
    }
    for(int cnt=1;cnt<i;cnt++)
        p = p->next;
    p->data = d;
    return 1;
}
//在第I上插入数据
template<typename T>
int LinkList<T>::InsertData(int i,const T &d){
    NODE<T> *p = head,*q;
    if(i<1||i>length+1){
        cout<<"插入位置错误"<<endl;
        return -1;
    }
    for(int cnt=1;cnt<i;cnt++){
        p = p->next;
    }
    q = new NODE<T>(d,p->next);
    p->next = q;
    length++;
    return 1;


}
//获取第i个位置的数据
template<typename T>
int LinkList<T>::GetData(T&d,int i){
    NODE<T> *p = head->next;
    cout<<"*p:"<<p->data<<endl;
    if(i<0||i>length){
        cout<<"数据的位置错误\n";
        return -1;
    }
    for(int cnt=1;cnt<i;cnt++){
        cout<<"cnt:"<<cnt<<" ";
        p = p->next;
    }
    d = p->data;
    return 1;
}
//删除第i个节点
template<typename T>
int LinkList<T>::DeleteData(int i){
    NODE<T> *p = head;
    cout<<"*p:"<<p->data<<endl;
    if(i<1||i>length){
        cout<<"删除的位置错误\n";
        return -1;
    }
    for(int cnt=1;cnt<i;cnt++)
        p = p->next;
    NODE<T> *q = p->next;
    p->next = q->next;
    delete q;
    length--;
    return 1;
}
//遍历链表
template<typename T>
void LinkList<T>::ShowList(){
    NODE<T> *p = head->next;
    if(!p){
        cout<<"链表为空"<<endl;
        return;
    }
    while(p){
        cout<<p->data<<"-->";
        p = p->next;
    }
    cout<<endl;
}

int main(void){
    vector<int> a;
    
    return 0;
}