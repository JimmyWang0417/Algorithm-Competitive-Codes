#include <bits/stdc++.h>
#define int long long
#define VI vector<int>
using namespace std;

template<class T>
inline void chmin(T &x,T y){if(x>y)x=y;}
template<class T>
inline void chmax(T &x,T y){if(x<y)x=y;}

inline int read(){
    int x=0,f=1;char ch=getchar();
    for(;!isdigit(ch);ch=getchar())f^=ch=='-';
    for(;isdigit(ch);ch=getchar())x=x*10+(ch^48);
    return f?x:-x;
}

const int inf=1e9;

string str;
VI a,sum,f[6][2];
int n,m,k;

int chk(int mid){
    for(int i=0;i<6;++i)for(int j=0;j<2;++j){
        f[i][j].assign(n+1,inf);
    }
    f[0][0][0]=0;
    for(int i=1;i<=n;++i){
        f[0][a[i]][i]=0;
    }
    for(int j=1;j<=k;++j){
        for(int i=1;i<=n;++i){
            if(a[i]){
                chmin(f[j][1][i],f[j][0][i-1]);
                chmin(f[j][1][i],f[j][1][i-1]);
            }else{
                chmin(f[j][0][i],f[j][0][i-1]);
                chmin(f[j][0][i],f[j][1][i-1]);
            }
            if(i>=mid)chmin(f[j][1][i],f[j-1][0][i-mid]+mid-sum[i]+sum[i-mid]);
        }
    }
    for(int i=1;i<=n;++i){
        if(min(f[k][0][i],f[k][1][i])<=m)return 1;
    }
    return 0;
}

signed main(){
    n=read(),m=read(),k=read();
    cin>>str;
    a=sum=VI(n+1,0);
    for(int i=1;i<=n;++i){
        a[i]=str[i-1]=='1';
        sum[i]=sum[i-1]+a[i];
    }
    int ans=-1,l=1,r=n;
    while(l<=r){
        int mid=(l+r)>>1;
        if(chk(mid)){
            ans=mid;
            l=mid+1;
        }else{
            r=mid-1;
        }
    }
    printf("%lld\n",ans);
}