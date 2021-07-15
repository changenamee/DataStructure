#include<iostream>
using namespace std;

//最大字段和（暴力法）
//遍历所有子序列求和
//n^2
int maxSubSum1(int arr[],int n){
    int sum = 0;
    int tempSum = 0;
    for(int i=0;i<n;i++){
        tempSum = 0;
        for(int j=i;j<n;j++){
            tempSum += arr[j];
            if(tempSum > sum)
                sum = tempSum;
        }
    }
    return sum;
}
//分治法
//最大字段和在左半部分或右半部分或两部分加起来

//返回三个数中的最大值
int max(int a,int b,int c){
    int max = a;
    if(b > max)
        max = b;
    if(c > max)
        max = c;
    return max;
}
int maxSubSum2(int arr[],int left,int right){
    if(left == right)   return arr[right];  //递归结束条件，left=right
    int middle = (left+right) /2;

    int maxLeftSubSum = maxSubSum2(arr,left,middle);
    int maxRightSubSum = maxSubSum2(arr,middle+1,right);

    //处理左右边界问题
    int maxLeftBorder = 0;
    int maxRightBorder = 0;
    int tempSum = 0;
    //左半部分
    for(int i=middle;i>=left;i--){
        tempSum += arr[i];
        if(tempSum > maxLeftBorder)
            maxLeftBorder = tempSum;
    }
    tempSum = 0;
    //右半部分
    for(int i=middle+1;i<right;i++){
        tempSum += arr[i];
        if(tempSum > maxRightBorder)
            maxRightBorder = tempSum;
    }
    int maxBorder = maxLeftBorder + maxRightBorder;
    return max(maxLeftSubSum,maxRightSubSum,maxBorder);
}

//动态规划
//负数的话设max是0
//b[j] = max{0,b[j-1]} + a[j]
int maxSubSum3(int a[],int n){
    int temp = 0;
    int max = 0;
    for(int i=0;i<n;i++){
        if(temp > 0){
            temp += a[i];
        }else{
            temp = a[i];
        }
        if(temp > max)
            max = temp;
    }
    return max;
}

int main(void){
    int a[] = {1,-2,3,-4,-5,1,3};
    cout<<maxSubSum3(a,7)<<endl;
    cout<<maxSubSum2(a,0,7)<<endl;
    cout<<maxSubSum1(a,7)<<endl;
    return 0;
}