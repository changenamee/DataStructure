#include<iostream>
#include<string>
#define MAXVALUE 10000  //寻找最小节点
#define MAXBIT 100
#define MAXLEAF 30  //最大叶子节点个数
#define MAXNODE 2*MAXLEAF-1 //节点个数
using namespace std;
//节点结构
typedef struct{
    int parent,lchild,rchild;
    double weight;
    char value;
}HuffmanNode;
//编码结构
typedef struct{
    int bit[MAXBIT];
    int start;  //开始编码的下标
}HuffmanCode;

//节点数组
HuffmanNode Huffman[MAXNODE];
//编码数组
HuffmanCode HuffCode[MAXLEAF];

//创建哈夫曼树
void CreateHuff(HuffmanNode Huffman[MAXNODE],int arr[],int n){
    int i,j,k;
    int p1,p2;
    int min1,min2;
    //初始化哈夫曼树
    for(i=0;i<n;i++){
        Huffman[i].parent = -1;
        Huffman[i].lchild = -1;
        Huffman[i].rchild = -1;
        Huffman[i].weight = 0;
    }
    for(i=0;i<256;i++){
        if(arr[i] != 0){
            Huffman[i].weight = arr[i];
            Huffman[i].value = i+'a';
        }
    }
    //建立树  
    for(i=0;i<n-1;i++){
        min1 = min2 = MAXVALUE;
        p1 = p2 = 0;
        for(j=0;j<n+i;j++){
            //寻找权值最小的两个节点
            if(Huffman[j].weight < min1 && Huffman[j].parent == -1){
                min2 = min1;
                p2 = p1;
                min1 = Huffman[j].weight;
                p1 = j;
            }else if(Huffman[j].weight < min2 && Huffman[j].parent == -1){
                min2 = Huffman[j].weight;
                p2 = j;
            }
        }
        //添加节点
        Huffman[n+i].weight = min1+min2;
        Huffman[n+i].lchild = p1;
        Huffman[n+i].rchild = p2;
        Huffman[n+i].parent = -1;
        Huffman[p1].parent = n+i;
        Huffman[p2].parent = n+i;
    }
}
//建立哈夫曼编码
void CreateHuffCode(HuffmanCode HuffCode[MAXLEAF],int n){
    HuffmanCode temp;   //临时变量
    int i,j,c,p;
    for(i=0;i<n;i++){
        temp.start = n-1;
        c = i;
        p = Huffman[c].parent;
        while(p != -1){
            if(Huffman[p].lchild == c){
                temp.bit[temp.start] = 0;
            }else{
                temp.bit[temp.start] = 1;
            }
            temp.start--;
            c = p;
            p = Huffman[c].parent;
        }
        for(j=temp.start+1;j<n;j++){
            HuffCode[i].bit[j] = temp.bit[j];
        }
        HuffCode[i].start = temp.start;
    }
    //输出编码
    for(i=0;i<n;i++){
        cout<<Huffman[i].value<<"的编码是:";
        for(j=HuffCode[i].start+1;j<n;j++)
            cout<<HuffCode[i].bit[j];
        cout<<endl;
    }
}

int main(void){
    int arr[7] = {31,16,10,8,11,20,4};
    CreateHuff(Huffman,arr,7);
    CreateHuffCode(HuffCode,7);
}