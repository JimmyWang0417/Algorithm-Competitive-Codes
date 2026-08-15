#include <bits/stdc++.h>
using namespace std;

// #define LOCAL
#ifdef LOCAL
#define debug(...) fprintf(stderr,##__VA_ARGS__)
#else
#define debug(...) 42
#endif

using LL=long long;
#define all(x) (x).begin(),(x).end()

void solve(){
    int n; cin>>n;
    vector<LL>a(n+1),s(n+1);
    for(int i=1;i<=n;++i) cin>>a[i];
    sort(all(a));
    for(int i=1;i<=n;++i){
        s[i]=s[i-1]+a[i];
        debug("s[%d]=%lld\n",i,s[i]);
    }
    auto get=[&](int l,int r)->LL{
        return s[r]-s[l-1];
    };
    vector<int>b(n+1);
    for(int i=3;i<=n;++i){
        int l=1,r=i-2,mid,opt=0;
        while(l<=r){
            mid=l+r>>1;
            if(get(mid,i-1)>a[i]){
                opt=mid;
                l=mid+1;
            }
            else r=mid-1;
        }
        b[i]=opt;
    }
    vector<int>ans(n+1,0);
    for(int i=1;i<=n;++i){
        if(b[i]) ans[i-b[i]+1]=i;
        debug("b[%d]=%d\n",i,b[i]);
    }
    for(int i=1;i<=n;++i){
        ans[i]=max(ans[i],ans[i-1]);
    }
    for(int i=1;i<=n;++i){
        if(ans[i]>=i) cout<<get(ans[i]-i+1,ans[i])<<' ';
        else cout<<"0 ";
    }
    cout<<'\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int t; cin>>t;
    while(t--) solve();
    return 0;
}
