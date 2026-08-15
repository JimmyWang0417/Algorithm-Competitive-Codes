#include <bits/stdc++.h>
void print(std::string s){
    int l=0;
    int n=s.size();
    while(s[l]=='0'&&l<n-1) l++;
    for(;l<n;l++) std::cout<<s[l];
    std::cout<<'\n';
}
bool cmp(std::string s1,std::string s2){
    int n=s1.size(),m=s2.size();
    int l1=0,l2=0;
    while(s1[l1]=='0'&&l1<n-1) l1++;
    while(s2[l2]=='0'&&l2<m-1) l2++;
    if(n-l1!=m-l2) return n-l1>m-l2;
    else{
        for(int i1=l1,i2=l2;i1<n&&i2<m;i1++,i2++){
            if(s1[i1]!=s2[i2]) return s1[i1]>s2[i2];
        }
    }
    return 1;
}
void solve(){
    std::string s;std::cin>>s;
    int n=s.size();
    std::string s1=s.substr(2,n-2),s2=s.substr(0,n-2);
    s1[n-3]=(s[0]=='0'?s1[n-3]:'0'+((s1[n-3]-'0')^1));
    s2[n-3]=(s[n-1]=='0'?s2[n-3]:'0'+((s2[n-3]-'0')^1));
    if(n<=4){
        if(s1<s2) print(s2);
        else print(s1);
    } else {
        std::string s3=s.substr(3,n-3),s4=s.substr(0,n-3),s5=std::max(s1,s2);
        s3[n-4]=((s3[n-4]-'0')^(s[1]-'0')+'0');
        s3[n-5]=((s3[n-5]-'0')^(s[0]-'0')+'0');
        s4[n-4]=((s3[n-4]-'0')^(s[n-1]-'0')+'0');
        s4[n-5]=((s3[n-5]-'0')^(s[n-2]-'0')+'0');
        std::string s6=std::max(s3,s4);
        if(cmp(s6,s5)) print(s6);
        else print(s5);
    }
}
int main()
{
    int T;std::cin>>T;
    while(T--) solve();
}
