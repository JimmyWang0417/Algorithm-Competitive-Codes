#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    while (n--) {
        string s;
        cin >> s;
        string res;
        for (char c : s) {
            if (c != '1' && c != 'i' && c != 'I' && c != 'l') {
                res += c;
            }
        }
        cout << res << '\n';
    }
    
    return 0;
}