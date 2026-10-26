#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x=0,f=1;char ch=getchar();
    for(;!isdigit(ch);ch=getchar())f^=ch=='-';
    for(;isdigit(ch);ch=getchar())x=x*10+(ch^48);
    return f?x:-x;
}

int ans,n,k,mo,dp[2][105][11000];

inline void red(int &x){x>=mo?x-=mo:0;}

signed main(){
    n=read(),k=read(),mo=read();
    dp[0][0][0]=1;
    for(int i=1;i<=n*2;++i){
        for(int k=0;k<11000;++k){
            for(int j=0;j<=min(n,i);++j){
                if(k+i<11000&&i<=2*(j+1)){
                    red(dp[1][j+1][k+i]+=dp[0][j][k]);
                }
                red(dp[1][j][k]+=dp[0][j][k]*(min(n,(j+1))-(i-1-j))%mo);
            }
        }
        memcpy(dp[0],dp[1],sizeof(dp[1]));
        // for(int k=0;k<=n*n+5;++k){
        //     for(int j=0;j<=n;++j){
        //         printf("dp[%lld][%lld][%lld]=%lld,",i,j,k,dp[0][j][k]);
        //     }
        //     puts("");
        // }
        // puts("");
        memset(dp[1],0,sizeof(dp[0]));
    }
    for(int i=k;i<11000;++i)red(ans+=dp[0][n][i]);
    printf("%lld\n",ans);
}
