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
inline void chmax(T &x,T y){x<y?x=y:0;}

// const int P1=,P2=,P3=;
constexpr int Q1=1000003,Q2=1000033,Q3=1000037;
struct HASH{
    using ll=long long;
    inline static constexpr array<ll,3> MOD{998244353,1000000007,1000000009};
    array<ll,3> value{};
    static ll norm(ll x,ll mod){x%=mod; return x<0?x+mod:x;}
    HASH(ll x=0):value({x,x,x}){}
    HASH(ll x,ll y,ll z):value({x,y,z}){}
    ll &operator[](size_t i){return value[i];}
    const ll &operator[](size_t i)const{return value[i];}
    HASH &operator+=(const HASH &x){
        for(int i=0;i<3;++i){
            if((value[i]+=x[i])>=MOD[i]){
                value[i]-=MOD[i];
            }
        }
        return *this;
    }
    HASH &operator-=(const HASH &x){
        for(int i=0;i<3;++i){
            if((value[i]-=x[i])<0){
                value[i]+=MOD[i];
            }
        }
        return *this;
    }
    HASH &operator*=(const HASH &x){
        for(int i=0;i<3;++i){
            value[i]=value[i]*x[i]%MOD[i];
        }
        return *this;
    }
    friend bool operator==(const HASH &x,const HASH &y){
        return x.value==y.value;
    }
    friend bool operator!=(const HASH &x,const HASH &y){
        return !(x==y);
    }
    friend HASH operator+(HASH x,const HASH& y){return x+=y;}
    friend HASH operator-(HASH x,const HASH& y){return x-=y;}
    friend HASH operator*(HASH x,const HASH& y){return x*=y;}
};

const HASH BASE{Q1,Q2,Q3};

vector<HASH> fpow;

int n;
VI a[3],nxt[3],dp[8],st[3];

vector<HASH> sum[3];

const int inf=1e9;

void solve(){
    n=read();
    for(int i=0;i<8;++i){
        dp[i].assign(n+1,-inf);
    }
    dp[7][0]=0;
    for(int k=0;k<3;++k){
        st[k]=a[k]=nxt[k]=VI(n+1,-1);
        sum[k].assign(n+1,HASH(0));
        for(int i=1;i<=n;++i){
            a[k][i]=read();
            sum[k][i]=sum[k][i-1]+fpow[a[k][i]];
        }
    }
    for(int k=0;k<3;++k){
        for(int i=1,last=0;i<=n;++i){
            int s=0;
            for(int u=0;u<3;++u){
                if(sum[k][i]==sum[u][i]){
                    s|=(1<<u);
                }
            }
            int popcnt=__builtin_popcountll(s);
            if(popcnt>1){
                dp[s][i]=0;
                nxt[k][last]=i;
                st[k][last]=s;
                last=i;
            }
        }
    }

    // for(int i=0;i<3;++i,puts("")){
    //     printf("HASH:");
    //     for(int j=1;j<=n;++j){
    //         printf("[%lld %lld %lld] ",sum[i][j][0],sum[i][j][1],sum[i][j][2]);
    //     }
    // }

    // for(int i=0;i<3;++i,puts("")){
    //     printf("NXT:");
    //     for(int j=0;j<=n;++j){
    //         printf("%lld ",nxt[i][j]);
    //     }
    // }
    for(int i=0;i<n;++i){
        for(int s=0;s<8;++s){
            if(dp[s][i]<0)continue;
            for(int u=0;u<3;++u)if((s>>u)&1){
                int j=nxt[u][i],v=st[u][i];
                if(j!=-1){
                    chmax(dp[v][j],dp[s][i]+1);
                }
            }
        }
    }
    printf("%lld\n",dp[7][n]);
}

const int V=2e5+5;


signed main(){
    fpow.assign(V,HASH(1));
    for(int i=1;i<V;++i)fpow[i]=fpow[i-1]*BASE;
    for(int cas=read();cas--;)solve();
}
