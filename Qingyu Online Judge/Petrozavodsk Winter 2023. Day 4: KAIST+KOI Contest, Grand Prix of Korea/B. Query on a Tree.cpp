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

int f(int x){return x*(x-1)/2;}

void solve(){
    int n=read(),q,dfntot=0;
    vector<VI> edge(n+1),mdf(n+1),Node(n+1);
    VI father,dfn,vis;
    father=dfn=vis=VI(n+1,0);
    for(int i=1;i<n;++i){
        int x=read(),y=read();
        edge[x].push_back(y);
        edge[y].push_back(x);
    }
    auto dfs=[&](int u,int fa,auto &&self)->void{
        dfn[u]=++dfntot,father[u]=fa;
        for(int v:edge[u])if(v!=fa){
            self(v,u,self);
        }
    };
    dfs(1,0,dfs);
    q=read();
    while(q--){
        int k=read(),ans=0;
        VI node;
        for(int i=1;i<=k;++i){
            int x=read();
            vis[x]=1;
            node.push_back(x);
        }
        sort(node.begin(),node.end(),[&](int x,int y){
            return dfn[x]>dfn[y];
        });
        for(int u:node){
            int son=u;
            for(int v:mdf[u]){
                if(Node[v].size()>Node[son].size())son=v;
            }
            if(son!=u){
                Node[u].swap(Node[son]);
                ans-=f(Node[u].size());
            }
            for(int v:mdf[u])if(v!=son){
                ans-=f(Node[v].size());
                for(int x:Node[v])Node[u].push_back(x);
            }
            Node[u].push_back(u);
            ans+=f(Node[u].size());
            if(vis[father[u]])mdf[father[u]].push_back(u);
        }
        for(int x:node){
            mdf[x]=Node[x]={};
            vis[x]=0;
        }
        printf("%lld\n",ans);
    }
}

signed main(){
    // for(int cas=read();cas--;){
        solve();
    // }
}
