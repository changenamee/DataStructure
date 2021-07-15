//棋盘覆盖问题
//分治法
#include<iostream>
#include<vector>
using namespace std;
int boardSize=0;
int numL=0;
vector<vector<int> > board;
void check(int,int,int,int,int);
int main(void){
    int rowTopLeft=0,colTopLeft=0,specialRow=0,specialCol=0;
    int k=0,a=0;
    cout<<"输入K：";
    cin>>k;
    //错误检查
    boardSize = pow(2,k);
    board.resize(boardSize,vector<int>(boardSize,0));
    cout<<"输入特殊行号和列号（空格分开）:";
    cin>>specialRow>>specialCol;
    //错误检查
    board[specialRow][specialCol] = 0;
    //cout<<"1"<<endl;
    check(rowTopLeft,colTopLeft,specialRow,specialCol,boardSize);
    //cout<<"2"<<endl;
    for(int i=0;i<boardSize;++i){
        for(int j=0;j<boardSize;++j){
            cout<<board[i][j]<<"\t";
        }
        cout<<endl;
    }
    cout<<"cin to end.";
    cin>>a;
    return 0;
}

void check(int rowTopLeft,int colTopLeft,int specialRow,int specialCol,int boardSize){
    if(boardSize==1)    return;
    //cout<<"3"<<endl;
    int num = ++numL,size=boardSize/2;
    //覆盖在左上角
    if(specialRow<=rowTopLeft+size-1 && specialCol<=colTopLeft+size-1){
        check(rowTopLeft,colTopLeft,specialRow,specialCol,size);
    }else{
        board[rowTopLeft+size-1][colTopLeft+size-1] = num;
        check(rowTopLeft,colTopLeft,rowTopLeft+size-1,colTopLeft+size-1,size);
    }
    //覆盖在右上角
    if(specialRow<=rowTopLeft+size-1 && specialCol>=colTopLeft+size){
        check(rowTopLeft,colTopLeft+size,specialRow,specialCol,size);
    }else{
        board[rowTopLeft+size-1][colTopLeft+size] = num;
        check(rowTopLeft,colTopLeft+size,rowTopLeft+size-1,colTopLeft+size,size);
    }
    //覆盖在左下角
    if(specialRow>=rowTopLeft+size && specialCol<=colTopLeft+size-1){
        check(rowTopLeft+size,colTopLeft,specialRow,specialCol,size);
    }else{
        board[rowTopLeft+size][colTopLeft+size-1] = num;
        check(rowTopLeft+size,colTopLeft,rowTopLeft+size,colTopLeft+size-1,size);
    }
    //覆盖在右下角
    if(specialRow>=rowTopLeft+size && specialCol>=colTopLeft+size){
        check(rowTopLeft+size,colTopLeft+size,specialRow,specialCol,size);
    }else{
        board[rowTopLeft+size][colTopLeft+size] = num;
        check(rowTopLeft+size,colTopLeft+size,rowTopLeft+size,colTopLeft+size,size);
    }
}