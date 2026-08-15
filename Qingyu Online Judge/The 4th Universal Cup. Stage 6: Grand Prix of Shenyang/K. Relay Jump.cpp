#include <bits/stdc++.h>
using ll=long long;
void solve(){
    int n,t;std::cin>>n>>t;
    std::vector<int> x1(n+5),y1(n+5),x2(n+5),y2(n+5);
    ll sx=0,sy=0;
    for(int i=1;i<=n;i++){
        std::cin>>x1[i]>>y1[i]>>x2[i]>>y2[i];
        sx+=x2[i]-x1[i],sy+=y2[i]-y1[i];
    }
    for(int i=1;i<=n;i++){
        if(sx==(ll)2*(x2[i]-x1[t])&&sy==(ll)2*(y2[i]-y1[t])){
            std::cout<<i<<'\n';
            return;
        }
    }
}
int main()
{
    int T;T=1;
    while(T--) solve();
}
