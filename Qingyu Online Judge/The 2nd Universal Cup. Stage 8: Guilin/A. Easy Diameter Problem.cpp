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
template<class T>inline void chmin(T &x,T y){x>y?x=y:y;}
template<class T>inline void chmax(T &x,T y){x<y?x=y:y;}

const int mo=1e9+7,inf=1e15;

mt19937 rnd(time(0));

inline void red(int &x){(x>=mo)&&(x-=mo);}
inline int qpow(int x,int t=mo-2){
    int ret=1;
    for(;t;t>>=1,x=x*x%mo)if(t&1)ret=ret*x%mo;
    return ret;
}

VI fac,ifac;

inline int binom(int n,int m){
    if(n<0||m>n||m<0)return 0;
    return fac[n]*ifac[m]%mo*ifac[n-m]%mo;
}

//???x,y???????
int f(int x,int y){return binom(x+y,x);}
int ex_f(int n,int m){
    if(n==0)return m==0;
    return binom(n+m-1,m);
}

int n,state,ans;
vector<vector<array<int,2>>> tree;
vector<VI> bound,capbnd,dis,lnk;
vector<array<int,2>> rev,E;

void dfs1(int u,int fa,VI &dis){
    for(auto [id,v]:tree[u])if(v!=fa){
        dis[v]=dis[u]+1;
        dfs1(v,u,dis);
    }
}

void dfs2(int u,int fa,int dep,VI &dp){
    dp[u]=dep;
    for(auto [_,v]:tree[u])if(v!=fa){
        dfs2(v,u,dep+2,dp);
        chmax(dp[u],dp[v]);
    }
}

array<int,2> getDiameter(){
    int ans=0,rid=0;
    for(int i=1;i<=n;++i)for(int j=i+1;j<=n;++j){
        chmax(ans,dis[i][j]);
    }
    VI dp(n+1,0);
    if((ans>>1)&1){
        for(int i=0;i<n-1;++i){
            auto [x,y]=E[i];
            dfs2(x,y,1,dp);
            dfs2(y,x,1,dp);
            if(dp[x]==ans/2&&dp[y]==ans/2){
                return {ans>>1,i+n+1};
            }
        }
    }else{
        for(int i=1;i<=n;++i){
            dfs2(i,0,0,dp);
            array<int,2> tmp{0,0};
            for(auto [_,j]:tree[i]){
                if(dp[j]>tmp[0])tmp={dp[j],tmp[0]};
                else chmax(tmp[1],dp[j]);
            }
            if(tmp[0]==ans/2&&tmp[1]==ans/2){
                return {ans>>1,i};
            }
        }
    }
    return {-1,-1};
}

void solve(){
    n=read(),state=0,ans=0;
    if(n==1){
        puts("1");
        return;
    }
    lnk.assign(4*n,VI(4*n,0)),tree.assign(n+1,{});
    for(int i=1;i<n;++i){
        int x=read(),y=read();
        tree[x].push_back({n+i,y});
        tree[y].push_back({n+i,x});
        E.push_back({x,y});
    }
    for(int i=1;i<=n;++i){
        for(auto [j,_]:tree[i]){
            lnk[i][j]=state++;
            lnk[j][i]=state++;
            rev.push_back({i,j});
            rev.push_back({j,i});
        }
    }
    dis.assign(2*n,VI(n+1,0));
    bound.assign(2*n,VI(2*n+3,0));
    capbnd.assign(4*n,VI(2*n+3,0));
    for(int i=1;i<=n;++i){
        dfs1(i,0,dis[i]);
        for(int j=1;j<=n;++j)dis[i][j]<<=1;
    }
    for(int i=0;i<n-1;++i){
        auto [x,y]=E[i];
        dfs1(x,y,dis[n+1+i]);
        dfs1(y,x,dis[n+1+i]);
        for(int j=1;j<=n;++j){
            dis[n+i+1][j]=dis[n+i+1][j]<<1|1;
        }
    }

    for(int i=1;i<n*2;++i){
        for(int j=1;j<=n;++j)++bound[i][dis[i][j]];
    }
    for(int i=0;i<state;++i){
        auto [x,y]=rev[i];//x->y
        for(int j=1;j<=n;++j){
            capbnd[i][dis[x][j]]+=dis[x][j]==dis[y][j]+1;
        }
    }
    
    auto [D,mid]=getDiameter();
    rev.push_back({-1,mid});

    vector<VI> dp,rdp;
    dp.assign(state+1,VI(n+1,0));
    dp[state][0]=1;

    for(int d=D;d;--d){
        rdp.assign(state+1,VI(n+1,0));
        for(int x=0;x<=state;++x){
            auto [u,v]=rev[x];//u->v
            for(int l=0;l<=n;++l)if(dp[x][l]){
                if(v>n){
                    auto [a,b]=E[v-n-1];
                    for(int w:{a,b})if(w!=u){
                        int add=bound[v][d]-capbnd[lnk[v][w]][d];
                        red(rdp[lnk[v][w]][l+add]+=fac[add]*dp[x][l]%mo);
                    }
                }else{
                    for(auto [w,_]:tree[v])if(w!=u){
                        int add=bound[v][d]-capbnd[lnk[v][w]][d];
                        int A=capbnd[x][d+1]-capbnd[lnk[v][w]][d],B=add-A;
                        if(u==-1)A=0,B=add;
                        int sym=f(l+B,A)*fac[A]%mo*fac[B]%mo;
                        red(rdp[lnk[v][w]][l+add]+=sym*dp[x][l]%mo);
                    }
                }
                if(u!=-1){
                    int m=capbnd[x][d+1];
                    for(int i=1;i<=m;++i){
                        red(rdp[x^1][i]+=fac[m]*ex_f(l,m-i)%mo*dp[x][l]%mo);
                    }
                }
            }
        }
        dp.swap(rdp);
    }

    for(int i=0;i<state;++i)for(int l=0;l<=n;++l)red(ans+=dp[i][l]);

    printf("%lld\n",ans);

    return;
}

signed main(){

    const int V=6e5;
    fac=ifac=VI(V,1);
    for(int i=1;i<V;++i){
        fac[i]=fac[i-1]*i%mo;
    }
    ifac[V-1]=qpow(fac[V-1]);
    for(int i=V-1;i;--i){
        ifac[i-1]=ifac[i]*i%mo;
    }

    // for(int cas=read();cas--;){
        solve();

    // }
    return 0;
}
