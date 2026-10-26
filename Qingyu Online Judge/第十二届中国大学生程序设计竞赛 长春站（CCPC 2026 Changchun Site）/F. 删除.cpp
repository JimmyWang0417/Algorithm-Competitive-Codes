#include <bits/stdc++.h>
#define int long long
#define VI vector<int>
#define VVI vector<VI>
#define VVVI vector<VVI>
using namespace std;
inline int read(){
    int x=0,f=1;char ch=getchar();
    for(;!isdigit(ch);ch=getchar())f^=ch=='-';
    for(;isdigit(ch);ch=getchar())x=x*10+(ch^48);
    return f?x:-x;
}
const int mo=1e9+7,inf=1e15;
inline void red(int &x){x>=mo?x-=mo:0;}
inline int qpow(int x,int t=mo-2){
    int ret=1;
    for(;t;t>>=1,x=x*x%mo)if(t&1)ret=ret*x%mo;
    return ret;
}
VI fac,ifac;
inline int binom(int n,int m){
    if(n<0||n<m||m<0)return 0;
    return fac[n]*ifac[m]%mo*ifac[n-m]%mo;
}
namespace solve{
    int n,ans;
    VI a,dp[2];
    VVVI f,g;
    void DP1(){
        f=g=VVVI(n+5,VVI(n+2,VI(n+2,0)));
        for(int i=0;i<=n;++i){
            f[0][i+1][i]=g[0][i+1][i]=1;
        }
        for(int k=1;k<=n;++k){
            for(int l=1;l<=n;++l)for(int r=l;r<=n;++r){
                int tag=0;
                for(int i=l;i<=r;++i)if(a[i]>k)tag=1;
                if(tag)break;
                for(int i=l;i<=r;++i){
                    if(a[i]!=k&&a[i]!=-1)continue;
                    int A=g[k-1][l][i-1]*g[k-1][i+1][r]%mo;
                    int B=k>1?g[k-2][l][i-1]*g[k-2][i+1][r]%mo:0;
                    red(f[k][l][r]+=binom(r-l,i-l)*(A+mo-B)%mo);
                }
            }
            for(int l=1;l<=n+1;++l)for(int r=1;r<=n+1;++r){
                red(g[k][l][r]=g[k-1][l][r]+f[k][l][r]);
            }
        }
    }
    void DP2(){
        dp[0]=dp[1]=VI(n+5,0);
        dp[0][1]=1;
        for(int i=1;i<=n;++i)if(a[i]==n+1||a[i]==-1){
            for(int j=i-1;j>=1;--j)if(a[j]==n+1||a[j]==-1){
                int tr=g[n][j+1][i-1]*binom(i-2,j-1)%mo;
                red(dp[0][i]+=dp[0][j]*tr%mo);
                if(a[j]==n+1)break;
            }
        }
        dp[1][n]=1;
        for(int i=n;i>=1;--i)if(a[i]==n+1||a[i]==-1){
            for(int j=i+1;j<=n;++j)if(a[j]==n+1||a[j]==-1){
                int tr=g[n][i+1][j-1]*binom(n-i-1,n-j)%mo;
                red(dp[1][i]+=dp[1][j]*tr%mo);
                if(a[j]==n+1)break;
            }
        }
    }
    void work(){
        a.assign((n=read())+1,0);
        for(int i=1;i<=n;++i){
            a[i]=read();
            if(!a[i])a[i]=n+1;
        }
        DP1(),DP2(),ans=0;
        for(int i=1;i<=n;++i)if(a[i]==n+1||a[i]==-1){
            red(ans+=dp[0][i]*dp[1][i]%mo*binom(n-1,i-1)%mo);
        }
        printf("%lld\n",ans);
    }
}
signed main(){
    const int V=1e6;
    fac=ifac=VI(V,1);
    for(int i=1;i<V;++i)fac[i]=fac[i-1]*i%mo;
    ifac.back()=qpow(fac.back());
    for(int i=V-1;i;--i)ifac[i-1]=ifac[i]*i%mo;
    for(int cas=read();cas--;){
        solve::work();
    }
}

/*
4
2
0 0
3
0 1 0
4
0 1 ?1 0
5
0 1 0 1 0
*/
