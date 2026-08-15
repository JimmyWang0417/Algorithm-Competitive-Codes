#include <bits/stdc++.h>
int main()
{
    int m;std::cin>>m;
    std::vector<int> b(m+5);
    for(int i=1;i<=m;i++){
        std::cin>>b[i];
    }
    int n;std::cin>>n;
    for(int T=1;T<=n;T++){
        int l;std::cin>>l;
        std::vector<int> a(l+5);
        for(int i=1;i<=l;i++) std::cin>>a[i];
        std::vector<int> cnt(m+5,0);cnt[0]=l+5;
        for(int i=1;i<=l;i++){
            for(int j=1;j<=m;j++){
                if(a[i]==b[j]) cnt[j]=std::min(cnt[j]+1,cnt[j-1]);
            }
        }
        std::cout<<cnt[m]<<'\n';
    }
}
