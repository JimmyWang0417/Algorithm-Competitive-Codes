#include <bits/stdc++.h>
using namespace std;

using LL=long long;
using ai2=array<int,2>;
using al2=array<LL,2>;

constexpr LL inf=1000000000ll;
void solve(){
    int n;
    cin>>n;
    vector<al2>a(n);
    LL L=0,R=0;
    for(int i=0;i<n;++i){
        LL x; cin>>x;
        a[i]=al2{max(0ll,x*10000000ll-5000000ll),min(inf,x*10000000ll+4999999ll)};
        L+=a[i][0];
        R+=a[i][1];
    }
    if(inf<L || R<inf){
        cout<<"No\n";
        return;
    }
    LL sum=inf-L;
    vector<LL>ans(n);
    for(int i=0;i<n;++i){
        ans[i]=a[i][0];
        const LL x=a[i][1]-a[i][0];
        const LL sub=min(sum,x);
        sum-=sub;
        ans[i]+=sub;
    }
    cout<<"Yes\n";
    for(auto& x:ans) cout<<x<<' ';
    cout<<'\n';
}
int main()
{
    int T;std::cin>>T;
    while(T--) solve();
}
