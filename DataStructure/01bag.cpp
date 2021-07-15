#include<iostream>
#include<algorithm>
using namespace std;

int v[5] = {0,2,5,7,10};    //物品价值
int w[5] = {0,1,3,9,5}; //物品重量
int bagw = 12;  //背包容量
int db[5][12] = { {0} }; //动态规划表
int result[5];  //结果

//寻找挑选结果
void find(){
    for(int i=1;i<=5;i++){
        for(int j=1;j<=12;j++){
            if(j < w[i]){   //容量不足
                db[i][j] = db[i-1][j];
            }else{  //选择拿或不拿第i个物品
                db[i][j] = max(db[i-1][j],db[i-1][j-w[i]]+v[i]);
            }
        }
    }
}
//求出最优解
void best(int i,int j){
    if(i > 0){
        if(db[i][j] == db[i-1][j]){
            result[i] = 0;
            best(i-1,j);
        }else if(db[i][j] != db[i-1][j] && db[i][j] == (db[i-1][j-w[i]] + v[i])){
            result[i] = 1;
            best(i-1,j-w[i]);
        }
    }
}
//输出结果
void print(){
    //输出表格 
    for(int i=0;i<5;i++){
        for(int j=0;j<12;j++){
            cout<<db[i][j]<<" ";
        }
        cout<<endl;
    }
    //输出选取的结果
    for(int i=0;i<5;i++)
        cout<<result[i]<<" ";
    cout<<endl;
}

int main(void){
    find();
    best(4,12);
    print();
    return 0;
}