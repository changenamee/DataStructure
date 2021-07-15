#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<unordered_map>
#include<algorithm>
#include<queue>
using namespace std;
const int N=100001;
//冒泡排序，平均/最差时间复杂度O(n^2),空间复杂度(1)，稳定排序
void bubbleSort(vector<int>& vec){
    int len = vec.size();
    if(!len)    return;
    for(int i=0;i<len-1;++i){
        for(int j=0;j<len-1-i;++j){
            if(vec[j]>vec[j+1]){
                swap(vec[j],vec[j+1]);
            }
        }
    }
}
//选择排序，平均/最差时间复杂度O(n^2),空间复杂度(1)，数组不稳定，链表稳定
void selectSort(vector<int>& vec){
    int len = vec.size();
    if(!len)    return;
    for(int i=0;i<len;++i){
        int index = i;
        for(int j=i+1;j<len;++j){
            if(vec[j]>vec[index]){
                index = j;
            }
        }
        swap(vec[index],vec[i]);
    }
}
//快速排序，平均时间复杂度O(nlogn),最差时间复杂度(n^2),空间复杂度(logn)，不稳定
void fastSort(vector<int>& vec,int left,int right){
    if(left>=right) return;
    int l=left,r=right,key=vec[left];   //基准
    while (l<r)
    {
        while(l<r && vec[r]>=key)   //从后往前找到第一个比key小的
            --r;
        if(l<r)
            vec[l++] = vec[r];
        while(l<r && vec[l]<=key)   //从前往后找到第一个比key大的
            ++l;
        if(l<r)
            vec[r--] = vec[l];
    }
    vec[l] = key;
    fastSort(vec,left,l-1);
    fastSort(vec,l+1,right);
}
//堆排序，平均时间复杂度O(nlogn)，最差时间复杂度(nlogn),空间复杂度(1)，不稳定
//建堆
void heapify(vector<int>& vec,int index,int len){   
    int left=index*2+1,right = index*2+2;
    int biggest = index;
    if(left<len && vec[left]>vec[biggest])
        biggest = left;
    if(right<len && vec[right]>vec[biggest])
        biggest = right;
    if(biggest!=index){
        swap(vec[index],vec[biggest]);
        heapify(vec,biggest,len);
    }
}
void heapSort(vector<int>& vec){
    int len = vec.size();
    //初始化堆
    for(int i=len/2;i>=0;--i){
        heapify(vec,i,len);
    }
    for(int i=len-1;i>0;--i){
        swap(vec[0],vec[i]);
        heapify(vec,0,i);
    }
}
//插入排序，平均/最差时间复杂度O(n^2),空间复杂度(1)，稳定排序
void insertSort(vector<int>& vec){
    int len=vec.size();
    for(int i=1;i<len;++i){
        int num = vec[i];
        for(int j=i-1;j>=0;--j){
            if(vec[j]>num){
                vec[j+1] = vec[j];
                vec[j] = num;
            }
        }
    }
}
//归并排序,平均时间复杂度O(nlogn)，最差时间复杂度(nlogn),空间复杂度(n)，稳定
void merge(vector<int>& vec,int low,int mid,int high){
    int i=low,j=mid+1,cnt=0;
    vector<int> temp(high-low+1);
    while(i<=mid && j<=high){
        if(vec[i]<vec[j]){
            temp[cnt++] = vec[i++];
        }else{
            temp[cnt++] = vec[j++];
        }
    }
    while(i<=mid)   temp[cnt++] = vec[i++];
    while(j<=high)  temp[cnt++] = vec[j++];
    for(int m=low,n=0;m<=high;m++,n++)
        vec[m] = temp[n];
}
void mergeSort(vector<int>& vec,int low,int high){
    if(low<high){
        int mid = low+(high-low)/2;
        mergeSort(vec,low,mid);
        mergeSort(vec,mid+1,high);
        merge(vec,low,mid,high);
    }
}
//希尔排序
void shellSort(vector<int>& vec){
    int len = vec.size();
    int gap=len/2;
    while(gap){
        for(int i=gap;i<len;++i){
            for(int j=i;j>=gap&&vec[j]<vec[j-gap];j-=gap){
                swap(vec[j],vec[j-gap]);
            }
        }
        gap/=2;
    }
}
//
int main(void){
    vector<int> vec = {5,2,1,4,3};
    cout<<"before:";
    for(int i=0;i<vec.size();++i)
        cout<<vec[i]<<" ";
    cout<<endl;
    //bubbleSort(vec);
    //selectSort(vec);
    //fastSort(vec,0,vec.size()-1);
    //heapSort(vec);
    //insertSort(vec);
    //mergeSort(vec,0,vec.size()-1);
    shellSort(vec);
    cout<<"after:";
    for(int i=0;i<vec.size();++i)
        cout<<vec[i]<<" ";
    cout<<endl;
    return 0;
}