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

int n,lim,ans;
VI a,b,tmp;

void solve(){
    n=read(),ans=0,a=b=VI(n+1,0),tmp={};
    for(int i=1;i<=n;++i){
        a[i]=read();
        tmp.push_back(a[i]);
    }
    sort(tmp.begin(),tmp.end());
    if(n==2){
        printf("%lld 0\n",tmp[0]);
        return;
    }
    lim=min(2*tmp[0],tmp[n-2]);
    printf("%lld ",lim);
    for(int i=1;i<=n;++i)b[i]=(a[i]>=lim);
    for(int i=1;i<=n;++i){
        if(b[i]){
            ans+=i-1;
            break;
        }
    }
    for(int i=n;i>=1;--i){
        if(b[i]){
            ans+=n-i;
            break;
        }
    }
    printf("%lld\n",ans);
}

signed main(){
    for(int cas=read();cas--;)solve();
}
