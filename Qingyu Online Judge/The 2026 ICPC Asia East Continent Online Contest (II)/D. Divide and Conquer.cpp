#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x=0,f=1;char ch=getchar();
    for(;!isdigit(ch);ch=getchar())f^=ch=='-';
    for(;isdigit(ch);ch=getchar())x=x*10+(ch^48);
    return f?x:-x;
}

template<class T>
inline void chmax(T &x,T y){x<y?x=y:0;}
template<class T>
inline void chmin(T &x,T y){x>y?x=y:0;}

const int N=1e6+5,mo=998244353;

vector<array<int,2>> input[N];

vector<int> used,rr;

int n,q,lim[N],a[N],b[N],sgn[N],fail,L[N],R[N],vis[N];

int totA[N],totB[N];

array<int,2> sgm[N];

#define lc p<<1
#define rc p<<1|1

void build(int p,int l,int r){
    L[p]=l,R[p]=r;
    if(l==r){
        return;
    }
    int mid=(l+r)>>1;
    build(lc,l,mid);
    build(rc,mid+1,r);
}

signed main(){
    n=1<<read(),q=read(),fail=0;
    used={n};
    memset(lim,-1,sizeof(lim));
    lim[1]=n;
    build(1,1,n);
    input[n].push_back({1,n});
    for(int i=1;i<=q;++i){
        int u=read(),x=read();
        if(lim[u]==-1){
            lim[u]=x;
        }else{
            if(lim[u]!=x){
                fail=1;
            }
        }
        input[x].push_back({L[u],R[u]});
        used.push_back(x);
    }
    sort(used.begin(),used.end());
    for(int i=0,j;i<used.size();i=j){
        j=i+1;
        while(j<used.size()&&used[i]==used[j])++j;
        rr.push_back(used[i]);
        vis[used[i]]=1;
    }
    used.clear();
    for(int x:rr){
        // sort(input[x].begin(),input[x].end(),[](auto x,auto y){
        //     auto [lx,rx]=x;
        //     auto [ly,ry]=y;
        //     return rx-lx>ry-ly;
        // });
        int L=1,R=n;
        for(auto [l,r]:input[x]){
            chmax(L,l),chmin(R,r);
        }
        if(R<L){
            fail=1;
        }else{
            sgm[x]={L,R};
        }
    }
    for(int i=1;i<=n;++i){
        int id=i+n-1,last=-1,first=-1;
        while(id!=0){
            if(lim[id]!=-1){
                if(last!=-1){
                    if(lim[id]<last){
                        fail=1;
                        break;
                    }else{
                        last=lim[id];
                    }
                }else{
                    first=id;
                    last=lim[id];
                }
            }
            id=id/2;
        }
        a[i]=lim[first];
        int DL=sgm[a[i]][0],DR=sgm[a[i]][1];
        if(DL==L[first]&&DR==R[first]){
            b[i]=1;
        }
    }
    if(fail){
        puts("0");
        return 0;
    }
    for(int i=1;i<=n;++i){
        if(b[i])++totB[a[i]];
        else ++totA[a[i]];
    }
    int ans=1,avai=0;
    for(int i=n;i>=1;--i){
        if(vis[i]){
            ans=ans*totB[i]%mo;
        }else{
            ans=ans*avai%mo;
        }
        avai=avai+totB[i]+totA[i]-1;
    }
    printf("%lld\n",ans);
}
