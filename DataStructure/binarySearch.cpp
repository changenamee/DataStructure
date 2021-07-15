#include<iostream>
using namespace std;

int binarySearch(int arr[],int num,int len){
    int start = 0;
    int end = len - 1; 
    while(start <= end){    //start等于end时也有效
        int mid = start + (end-start)/2;
        if(arr[mid] > num){
            end = mid-1;
        }else if(arr[mid] < num){
            start = mid+1;
        }else{
            return mid;
        }
    }
    return -1;
}

int main(void){
    int arr[] = {1,23,111,45,56,66};
    int len = end(arr) - begin(arr);
    int n = binarySearch(arr,23,len);
    cout<<"23 is in "<<n<<endl;
    return 0;
}