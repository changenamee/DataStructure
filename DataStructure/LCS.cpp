/* 
动态规划求LCS（最长公共子序列）
 */
#include<iostream>
#include<stack>
using namespace std;

void LCS(string s1,string s2){
    int m = s1.length() + 1;    //第一行第一列初始化为0，所以长度+1；
    int n = s2.length() + 1;
    int **b,**c;
    b = new int* [m];   //存LCS字符
    c = new int* [m];   //存LCS 长度
    for(int i=0;i<m;i++){
        b[i] = new int [n];
        c[i] = new int [n];
        for(int j = 0;j<n;j++)
            b[i][j] = 0;
    }
    //第一行第一列初始化为0
    for(int i =0;i<m;i++)
        c[i][0] = 0;
    for(int i=0;i<n;i++)
        c[0][i] = 0;
    for(int i=0; i<m-1; i++){
        for(int j=0; j<n-1; j++){
            if(s1[i] == s2[j]){
                c[i+1][j+1] = c[i][j] + 1;
                b[i+1][j+1] = 1;    //1表示箭头为左上
            }else if(c[i+1][j] >= c[i][j+1]){
                c[i+1][j+1] = c[i+1][j];
                b[i+1][j+1] = 2;    //2表示箭头向左
            }else{
                c[i+1][j+1] = c[i][j+1];
                b[i+1][j+1] = 3;    //3表示箭头向上
            }
        }
    }
    //输出c数组
    for(int i =0;i<m;i++){
        for(int j=0; j<n;j++){
            cout<<c[i][j]<<" ";
        }
        cout<<endl;
    }
    stack<char> same;   //存放LCS字符
    stack<int> same1,same2; //存放LCS字符下标
    for(int i=m-1,j=n-1;i>=0 && j>=0;){
        if(b[i][j] == 1){   //字符相同
            same.push(s1[i]);
            same1.push(i);
            same2.push(j);
            i--;j--;
        }else if(b[i][j] == 2){ //箭头指向左
            j--;
        }else i--;
    }

    cout<<s1<<endl; //输出字符串s1
    for(int i=0;i<m && !same1.empty();i++){
        if(i == same1.top()){
            cout<<1;
            same1.pop();
        }else{
            cout<<' ';
        }
    }
    cout<<endl<<s2<<endl;   //输出字符串s2
    for(int i=0;i<n && !same2.empty();i++){
        if(i == same2.top()){
            cout<<1;
            same2.pop();
        }else{
            cout<<' ';
        }
    }
    cout<<endl<<"LCS 长度："<<c[m-1][n-1]<<endl;
    cout<<"LCS:";
    while(!same.empty()){
        cout<<same.top();
        same.pop();
    }
    for(int i=0;i<m;i++){
        delete [] c[i];
        delete [] b[i];
    }
    delete [] b;
    delete [] c;
}

int main(void){
    string s1 = "abcdddefs";
    string s2 = "bcdsddesf";

    LCS(s1,s2);
    return 0;
}