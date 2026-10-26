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

template<class T>
inline void chmin(T &x,T y){x>y?x=y:0;}
template<class T>
inline void chmax(T &x,T y){x<y?x=y:0;}

VI work(int n,VI a,VI r){
    VI d(n+1,0),ans;
    for(int i=1;i<=n;++i){
        if(i==1||i==n)d[i]=1;
        else d[i]=2;
    }
    set<int> oper;
    auto chk=[&](int i)->void{
        if(a[i]>=d[i]&&r[i]>0){
            oper.insert(i);
        }
    };
    for(int i=1;i<=n;++i){
        if(a[i]>=d[i]&&r[i]>0){
            oper.insert(i);
        }
    }
    while(oper.size()){
        auto it=oper.end();
        it--;
        int i=*it;
        oper.erase(it);
        a[i]-=d[i];
        if(i>1)++a[i-1];
        if(i<n)++a[i+1];
        --r[i];
        ans.push_back(i);
        chk(i);
        if(i>1)chk(i-1);
        if(i<n)chk(i+1);
    }
    reverse(ans.begin(),ans.end());
    return ans;
}

void solve(){
    int n=read(),typ=read(),ans=0;
    VI a,s1,s2,s,d;
    a=s1=s2=s=d=VI(n+1,0);
    for(int i=1;i<=n;++i){
        a[i]=read();
        s1[i]=i,s2[i]=s2[i-1]+a[i];
        s[i]=s2[i]-s1[i];
    }
    d[1]=0;
    for(int i=2;i<=n;++i){
        d[i]=d[i-1]-s[i-1];
        chmin(d[0],d[i]);
    }
    for(int i=1;i<=n;++i){
        d[i]-=d[0];
        ans+=d[i];
    }
    printf("%lld\n",ans);
    if(typ){
        auto ans=work(n,a,d);
        for(int x:ans)printf("%lld ",x);
    }
}

signed main(){
    for(int cas=1;cas--;)solve();
}
