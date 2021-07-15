#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXSIZE 1024    //哈弗曼树节点最大个数
#define SSIZE 26    //26个小写字母
//存放各个字母出现的次数，当做权值
int str[SSIZE]={0};
//存放字符串
int cnt=0;  //存放字符个数
//哈夫曼树结构
typedef struct TreeNode{
    int weight; //权值
    int left;
    int right;
    int parent;
    char da;
}TreeNode;
//哈弗曼树，存放各个节点
TreeNode HuffmanTree[MAXSIZE*2-1];
//初始化哈弗曼树
void InitHuffmanTree(TreeNode t[]){
    for(int i=0;i<MAXSIZE*2-1;i++){
        t[i].weight = 0;
        t[i].left = -1;
        t[i].right = -1;
        t[i].parent = -1;

    }
}
//得到各个字符的权值
int GetWeight(TreeNode t[],char *c){
    int m=0;
    int num[SSIZE]={0};
    int len = strlen(c);
    InitHuffmanTree(t);
    if(len==0){
        printf("字符串为空\n");
        return -1;
    }
    //str存储各个字母出现的次数，当做权值
    for(int i=0;i<len;i++){
        str[c[i]-'a']++;
    }
    //计算叶节点个数（权值不为0的字符的个数）
    for(int i=0;i<SSIZE;i++){
        if(str[i]!=0){
            cnt++;
        }
    }
    //字符串为空
    if(cnt==0){
        return -1;
    }
    //分配叶节点的权值
    while(m<cnt){
        for(int j=0;j<SSIZE;j++){
            if(str[j]!=0 && num[j] == 0){
                num[j] = 1;
                t[m].da = j+'a';
                t[m].weight = str[j];
                break;
            }
        }
        m++;
    }
    return 0;
}
//建立哈弗曼树
void CreateTree(TreeNode t[],char *c){
    int x1,x2;  //存放权值最小的两个值
    int p1,p2;  //存放x1,x2的位置
    //初始化哈弗曼树
    GetWeight(t,c);
    for(int i=0;i<cnt-1;i++){
        x1=x2=MAXSIZE;
        p1=p2=0;
        for(int j=0;j<cnt+i;j++){   //找出权值最小的两个节点
            if(t[j].weight < x1 && t[j].parent==-1){    //最小的权值
                x2 = x1; p2 = p1;
                x1 = t[j].weight; p1 = j;
            }else if(t[j].weight < x2 && t[j].parent==-1){  //次小的权值
                x2 = t[j].weight; p2 = j;
            }
        }
        //将两棵权值最小的树合并为一棵树
        t[p1].parent = cnt+i; t[p2].parent = cnt+i;
        t[cnt+i].weight = t[p1].weight+t[p2].weight;
        t[cnt+i].left = p1; t[cnt+i].right = p2;
    }
}

//对字符进行编码
//左子树是0，右子树是1
typedef struct HuffmanCode{
    int bit[SSIZE]; //存放字符的哈夫曼编码
    int start;  //存放字符编码在bit数组中开始的位置
}HuffmanCode;
HuffmanCode code[SSIZE];    //最多SSIZE(26)个字符
void CreateHuffmanCode(TreeNode t[],HuffmanCode c[]){
    HuffmanCode temp;
    int m,p;
    for(int i=0;i<cnt;i++){ //len个叶节点
        temp.start = cnt-1;
        m = i;
        p = t[i].parent;
        while(p!=-1){   //从叶子节点到根节点遍历
            if(t[p].left == m){ //左子树为0，柚子树为1
                temp.bit[temp.start] = 0;
            }else{
                temp.bit[temp.start] = 1;
            }
            temp.start--;
            m = p;  //继续向根节点处走
            p = t[m].parent;
        }
        for(int j=temp.start+1;j<cnt;j++){  //保存求出的字符哈夫曼编码
            c[i].bit[j] = temp.bit[j];
        }
        c[i].start = temp.start+1;
    }
}
//接受电文数据并编码
void GetDataAndCode(char *c){
    printf("输入数据：");
    scanf("%s",c);
    CreateTree(HuffmanTree,c);
    CreateHuffmanCode(HuffmanTree,code);
    printf("\n%s 编码成功\n\n",c);
}
//打印字符与编码的关系
int ShowCharAndCode(){
    char f;
    printf("输入想查找的字符：");
    getchar();
    scanf("%c",&f);
    for(int i=0;i<cnt;i++){
        if(HuffmanTree[i].da == f){
            printf("%c对应的编码:",f);
            for(int j=code[i].start;j<cnt;j++){
                printf("%d",code[i].bit[j]);
            }
            printf("\n\n");
            return 1;
        }
    }
    printf("电文中没有字符%c\n",f);
    return -1;
}
//打印电文以及电文对应的编码
void ShowStringAndCode(char *c){
    printf("电文：%s\n",c);
    printf("编码：");
    int len = strlen(c);
    for(int i=0;i<len;i++){ 
        for(int j=0;j<cnt;j++){
            if(HuffmanTree[j].da == c[i]){
                for(int m=code[j].start;m<cnt;m++){
                    printf("%d",code[j].bit[m]);
                }
            }
        }
    }
    printf("\n");
}
//接受编码数据并译码
void Encoding(TreeNode t[]){
    TreeNode temp = t[2*cnt-2];
    char e;
    getchar();
    printf("输入要译码的哈弗曼编码(输入’#‘结束):");
    e = getchar();
    while(e!='#'){
        if(e == '1'){ //柚子树
            if(temp.right==-1){ //到达叶子节点，输出叶子节点的字符
                printf("%c",temp.da);
                temp = t[2*cnt-2];
                continue;
            }else{  //没到叶子节点，继续向下找
                temp = t[temp.right];
                e = getchar();
            }
        }else if(e == '0'){   //左子树
            if(temp.left==-1){
                printf("%c",temp.da);
                temp = t[2*cnt-2];
                continue;
            }else{
                temp = t[temp.left];
                e = getchar();
            }
        }
    }
    printf("%c",temp.da);
    printf("\n译码成功\n");
}
//菜单
void Menu(){
    printf("选择功能:\n");
    printf("1:接收电文数据(仅由26个小写字母组成)并编码\n");
    printf("2:打印字符与编码的对应关系\n");
    printf("3:打印电文以及该电文对应的编码\n");
    printf("4:接收编码数据并译码\n");
    printf("0:退出\n");
}
int main(void){
    char *c;    //编码的字符
    int choose=0;   //功能选择
    while(1){
        Menu();
        scanf("%d",&choose);
        switch (choose)
        {
        case 1:
            GetDataAndCode(c);
            break;
        case 2:
            ShowCharAndCode();
            break;
        case 3:
            ShowStringAndCode(c);
            break;
        case 4:
            Encoding(HuffmanTree);
            break;
        case 0:
            return 0;
        default:
            printf("选择正确的功能编号\n\n");
            break;
        }
    }
    return 0;
}