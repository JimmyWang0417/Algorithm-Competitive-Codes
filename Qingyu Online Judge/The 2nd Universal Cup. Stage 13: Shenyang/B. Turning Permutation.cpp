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

vector<VI> f[3];
VI perm,q,cnt,pre[3],suf[3];
int n,KK;

int calc(int pos){
    // f[0]=f[1]=vector<VI>(n+2,VI(n+2,0));
    f[0].assign(n+5,VI(n+5,0));
    f[1].assign(n+5,VI(n+5,0));
    for(int i=1;i<=n;++i){
        cnt[i]=cnt[i-1]+(!q[i]);
    }
    if(q[1]){
        f[0][1][0]=f[1][1][0]=1;
    }else{
        f[0][1][1]=f[1][1][1]=1;
    }
    for(int i=2;i<=n;++i){
        for(int t=0;t<2;++t){
            suf[t]=pre[t]=f[t][i-1];
            for(int j=1;j<=n+1;++j){
                pre[t][j]=pre[t][j-1]+pre[t][j];
                chmin(pre[t][j],KK+5);

            }
            for(int j=n;j>=0;--j){
                suf[t][j]=suf[t][j+1]+suf[t][j];
                chmin(suf[t][j],KK+5);
            }
        }
        if(!q[i]){
            for(int k=1;k<=cnt[i];++k){
                f[0][i][k]=pre[1][k-1];
                f[1][i][k]=suf[0][k];
            }
        }else{
            if(q[i-1]){
                if(q[i-1]<q[i]){
                    f[0][i][0]=f[1][i-1][0];
                }else{
                    f[1][i][0]=f[0][i-1][0];
                }
            }else{
                f[1][i][0]=suf[0][1];
            }
        }
    }
    int ret=0;
    for(int i=0;i<=n;++i){
        ret+=f[0][n][i]+f[1][n][i];
        chmin(ret,KK+5);
    }
    return ret;
}

void solve(){
    n=read(),KK=read();
    cnt=perm=q=VI(n+10,0);
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j)if(!q[j]){
            perm[i]=j;
            q[j]=i;
            int tmp=calc(i);
            if(tmp<KK||tmp==-1){
                q[j]=0;
                perm[i]=0;
                KK-=tmp;
                continue;
            }else{
                break;
            }
        }
        if(!perm[i]){
            puts("-1");
            return;
        }
    }
    for(int i=1;i<=n;++i){
        printf("%lld ",perm[i]);
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