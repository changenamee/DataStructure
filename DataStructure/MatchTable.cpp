#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXCNT=50;
vector<vector<int> > f(MAXCNT,vector<int>(MAXCNT));
void func(int row,int col,int num){
    if(num==1)  return; //选手个数是1，返回
    int half = num/2;
    //左上角=右下角，右上角=左下角
    f[row+half][col+half]=f[row][col];      //左上角赋值给右下角
    f[row+half][col] = f[row][col]+half;    //左下角=左上角+half
    f[row][col+half] = f[row+half][col];    //右上角=左下角
    //递归四个角
    func(row,col,half);
    func(row+half,col,half);
    func(row+half,col+half,half);
    func(row,col+half,half);
}
int main(void){
    int k=0,num=0;
    cout<<"输入k:";
    cin>>k;
    num = pow(2,k); //选手个数
    f[0][0] = 1;
    func(0,0,num);
    for(int i=0;i<num;++i){
        for(int j=0;j<num;++j){
            cout<<f[i][j]<<"\t";
        }
        cout<<endl;
    }
    return 0;
}