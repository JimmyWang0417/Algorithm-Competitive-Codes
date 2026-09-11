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

vector<array<int,2>> ans;

int n;
string str;

map<array<int,2>,int> vis,tmp;


void solve(){
    n=read(),ans={};
    cin>>str;
    for(int s=0;s<(1<<n);++s){
        int x=0,y=0,tag=0;
        tmp.clear();
        tmp[{0,0}]=-1;
        for(int i=0;i<n;++i){
            int dx=x,dy=y;
            if(str[i]=='L')--dx;
            else if(str[i]=='R')++dx;
            else if(str[i]=='U')++dy;
            else --dy;
            
            if((s>>i)&1){
                if(tmp[{dx,dy}]!=-1){
                    tmp[{dx,dy}]=1;
                    continue;
                }else{
                    tag=1;
                    break;
                }
            }else{
                if(tmp[{dx,dy}]!=1){
                    tmp[{dx,dy}]=-1;
                    x=dx,y=dy;
                    continue;
                }else{
                    tag=1;
                    break;
                }
            }
        }
        if(tag)continue;
        else{
            if(!vis[{x,y}]){
                vis[{x,y}]=1;
                // ++ans;
                ans.push_back({x,y});
            }
        }
    }
    sort(ans.begin(),ans.end());
    printf("%lld\n",ans.size());
    for(auto [x,y]:ans){
        printf("%lld %lld\n",x,y);
    }
    // printf("%lld\n",ans);
    return;
}

signed main(){
    // for(int cas=read();cas--;){
        solve();

    // }
    return 0;
}