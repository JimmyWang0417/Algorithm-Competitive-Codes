#include <bits/stdc++.h>
const int mod=1000000007;
using ll=long long;
void solve(){
    int n,m;std::cin>>n>>m;
    std::vector<int> a(n+5);
    std::vector<std::vector<ll>> f(n+5,std::vector<ll>(2));
    for(int i=1;i<=n;i++) std::cin>>a[i];
    ll ans=0;
    f[0][1]=1;
    ll res=1;
    for(int i=1;i<=n;i++) if(a[i]==-1) res=(ll)res*m%mod;
    for(int i=1;i<=n;i++){
        if(a[i]>=2&&a[i]<=n-1){
            return (void) (std::cout<<(res-ans+mod)%mod<<'\n');
        }
        else if(a[i]==1) f[i][0]=0,f[i][1]=f[i-1][0];
        else if(a[i]==-1) f[i][0]=(ll)(f[i-1][0]+f[i-1][1])*std::max((m-n+1),0)%mod,f[i][1]=(ll)f[i-1][0]%mod;
        else f[i][0]=(ll)(f[i-1][0]+f[i-1][1])%mod;
        // std::cerr<<f[i][0]<<' '<<f[i][1]<<'\n';
    }
    int fl=n%2;
    for(int i=1;i<=n;i++) if(a[i]!=1&&a[i]!=-1) fl=0;
    std::cout<<(res-f[n][0]-fl+mod)%mod<<'\n';
}
int main()
{
    int T=1;
    while(T--) solve();
}
