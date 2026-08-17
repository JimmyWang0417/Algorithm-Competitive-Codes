#include <bits/stdc++.h>
using ll=long long;
// constexpr ll mx=1e12;
const int mod=998244353;
const int inv2=499122177;
// const ll inf = 1e18;
const int inf=1e9;
const int N = 10005, M = 500005;
struct Solve{
    struct p{
        int x,y;
    };
    void solve(){
       int n;std::cin>>n;
       if(n>180) return (void) (std::cout<<"NO\n");
       std::vector<int> pts={50,25,0};
       for(int i=1;i<=20;i++) pts.emplace_back(i),pts.emplace_back(2*i),pts.emplace_back(3*i);
       std::vector<p> v(200,(p){-1,-1});
       for(int i=0;i<pts.size();i++){
            for(int j=0;j<pts.size();j++){
                v[pts[i]+pts[j]]=(p){pts[i],pts[j]};
            }
       }
       
        if(n>=50){
            int n1=n-50;
            if(v[n1].x!=-1){
                std::cout<<"YES\n";
                std::cout<<3<<'\n'<<v[n1].x<<' '<<v[n1].y<<' '<<50<<'\n';
                return;
            }
        }
        for(int i=1;i<=20;i++){
            if(n>=2*i){
                if(v[n-2*i].x!=-1){
                    int n1=n-2*i;
                    std::cout<<"YES\n";
                    std::cout<<3<<'\n'<<v[n1].x<<' '<<v[n1].y<<' '<<2*i<<'\n';
                    return;
                }
            }
        }
        std::cout<<"NO\n";
       
       
    }
};
void solve(){
    Solve a;a.solve();
}

int main()
{
   int T=1;
//    std::cin>>T;
   while(T--) solve();
}
