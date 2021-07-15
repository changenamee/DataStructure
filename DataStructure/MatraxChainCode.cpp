#include<iostream>
using namespace std;
#define M 7
//动态规划
//m数组记录链的最小代价，s数组记录链最小代价是k的取值
//p数组记录矩阵的行列,length为矩阵链的长度
void MatraxChainOrder(int *p,int length,int m[][M],int s[][M]){
    int n = length - 1;
    int i,j;
    for(i = 1;i<=n;i++)
        m[i][i] = 0;    //长度为1的最小链的代价
    for(int l = 2;l<=n;l++){    //链的长度，自底向上
        for(i = 1;i<=n-l+1;i++){
            // l = j - i + 1;
            j=l+i-1;
            m[i][j] = 1222222222;
            for(int k = i;k<=j-1;k++){
                int q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
                if(q < m[i][j]){
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
}

//打印
void PrintMatrax(int s[][M],int i,int j){
    if(i == j)
        printf("A%d",i);
    else{
        printf("(");
        PrintMatrax(s,i,s[i][j]);
        PrintMatrax(s,s[i][j]+1,j);
        printf(")");
    }
}

int main(void){
    int p[M]={30,35,15,5,10,20,25};
    int m[M][M],s[M][M];
    MatraxChainOrder(p,M,m,s);
    cout<<"当n=6时最优解为: \n"<<m[1][6];
    cout<<"\n括号化方案为：\n"; 
    PrintMatrax(s,1,6);
    return 0;
}