#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x=0,f=1;char ch=getchar();
    for(;!isdigit(ch);ch=getchar())f^=ch=='-';
    for(;isdigit(ch);ch=getchar())x=x*10+(ch^48);
    return f?x:-x;
}

void solve(){
    int n=read();
    if(n&1)puts("0");
    else{
        int ans=n*(n-2)/2;
        printf("%lld\n",ans);
    }
}

signed main(){
    for(int cas=read();cas--;)solve();
}