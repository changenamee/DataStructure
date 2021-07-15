#include<algorithm>
#include<iostream>
using namespace std;
/* 
最大堆，最小堆（二叉树）
 */

//交换值
void swap(int arr[],int a,int b){
    int temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}
//构造最大堆
void heapInsert(int arr[],int len){
    for(int i=0;i<len;i++){
        int currentIndex = i;   //当前索引
        int fatherIndex = (i-1)/2;  //父节点索引
        while(arr[currentIndex] < arr[fatherIndex]){
            swap(arr,currentIndex,fatherIndex); //交换值
            currentIndex = fatherIndex; //更改当前索引和新的父节点索引
            fatherIndex = (currentIndex - 1)/2;
        }
    }
}
//对取出顶端元素后的堆再次构造最大堆
void heapIns(int arr[],int index,int len){
    int left = 2*index + 1; //左孩子，右孩子
    int right = 2*index + 2;
    while(left < len){
        int largestIndex;   //左右孩子中较大节点的索引
        if(arr[left] > arr[right] && right < len)
            largestIndex = left;
        else
            largestIndex = right;
        
        if(arr[index] > arr[largestIndex])
            largestIndex = index;
        //如果最大值是当前节点，则堆成立
        if(largestIndex == index)
            break;
        swap(arr,index,largestIndex);
        index = largestIndex;

        left = 2*index + 1;
        right = 2*index + 2;
    }
}
//堆排序
int heapSort(int arr[],int len){
    heapInsert(arr,len);
    int size = len;
    while(size > 0){
        swap(arr,0,size-1);
        size--;
        heapIns(arr,0,size);
    }
}