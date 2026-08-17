#include <bits/stdc++.h>
using namespace std;

// #define LOCAL
#ifdef LOCAL
#define dbg(...) fprintf(stderr,##__VA_ARGS__)
#else
#define dbg(...) 42
#endif

constexpr int inf=1e9;
void solve(){
    int n,m,K;
    cin>>n>>m>>K;
    vector<int>pos(m,-1);
    for(int i=0,r,c;i<K;++i){
        cin>>r>>c;
        --r,--c;
        pos[c]=r;
    }
    vector<vector<int>>dp(n,vector<int>(m));
    vector<int>opt(n);
    vector<int>a(K);
    auto fuck=[&]()->void{
        dp.assign(n,vector<int>(m,inf));
        auto rush=[&](const int& j)->void{
            // return;
            const int& p=pos[j];
            for(int i=0;i<n-1;++i){
                if(i==p || i+1==p) continue;
                dp[i+1][j]=min(dp[i+1][j],dp[i][j]+1);
            }
            for(int i=n-1;i>0;--i){
                if(i==p || i-1==p) continue;
                dp[i-1][j]=min(dp[i-1][j],dp[i][j]+1);
            }
            for(int i=0;i<n-1;++i){
                if(i==p || i+1==p) continue;
                dp[i+1][j]=min(dp[i+1][j],dp[i][j]+1);
            }
            for(int i=n-1;i>0;--i){
                if(i==p || i-1==p) continue;
                dp[i-1][j]=min(dp[i-1][j],dp[i][j]+1);
            }
        };
        for(int i=0;i<n;++i){
            dp[i][0]=0;
        }
        int tot=0;
        for(int j=1;j<m;++j){
            dbg("j=%d\n",j);
            if(pos[j]==-1){
                for(int i=0;i<n;++i){
                    dp[i][j]=dp[i][j-1]+1;
                }
                rush(j);
                continue;
            }
            const int& p=pos[j];
            assert(tot<K);
            const bool& _=a[tot++];
            if(!_){ // go up
                dbg("\tgoing up\n");
                for(int i=0;i<p;++i){
                    dp[i][j]=dp[i][j-1]+1;
                }
                if(p-1>0){
                    int pre;
                    if(pos[j-1]==-1) pre=n;
                    else pre=pos[j-1];
                    dbg("\tp=%d pre=%d\n",p,pre);
                    for(int i=p;i<pre;++i){
                        int& d=dp[p-1][j];
                        const int x=dp[i][j-1]+(i-(p-1))+1;
                        d=min(d,x);
                    }
                }
            }
            else{ // go down
                dbg("\tgoing down\n");
                for(int i=p+1;i<n;++i){
                    dp[i][j]=dp[i][j-1]+1;
                }
                if(p+1<n){
                    int pre;
                    if(pos[j-1]==-1) pre=0;
                    else pre=pos[j-1]+1;
                    for(int i=pre;i<=p;++i){
                        int& d=dp[p+1][j];
                        const int x=dp[i][j-1]+(p+1-i)+1;
                        d=min(d,x);
                    }
                }
            }
            rush(j);
        }
    };
    for(int s=0;s<(1<<K);++s){
        for(int i=0;i<K;++i){
            a[i]=s>>i&1;
        }
        dbg("s=%d\n",s);
        fuck();
        int ans=inf;
        for(int i=0;i<n;++i){
            ans=min(ans,dp[i][m-1]);
        }
        if(ans==inf) ans=-1;
        cout<<ans<<' ';
    }
    cout<<'\n';
}

signed main()
{
    #ifndef LOCAL
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    #endif
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
