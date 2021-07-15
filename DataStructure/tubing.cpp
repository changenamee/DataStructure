#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXCNT=50;
vector<vector<int>> f(MAXCNT,vector<int>(2));

void quickSort(vector<int>& vec,int left,int right){
    if(left>=right) return;
    int i=left,j=right,num=vec[left];
    while(i<j){
        while(i<j && vec[j]>=num)
            --j;
        if(i<j) vec[i++] = vec[j];
        while(i<j && vec[i]<=num)
            ++i;
        if(i<j) vec[j--] = vec[i];
    }
    vec[i] = num;
    quickSort(vec,left,i-1);
    quickSort(vec,i+1,right);
}
int main(void){
    int cnt=0,mid=0,res=0;
    vector<int> y(MAXCNT);
    cout<<"输入油井数量:";
    cin>>cnt;
    //输入油井坐标，空格隔开x,y
    for(int i=0;i<cnt;++i){
        cin>>f[i][0]>>f[i][1];
        y[i] = f[i][1];
    }
    quickSort(y,0,cnt-1);
    //注意数组大小....
    if(cnt%2==1){
        mid = y[cnt/2];
    }else   mid = (y[cnt/2-1]+y[cnt/2])/2;
    for(int i=0;i<cnt;++i)
        res += abs(y[i]-mid);
    cout<<"min res is:"<<res<<endl;
}