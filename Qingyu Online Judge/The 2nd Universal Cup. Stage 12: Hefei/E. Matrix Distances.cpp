#include <bits/stdc++.h>
#define int long long
#define VI vector<int>
using namespace std;

template<class T>
inline void chmin(T &x,T y){if(x>y)x=y;}

inline int read(){
    int x=0,f=1;char ch=getchar();
    for(;!isdigit(ch);ch=getchar())f^=ch=='-';
    for(;isdigit(ch);ch=getchar())x=x*10+(ch^48);
    return f?x:-x;
}

struct BitTree{
    VI s;
    int n;
    BitTree(int n=0):s(VI(n+3,0)),n(n){}
    void add(int x,int t){
        if(x>n||!x)return;
        for(;x<=n;x+=x&-x)s[x]+=t;
    }
    void clr(int x){
        if(x>n||!x)return;
        for(;x<=n;x+=x&-x)s[x]=0;
    }
    int ask(int x){
        if(x<=0)return 0;
        chmin(x,n);
        int ret=0;
        for(;x;x-=x&-x)ret+=s[x];
        return ret;
    }
}fenwickX,fenwickY,ddX,ddY;

int n,m,cnt=0,ans;
vector<VI> mp;
map<int,int> st;
vector<vector<array<int,2>>> pos;

void solve(){
    n=read(),m=read(),ans=cnt=0,st={};
    mp.assign(n+1,VI(m+1,0));
    for(int i=1;i<=n;++i)for(int j=1;j<=m;++j){
        mp[i][j]=read();
        if(!st[mp[i][j]]){
            st[mp[i][j]]=++cnt;
        }
        mp[i][j]=st[mp[i][j]];
    }
    pos.assign(cnt+3,{});
    for(int i=1;i<=n;++i)for(int j=1;j<=m;++j){
        pos[mp[i][j]].push_back({i,j});
    }
    fenwickX=ddX=(n+3),fenwickY=ddY=(m+3);
    for(int i=1;i<=cnt;++i){
        int sumx=0,sumy=0,tt=0;
        for(auto [x,y]:pos[i]){
            fenwickX.add(x,x);
            fenwickY.add(y,y);
            ddX.add(x,1);
            ddY.add(y,1);
            sumx+=x;
            sumy+=y;
            ++tt;
        }
        --tt;
        for(auto [x,y]:pos[i]){
            int sx=fenwickX.ask(x-1);
            int sy=fenwickY.ask(y-1);
            int tx=sumx-x-sx;
            int ty=sumy-y-sy;
            int cntx=ddX.ask(x-1),dntx=tt-cntx;
            int cnty=ddY.ask(y-1),dnty=tt-cnty;
            ans+=cntx*x-sx+tx-dntx*x;
            ans+=cnty*y-sy+ty-dnty*y;
        }

        for(auto [x,y]:pos[i]){
            fenwickX.clr(x);
            fenwickY.clr(y);
            ddX.clr(x);
            ddY.clr(y);
        }
    }
    printf("%lld\n",ans);
}

signed main(){
    // for(int cas=read();cas--;){
        solve();
    // }
}