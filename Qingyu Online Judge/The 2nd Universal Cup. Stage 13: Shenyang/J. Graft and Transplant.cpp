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
VI deg;
int n,leaf;
signed main(){
    n=read(),leaf=0;
    deg.assign(n+1,0);
    for(int i=1;i<n;++i){
        int x=read(),y=read();
        ++deg[x],++deg[y];
    }
    if(n==2){
        puts("Bob");
        return 0;
    }
    for(int i=1;i<=n;++i)if(deg[i]==1)++leaf;
    leaf=n-1-leaf;
    if(leaf&1)puts("Alice");
    else puts("Bob");
}
