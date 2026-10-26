#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
namespace __gnu_rb_tree
{
    using namespace __gnu_pbds;
    template <class Key, class Mapped = null_type, class Cmp = std::less<Key>>
    using rb_tree = tree<Key, Mapped, Cmp, rb_tree_tag, tree_order_statistics_node_update>;
}
using __gnu_rb_tree::rb_tree;

#define int long long
#define VI vector<int>
using namespace std;
inline int read(){
    int x=0,f=1;char ch=getchar();
    for(;!isdigit(ch);ch=getchar())f^=ch=='-';
    for(;isdigit(ch);ch=getchar())x=x*10+(ch^48);
    return f?x:-x;
}

template<class T>inline void chmin(T &x,T y){x>y?x=y:0;}
template<class T>inline void chmax(T &x,T y){x<y?x=y:0;}

int n,cnt[10],upcnt[10],q;

string X,Ystr;
VI Y;

rb_tree<int> pos[10],uppos[10],downpos[10];

int getval(rb_tree<int> &t,int id){
    if(id<0)return -1;
    if(id>=t.size())return n-1;
    else return *t.find_by_order(id)-1; 
}

int getdd(rb_tree<int> &t, int x){
    if(t.empty()) return -1;
    auto it=t.upper_bound(x);
    if(it==t.begin()) return -1;
    return *(--it);
}

struct fenwick{
    VI s;
    int n;
    fenwick(int _n=0):s(VI(_n+10,0)),n(_n+5){}
    void add(int x,int t){
        ++x,++x,++x;
        for(;x<=n;x+=x&-x)s[x]+=t;
    }
    int ask(int x){
        ++x,++x,++x;int ret=0;
        for(;x;x-=x&-x)ret+=s[x];
        return ret;
    }
}CC[10];

int ask(int pp){
    int gaai=n-1;
    for(int i=0;i<=9;++i){
        chmin(gaai,getval(pos[i],cnt[i]));
    }
    if(gaai==n-1)return Y[pp];
    else{
        int maxdiff=-1;
        for(int D=0;D<9;++D){
            int rg=getval(uppos[D],upcnt[D]-1);
            int tmp=getdd(downpos[D],min(gaai+1,rg));
            chmax(maxdiff,tmp);
        }
        if(maxdiff==-1)return -1;
        if(pp<maxdiff)return Y[pp];
        else{
            VI use(11,0);
            for(int i=0;i<=9;++i){
                use[i]=cnt[i]-CC[i].ask(maxdiff-1);
            }
            int digit=Y[maxdiff],rrd=-1;
            for(int i=digit+1;i<=9;++i){
                if(use[i]){
                    rrd=i;
                    break;
                }
            }
            if(pp==maxdiff)return rrd;
            --use[rrd];
            pp-=maxdiff;
            for(int D=0;D<=9;++D){
                if(pp<=use[D])return D;
                else pp-=use[D];
            }
            return -1;
        }
    }
}

void solve(){
    cin>>X>>Ystr;
    q=read(),n=X.size();
    for(int i=0;i<n;++i){
        ++cnt[X[i]-'0'];
        for(int j=0;j<X[i]-'0';++j){
            ++upcnt[j];
        }
    }
    for(int D=0;D<=9;++D){
        CC[D]=fenwick(n+5);
    }
    for(int i=0;i<n;++i){
        int digit=Ystr[i]-'0';
        Y.push_back(digit);
        pos[digit].insert(i);
        for(int j=0;j<digit;++j){
            uppos[j].insert(i);
        }
        for(int j=digit;j<=9;++j){
            downpos[j].insert(i);
        }
        CC[digit].add(i,1);
    }
    while(q--){
        int opt=read();
        if(opt==1){
            int i=read()-1,x=read();
            pos[Y[i]].erase(i);
            CC[Y[i]].add(i,-1);
            pos[x].insert(i);
            CC[x].add(i,1);
            for(int j=0;j<Y[i];++j){
                uppos[j].erase(i);
            }
            for(int j=Y[i];j<=9;++j){
                downpos[j].erase(i);
            }
            for(int j=0;j<x;++j){
                uppos[j].insert(i);
            }
            for(int j=x;j<=9;++j){
                downpos[j].insert(i);
            }
            Y[i]=x;
        }else{
            int i=read()-1;
            printf("%lld\n",ask(i));
        }
    }
}

signed main(){
    solve();
}
