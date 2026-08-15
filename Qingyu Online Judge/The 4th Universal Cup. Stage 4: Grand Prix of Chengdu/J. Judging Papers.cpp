#include <bits/stdc++.h>
void solve(){
    int n,m,k,b;
    std::cin>>n>>m>>k>>b;
    int cnt=0,cnt1=0;
    for(int i=1;i<=n;i++){
        int s1=0,s2=0;
        for(int j=1;j<=m;j++){
            int x;std::cin>>x;
            s1+=x;s2+=(x<1?x+1:x-1);
        }
        if(s1>=k) cnt++;
        else if(s2>=k) cnt1++;
    }
    std::cout<<cnt+std::min(cnt1,b)<<'\n';
}
int main()
{
    int T;std::cin>>T;
    while(T--) solve();
}
