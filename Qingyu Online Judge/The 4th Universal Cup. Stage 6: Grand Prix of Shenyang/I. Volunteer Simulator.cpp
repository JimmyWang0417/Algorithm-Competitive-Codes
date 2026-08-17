#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;

#define N 420
#define M 14
void solve(){
    int n; cin>>n;
    vector<int>ans(N),out;
    vector flag(N,vector<int>(M));
    for(int i,j,t;n--;){
        cin>>i>>j>>t;
        bool ok=0;
        if(!flag[i][j]){
            if(t<240) ok=1;
            else if(ans[i]<3) ok=1;
        }
        if(ok){
            ++ans[i];
            out.emplace_back(j);
        }
        else{
            out.emplace_back(0);
        }
        flag[i][j]=1;
    }
    for(auto& x:out) cout<<x<<'\n';
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    while (T--) solve();
    return 0;
}
