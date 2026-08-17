#include <bits/stdc++.h>
using ll=long long;
void solve(){
    int n,m,a,b;
    std::cin>>n>>m>>a>>b;
    std::vector<int> cnt(n*m+5),p(n*m+5);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            int x;std::cin>>x;
            cnt[x]++;
        }
    }
    for(int i=1;i<=n*m;i++){
        p[i]=i;
    }
    std::sort(p.begin()+1,p.begin()+n*m+1,[&](int x,int y){return cnt[x]>cnt[y];});
    ll sum1=0,ans=LONG_LONG_MAX,sum2=0;
    for(int i=1;i<=n*m;i++){
        if(!cnt[p[i]]) break;
        // std::cout<<"pi:"<<p[i]<<'\n';
        sum1+=cnt[p[i]];
        sum2+=std::min((ll)a*cnt[p[i]],(ll)(i-1)*b*cnt[p[i]]);
        ans=std::min(ans,(ll)(n*m-sum1-cnt[0])*a+(ll)cnt[0]*i*b+sum2);
        // std::cout<<"ans:"<<ans<<'\n';
    }
    ans=std::min(ans,(ll)(n*m-cnt[0])*a);
    std::cout<<ans<<'\n';
}
int main()
{
    int T;
    std::cin>>T;
    while(T--) solve();
}
