#include <bits/stdc++.h>
// #define int long long
#define VI vector<int>
using namespace std;

inline int read(){
    int x=0,f=1;char ch=getchar();
    for(;!isdigit(ch);ch=getchar())f^=ch=='-';
    for(;isdigit(ch);ch=getchar())x=x*10+(ch^48);
    return f?x:-x;
}

VI compose(VI &x,VI &y){
    VI ret=x;
    for(int i=0;i<x.size();++i)ret[i]=x[y[i]];
    return ret;
}

void solve(){
    int n=read(),m=read(),tag=1;
    vector<VI> p(m),perm;
    for(int i=0;i<m;++i){
        for(int j=0;j<n;++j)p[i].push_back(read()-1);
    }
    VI I(n);
    iota(I.begin(),I.end(),0);
    perm.push_back(I);
    for(int i=0;i<m;++i){
        vector<VI> tmp,rperm;
        for(VI& x:perm){
            VI rr=compose(x,p[i]);
            if(rr==I)tag=0;
            tmp.push_back(rr);
        }
        for(VI& x:tmp)perm.push_back(x);
        sort(perm.begin(),perm.end());
        for(int l=0,r;l<perm.size();l=r){
            r=l+1;
            while(r<perm.size()&&perm[l]==perm[r])++r;
            rperm.push_back(perm[l]);
        }
        perm.swap(rperm);
    }
    cout<<perm.size()-tag<<endl;
}

signed main(){
    // for(int cas=read();cas--;){
        solve();
    // }
}
