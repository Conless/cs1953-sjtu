#include <bits/stdc++.h>
using namespace std;

int getorderpair(int arr[],int n,int num,int pos){
    int sum=0;
    for(int i=0;i<n;++i){
        if (!arr[i]) continue;
        sum+=((arr[i]<num && i<pos)||(arr[i]>num && i>pos));
    }
    return sum;
}
int getorderpairall(int arr[],int n){
    int sum=0;
    for(int i=0;i<n;++i){
        if (!arr[i]) continue;
        sum+=getorderpair(arr,n,arr[i],i);
    }
    return sum/2;	// each pair cal twice.
}
int main(){
    int arr[100],can[10];			// missing num
    unordered_set<int> s;
    for(int n,k,c,base,ans;cin>>n>>k;c=0,s.clear()){
        for(int i=ans=0;i<n;++i){
            cin>>arr[i];
            s.insert(arr[i]);            
        }
        for(int i=c=0;i<n;++i){		// find missing num
            if (s.find(i+1)==s.end()) can[c++]=i+1;
        }
       	int arrbase = getorderpairall(arr,n);
        do{
            int canbase = getorderpairall(can,c);
            for(int i=base=0,j=0;i<n;++i){
                if (arr[i]) continue;
                base+=getorderpair(arr,n,can[j++],i);
            }
            if (arrbase+canbase+base==k) ++ans;
        }while(next_permutation(can,can+c));
        cout<<ans<<endl;
    }
    return 0;
}