#include<bits/stdc++.h>
#include<vector>
using namespace std;
int main(){
    string s;
    getline(cin, s);
    vector<char> v;
    for(int i = 0;i<s.length();i++){
        if('a' <= s[i] && s[i] <= 'z' || 'A' <= s[i] && s[i] <= 'Z')
        {
            if('a' <= s[i] && s[i] <= 'z' ) s[i] -= 32;
            v.push_back(s[i]);
            i++;
            while('a' <= s[i] && s[i] <= 'z' || 'A' <= s[i] && s[i] <= 'Z'){
                if('A' <= s[i] && s[i] <= 'Z') s[i] +=32;
                v.push_back(s[i]);
                i++;
            }
            i--;
            v.push_back(' ');
        }
    }
    v.pop_back();
    for(int i = 0; i<v.size(); i++){
        cout<<v[i];
    }
}