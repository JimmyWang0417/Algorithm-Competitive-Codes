#include <bits/stdc++.h>

#define int long long
#define VI vector<int>
#define pii array<int,2>

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

int n,m;
VI idx,pre,suf,sum;
vector<array<int,2>> sgm;
string str;

int chk(int len){
    sgm={};
    for(int l=1,r=len;r<=n;++l,++r){
        if(sum[r]-sum[l-1])continue;
        int L=suf[l],R=pre[r];
        if(L>=R)return 1;
        if(sgm.empty()||sgm.back()!=pii{L,R}){
            sgm.push_back({L,R});
        }
    }
    int tag=0;
    for(auto [L,R]:sgm){
        if(R==L+1){
            tag=1;
        }
    }
    if(!tag)return 0;
    VI A,B,C,D,f;
    A=B=C=D=f=VI(m+1,0);
    for(auto [L,R]:sgm)if(R-L<=2){
        if(R-L==1){
            A[L]=B[R]=1;
        }else{
            C[L]=D[R]=1;
        }
    }
    for(int i=1;i<=m;++i){
        if(B[i])f[i]=1;
        if(D[i])f[i]|=f[i-2];
        if(f[i]&&A[i])return 1;
    }
    return 0;
}

void solve(){
    // n=read(),m=0;
    cin>>str;
    n=str.size(),m=0;
    idx=pre=sum=VI(n+2,0);
    suf=VI(n+2,n+1);
    for(int i=1;i<=n;++i){
        if(str[i-1]=='?'){
            idx[i]=++m;
            suf[i]=pre[i]=m;
        }
        sum[i]=sum[i-1]+(str[i-1]=='1');
    }
    for(int i=1;i<=n;++i){
        if(!pre[i]){
            pre[i]=pre[i-1];
        }
        if(suf[n-i+1]==n+1){
            suf[n-i+1]=suf[n-i+2];
        }
    }
    int l=0,r=n,ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(chk(mid)){
            ans=mid;
            l=mid+1;
        }else{
            r=mid-1;
        }
    }
    // chk(3);
    printf("%lld\n",ans);
    return;
}

signed main(){
    for(int cas=read();cas--;){
        solve();

    }
    return 0;
}
