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

constexpr int mo=998244353;

inline int qpow(int x,int t=mo-2){
    int ret=1;
    for(;t;t>>=1,x=x*x%mo)if(t&1)ret=ret*x%mo;
    return ret;
}

inline void red(int &x){x>=mo?x-=mo:0;}

int n,m,ans,lim;
vector<VI> a;
vector<vector<array<int,2>>> pos;
VI tmp,lnk,cnt,fac,ifac;
map<int,int> mp;

inline int binom(int n,int m){
    if(n<0||m<0||n<m)return 0;
    return fac[n]*ifac[m]%mo*ifac[n-m]%mo;
}

int subtask1(int id){
    vector<VI> DP(n+1,VI(m+1,0));
    DP[1][1]=1;
    for(int i=1;i<=n;++i)for(int j=1;j<=m;++j){
        if(a[i][j]==id)DP[i][j]=0;
        if(i==1&&j==1)continue;
        red(DP[i][j]=DP[i-1][j]+DP[i][j-1]);
        if(a[i][j]==id)DP[i][j]=0;
    }
    return (binom(n+m-2,n-1)+mo-DP[n][m])%mo;
}

int subtask2(int id){
    if(pos[id][0]==array<int,2>{1,1}||pos[id].back()==array<int,2>{n,m}){
        return binom(n+m-2,n-1);
    }
    pos[id].push_back({n,m});
    VI DP(pos[id].size(),0);
    for(int i=0;i<pos[id].size();++i){
        auto [x,y]=pos[id][i];
        DP[i]=binom(x+y-2,x-1);
        for(int j=0;j<i;++j){
            auto [xj,yj]=pos[id][j];
            red(DP[i]+=mo-DP[j]*binom(x-xj+y-yj,x-xj)%mo);
        }
    }
    pos[id].pop_back();
    return (binom(n+m-2,n-1)+mo-DP.back())%mo;
}

void solve(){
    n=read(),m=read(),ans=0;
    a.assign(n+1,VI(m+1,0));
    for(int i=1;i<=n;++i)for(int j=1;j<=m;++j){
        a[i][j]=read();
        tmp.push_back(a[i][j]);
    }
    sort(tmp.begin(),tmp.end());
    for(int i=0,j,k=0;i<tmp.size();i=j,++k){
        j=i+1;
        while(j<tmp.size()&&tmp[i]==tmp[j])++j;
        lnk.push_back(tmp[i]);
        mp[tmp[i]]=k;
    }
    cnt.assign(lnk.size(),0);
    pos.assign(lnk.size(),{});
    for(int i=1;i<=n;++i)for(int j=1;j<=m;++j){
        a[i][j]=mp[a[i][j]];
        ++cnt[a[i][j]];
        pos[a[i][j]].push_back({i,j});
    }
    lim=sqrt(n*m)+5;

    // puts("DUBUG:");

    // for(int i=1;i<=n;++i,puts(""))for(int j=1;j<=m;++j){
    //     printf("%lld ",a[i][j]);
    // }

    for(int i=0;i<cnt.size();++i){
        int A,B=lnk[i];
        if(cnt[i]>=lim){
            A=subtask1(i);
            // red(ans+=subtask1(i)*lnk[i]%mo);
        }else{
            A=subtask2(i);
            // red(ans+=subtask2(i)*lnk[i]%mo);
        }
        // printf("%lld %lld\n",A,B);
        red(ans+=A*B%mo);
    }
    printf("%lld\n",ans);
}

constexpr int V=1e5;

signed main(){
    fac=ifac=VI(V,1);
    for(int i=1;i<V;++i){
        fac[i]=fac[i-1]*i%mo;
    }
    ifac[V-1]=qpow(fac[V-1]);
    for(int i=V-1;i;--i){
        ifac[i-1]=ifac[i]*i%mo;
    }
    // for(int cas=read();cas--;)solve();
    solve();
}
