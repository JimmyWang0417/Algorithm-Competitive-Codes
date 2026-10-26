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

const int N=55;
int f[N<<2][N][N][N],n,m;
char str[255];

void solve(){
    n=read(),m=n*4;
    memset(f,0,sizeof(f));
    scanf("%s",str+1);
    f[m+1][0][0][0]=1;
    for(int i=m;i>=1;--i){
        for(int x=0;x<=n;++x)for(int y=0;y<=n;++y)for(int z=0;z<=n;++z){
            if(str[i]=='p'||str[i]=='?'){
                red(f[i][x+1][y][z]+=f[i+1][x][y][z]);
            }
            if(str[i]=='c'||str[i]=='?')if(y){
                red(f[i][x][y-1][z+1]+=f[i+1][x][y][z]);
            }
            if(str[i]=='u'||str[i]=='?'){
                if(x)red(f[i][x-1][y+1][z]+=f[i+1][x][y][z]);
                else if(z)red(f[i][x][y][z-1]+=f[i+1][x][y][z]);
            }
        }
    }
    // for(int i=1;i<=m;++i)for(int x=0;x<=n;++x)for(int y=0;y<=n;++y)for(int z=0;z<=n;++z){
    //     printf("f[%lld][%lld][%lld][%lld]=%lld\n",i,x,y,z,f[i][x][y][z]);
    // }
    printf("%lld\n",f[1][0][0][0]);
    return;
}

signed main(){
    // for(int cas=read();cas--;){
        solve();

    // }
    return 0;
}
