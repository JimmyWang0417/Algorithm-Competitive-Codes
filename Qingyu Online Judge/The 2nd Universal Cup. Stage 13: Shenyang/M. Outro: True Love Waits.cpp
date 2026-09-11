#include <bits/stdc++.h>

#define int long long
#define VI vector<int>

using namespace std;

inline int read(){
    int x=0,f=1;char ch=getchar();
    for(;!isdigit(ch);ch=getchar())f^=ch=='-';
    for(;isdigit(ch);ch=getchar())x=x*10+(ch^48);
    return f?x:-x;
}
template<typename T>inline void chmin(T &x,T y){x>y?x=y:y;}
template<typename T>inline void chmax(T &x,T y){x<y?x=y:y;}

const int mo=1e9+7,inf=1e15;

mt19937 rnd(time(0));

inline void red(int &x){(x>=mo)&&(x-=mo);}
inline int qpow(int x,int t=mo-2){
    int ret=1;
    for(;t;t>>=1,x=x*x%mo)if(t&1)ret=ret*x%mo;
    return ret;
}

int fastcalc(int n){
    return (qpow(4,n)-1)*qpow(3)%mo*4%mo;
}

VI fpow,step;

string s,t;
int k;

void solve(){
    cin>>s>>t;
    k=read();
    reverse(s.begin(),s.end());
    reverse(t.begin(),t.end());
    if(s==t){
        printf("%lld\n",fastcalc(k-1));
        return;
    }
    int len=max(s.size(),t.size());
    if(len&1)++len;
    while(s.size()<len)s.push_back('0');
    while(t.size()<len)t.push_back('0');
    for(int i=0;i<len;++i){
        if(s[i]!=t[i])s[i]='1';
        else s[i]='0';
    }
    int upk=1;
    for(int i=1;i<len;i+=2){
        int u=i-1,v=i;
        if(s[i]!='0'||s[i-1]!='0'){
            break;
        }else ++upk;
    }
    if(upk<k){
        puts("-1");
        return;
    }
    int ans=fastcalc(k-1);
    for(int i=1,j=0;i<len;i+=2,++j){
        string tmp="";
        tmp+=s[i-1];
        tmp+=s[i];
        if(tmp=="00"){

        }else if(tmp=="11"){
            red(ans+=step[j]*2%mo);
        }else if(tmp=="01"){
            red(ans+=step[j]*3%mo);
        }else if(tmp=="10"){
            red(ans+=step[j]);
        }
    }
    printf("%lld\n",ans);
    return;
}

const int V=5e6+5;

signed main(){
    step=fpow=VI(V,0);
    
    fpow[0]=step[0]=1;
    for(int i=1;i<V;++i){
        fpow[i]=fpow[i-1]*4%mo;
        red(step[i]=step[i-1]+fpow[i]);
    }

    for(int cas=read();cas--;){
        solve();

    }
    return 0;
}
