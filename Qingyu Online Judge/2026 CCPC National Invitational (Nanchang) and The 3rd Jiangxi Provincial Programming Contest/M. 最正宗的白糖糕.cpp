#include <bits/stdc++.h>
#define int long long
#define VI vector<int>
using namespace std;
inline int read(){
    int x=0,f=1;char ch=getchar();
    for(;!isdigit(ch);ch=getchar())f^=ch=='-';
    for(;isdigit(ch);ch=getchar())x=x*10+(ch^48);
    return f?x:-x;
}

int n,m,k;

VI a;

int chk(int mid){
    a[0]=-mid-1;
    int i,j;
    for(i=0,j=1;j<=m;){
        int nxt=i;
        while(nxt+1<=n&&a[nxt+1]-a[i]<=2*mid+1){
            ++nxt;
        }
        i=nxt;
        ++j;
    }
    if(a[i]>=k-mid)return 1;
    else return 0;
}

signed main(){
    n=read(),m=read(),k=read();
    a.resize(n+1);
    for(int i=1;i<=n;++i){
        a[i]=read();
    }
    sort(a.begin()+1,a.end());
    int l=0,r=k,ans=-1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(chk(mid)){
            ans=mid;
            r=mid-1;
        }else{
            l=mid+1;
        }
    }
    printf("%lld\n",ans);
}