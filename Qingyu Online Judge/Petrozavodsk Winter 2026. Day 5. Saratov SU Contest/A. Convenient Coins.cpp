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

int n,last,ans;
VI a,sum,sum_of_sum;

void solve(){
    n=read(),a=sum=sum_of_sum=VI(n+2,0);
    for(int i=1;i<=n;++i){
        a[i]=read();
        sum[i]=sum[i-1]+a[i];
    }
    last=n+1,ans=0;
    for(int i=n;i;--i){
        sum_of_sum[i]=sum_of_sum[i+1]+sum[i];
        if(a[i]==1){
            last=i;
        }
        int cnt=n-last+1;
        ans+=sum_of_sum[last]-cnt*sum[i-1];
    }
    printf("%lld\n",ans);
}

signed main(){
    for(int cas=read();cas--;)solve();
}
