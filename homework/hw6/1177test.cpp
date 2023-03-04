#include <stdio.h>
#include <algorithm>
using namespace std;
int n,tot,k;
int a[10010];
bool f[30010];
int search_k(int l,int r)
{
    if(l==r&&l==k) return a[k];
    if(l<r)
    {
    	//这部分和快排一样的 
        int i=l,j=r,p=a[l];//选左端点为基准数 
        while(i<j)
        {
            while(i<j&&a[j]>p) j--;//从右向左，找到第一个小于基准数的数 
            if(i<j) swap(a[i],a[j]);
            while(i<j&&a[i]<=p) i++;//从左向右，找到第一个大于基准数得数 
            if(i<j) swap(a[i],a[j]);
        }
        a[i]=p;
        if(i==k) return a[k];
        else if(i>k) return search_k(l,i-1);//k在左区间 
        else return search_k(i+1,r);//右区间 
    }
}

int main() {
    
}