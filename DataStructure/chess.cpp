/* 
分治法解决棋盘问题
 */
#include<iostream>
using namespace std;
#define LENGTH 256
int arr[LENGTH][LENGTH] = {0};
//每次递归用不同的数
//递归调用注意变量变化
static int t = 0;
void chess(int a,int b,int x,int y,int length){ //(a,b)为左上角坐标,(x,y)为特殊点的坐标,length是棋盘长度
    int l = length/2;
    t++;
    int temp = t;
    //递归结束条件
    if(length == 1){
        return;
    }
    //特殊点在左上角
    if(x < (a+l) && y < (b+l)){
        chess(a,b,x,y,l);
    }else//将这个棋盘的右下角设为特殊点
    {
        arr[a+l-1][b+l-1] = temp;
        chess(a,b,a+l-1,b+l-1,l);
    }

    //特殊点在左下角
    if(x >= (a+l) && y < (b+l)){
        chess(a+l,b,x,y,l);
    }else{
        arr[a+l][b+l-1] = temp;
        chess(a+l,b,a+l,b+l-1,l);
    }

    //特殊点在右上角
    if(x<a+l && y>=b+l){//右上角的子棋盘
        chess(a,b+l,x,y,l);
    }
    else{
        arr[a+l-1][b+l]=temp;
        //cout<<"右上  "<<a+l-1<<"  "<<b+l<<"  "<<arr[a+l][b+l-1]<<endl;
        chess(a,b+l,a+l-1,b+l,l);
    }
    //右下角
    if(x>=a+l && y>=b+l){
        chess(a+l,b+l,x,y,l);
    }
    else{
        arr[a+l][b+l]=temp;
        //cout<<"右下  "<<a+l<<"  "<<b+l<<"  "<<arr[a+l][b+l]<<endl;
        chess(a+l,b+l,a+l,b+l,l);
    }
}

int main(void){
    int length;
    int a,b,x,y;
    cout<<"length:";
    cin>>length;
    cout<<"x:";
    cin>>x;
    cout<<"y:";
    cin>>y;
    int m = length;
    a = b = 1;

    chess(a,b,x,y,length);
    for(int i=1;i<=m;i++){
        for(int j=1;j<=m;j++){
            cout.width(3);
            cout<<arr[i][j];
            if(j == m)
                cout<<endl;
        }
    }
}