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
template<typename T>inline void chmin(T &x,T y){x>y?x=y:y;}
template<typename T>inline void chmax(T &x,T y){x<y?x=y:y;}

const int mo=998244353,inf=1e15;

mt19937 rnd(time(0));

inline void red(int &x){(x>=mo)&&(x-=mo);}
inline int qpow(int x,int t=mo-2){
    int ret=1;
    for(;t;t>>=1,x=x*x%mo)if(t&1)ret=ret*x%mo;
    return ret;
}

vector<array<int,2>> E;
vector<VI> edge;
VI d,ans,B;

int n,m,A;

void extend_bfs(int s){
    VI cnt(n+1,0),dis(n+1,-1),layer={s},node={};
    for(int i=1;i<=n;++i)if(i!=s)node.push_back(i);
    for(int i=0;layer.size();++i){
        for(int x:layer)dis[x]=i;
        for(int u:layer)for(int v:edge[u]){
            if(dis[v]==-1)++cnt[v];
        }
        VI nxnode={},nxlayer={};
        for(int x:node){
            if(cnt[x]==layer.size()){
                nxnode.push_back(x);
            }else{
                nxlayer.push_back(x);
            }
            cnt[x]=0;
        }
        node.swap(nxnode);
        layer.swap(nxlayer);
    }
    for(int i=1;i<=n;++i)if(i!=s&&dis[i]!=-1){
        if(2*d[i]<n){
            ++ans[dis[i]];
        }else{
            if(i<s){
                ++ans[dis[i]];
            }
        }
    }
}

void solve(){
    n=read(),m=read(),A=0,B={};
    edge.assign(n+1,{});
    ans=d=VI(n+1,0);
    for(int i=1;i<=m;++i){
        int x=read(),y=read();
        edge[x].push_back(y);
        edge[y].push_back(x);
        ++d[x],++d[y];
        E.push_back({x,y});
    }
    for(int i=1;i<=n;++i){
        if(d[i]*2<n){
            ++A;
        }else{
            B.push_back(i);
        }
    }
    ans[1]=A*(A-1)/2;
    for(auto [x,y]:E){
        if(d[x]*2<n&&d[y]*2<n){
            --ans[1],++ans[2];
        }
    }
    for(int i:B){
        extend_bfs(i);
    }
    for(int i=1;i<n;++i){
        printf("%lld ",ans[i]);
    }
    puts("");
    return;
}

signed main(){
    // for(int cas=read();cas--;){
        solve();

    // }
    return 0;
}