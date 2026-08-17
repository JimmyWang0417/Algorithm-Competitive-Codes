#include <bits/stdc++.h>
using namespace std;

using LL=long long;
using ai2=array<int,2>;
using ai4=array<int,4>;
using al2=array<LL,2>;

constexpr int N=205;
constexpr int M=25;
ai4 dp[N][N][M][2];
void dfs(int a,int b,int n,int p);
inline void dfs_next(int na,int nb,int nn,int np,int a,int b,int n,int p){
    if(dp[na][nb][nn][np][0]!=-1) return;
    dp[na][nb][nn][np]=ai4{a,b,n,p};
    if(nn) dfs(na,nb,nn,np);
}
void dfs(int a,int b,int n,int p){
    dfs_next(a,b,n,p^1,a,b,n,p);
    vector<int>add{};
    if(n>6){ // has red ball
        if(!p) dfs_next(a+1,b,n-1,1,a,b,n,p);
        else dfs_next(a,b+1,n-1,0,a,b,n,p);
        add={3,4,5,6,7,8};
    }
    else{ // no red ball
        add={8-n};
    }
    for(const auto& x:add){
        int na=a,nb=b;
        if(!p) na+=x;
        else nb+=x;
        dfs_next(na,nb,n-1,p,a,b,n,p);
    }
}
void init(){
    for(int a=0;a<=200;++a){
        for(int b=0;b<=200;++b){
            for(int n=21;n>=0;--n){
                dp[a][b][n][0]=dp[a][b][n][1]=
                ai4{-1,-1,-1,-1};
            }
        }
    }
    dfs(0,0,21,0);
}

void fuck(int na,int nb,int nn,int np){
    if(!na && !nb && nn==21 && !np){
        return;
    }
    auto [a,b,n,p]=dp[na][nb][nn][np];
    fuck(a,b,n,p);
    if(a==na && b==nb && n==nn && p!=np){
        cout<<"/";
        return;
    }
    const int delta=max(na-a,nb-b);
    if(n>6){ // red ball
        cout<<"1";
        const int x=delta-1;
        if(x) cout<<x;
        else cout<<"/";
    }
    else{ // color ball
        cout<<(delta);
    }
}
void solve(){
    int a,b,n,p;
    cin>>a>>b>>n>>p;
    if(!a && !b && n==21 && !p){
        cout<<"\n";
        return;
    }
    if(dp[a][b][n][p][0]==-1){
        cout<<"NA\n";
        return;
    }
    fuck(a,b,n,p);
    cout<<"\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T;std::cin>>T;
    while(T--) solve();
}
