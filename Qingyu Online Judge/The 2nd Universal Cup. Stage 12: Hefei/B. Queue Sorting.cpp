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

const int mo=998244353;

inline void red(int &x){if(x>=mo)x-=mo;}

int n,m;
VI a,l,r,id;
vector<VI> f;

signed main(){
    n=read(),m=0,a=l=r=VI(n+1,0);
    for(int i=1;i<=n;++i){
        a[i]=read();
        m+=a[i];
        l[i]=r[i-1]+1;
        r[i]=l[i]+a[i]-1;
    }
    id.assign(m+1,0);
    for(int i=1;i<=n;++i){
        for(int j=l[i];j<=r[i];++j){
            id[j]=i;
        }
    }
    f.assign(m+1,VI(m+1,0));
    f[0][0]=1;
    for(int i=1;i<=m;++i){
        for(int j=i;j<=m;++j){
            int vv=id[j];
            red(f[i][j]+=f[i-1][j]);
            if(j==l[vv]){
                for(int k=0;k<j;++k){
                    red(f[i][j]+=f[i-1][k]);
                }
            }else{
                red(f[i][j]+=f[i-1][j-1]);
            }
        }
    }
    // for(int i=0;i<=m;++i,puts(""))for(int j=0;j<=m;++j){
    //     printf("f[%lld][%lld]=%lld, ",i,j,f[i][j]);
    // }
    printf("%lld\n",f[m][m]);
}