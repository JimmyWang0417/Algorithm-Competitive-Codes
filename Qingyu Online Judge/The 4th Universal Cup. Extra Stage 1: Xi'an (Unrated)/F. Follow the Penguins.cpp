#include <bits/stdc++.h>
using namespace std;

// #define LOCAL
#ifdef LOCAL
#define debug(...) fprintf(stderr,##__VA_ARGS__)
#else
#define debug(...) 42
#endif

using LL=long long;
#define all(x) (x).begin(),(x).end()

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n; cin>>n;
    vector<int>to(n+1),in(n+1);
    for(int i=1;i<=n;++i){
        cin>>to[i];
        ++in[to[i]];
    }
    vector<LL>a(n+1);
    for(int i=1;i<=n;++i){
        cin>>a[i];
        a[i]<<=1;
    }
    vector<int>dir(n+1);
    for(int i=1;i<=n;++i){
        const int& j=to[i];
        if(a[i]<a[j]) dir[i]=1;
        else dir[i]=-1;
    }
    vector<int>seq,vis(n+1);
    queue<int>p;
    for(int i=1;i<=n;++i){
        if(!in[i]) p.push(i);
    }
    while(p.size()){
        auto u=p.front();
        seq.push_back(u);
        vis[u]=1;
        p.pop();
        if(!--in[to[u]]){
            p.push(to[u]);
        }
    }
    vector<int>from(n+1); // only work in cycle
    vector<LL>ans(n+1);
    auto fuck=[&](int u,int v)->void{ // use u to get v
        const LL& d=abs(a[u]-a[v]);
        debug("u=%d v=%d t[%d]=%lld d=%lld\n",u,v,u,ans[u],d);
        if(dir[u]==dir[v]){
            ans[v]=ans[u]+d;
        }
        else{
            ans[v]=max(d/2,d-ans[u]);
        }
        debug("\tt[%d]=%lld\n",v,ans[v]);
    };
    constexpr LL inf=1e12;
    for(int i=1;i<=n;++i){
        if(!vis[i]){
            debug("work %d\n",i);
            vector<int>b;
            {
                int u=i;
                while(!vis[u]){
                    vis[u]=1;
                    b.emplace_back(u);
                    from[to[u]]=u;
                    u=to[u];
                }
            }
            LL mn=inf; int st=-1;
            for(const auto& u:b){
                debug("\tu=%d from[%d]=%d\n",u,u,from[u]);
                const int& v=to[u];
                if(dir[u]==dir[v]) continue;
                LL res=abs(a[u]-a[v])>>1;
                if(res<mn){
                    mn=res;
                    st=u;
                }
            }
            ans[st]=mn;
            {
                int u=st;
                while(1){
                    const int& v=from[u];
                    if(ans[v]) break;
                    fuck(u,v);
                    u=v;
                }
            }
        }
    }
    #ifdef LOCAL
    for(int i=1;i<=n;++i){
        debug("dir[%d]=%d\n",i,dir[i]);
    }
    #endif
    // work with reverse seq
    for(int i=seq.size()-1;~i;--i){
        const int& u=seq[i];
        fuck(to[u],u);
    }
    for(int i=1;i<=n;++i){
        cout<<ans[i]<<' ';
    }
    return 0;
}
