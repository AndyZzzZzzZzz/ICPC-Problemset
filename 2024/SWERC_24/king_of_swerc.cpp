#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
using namespace std;

int main(){

    unordered_map<string, int> mp;

    int n;
    cin >> n;

    for(int i = 0; i < n; i ++){
        string temp;
        cin >> temp;
        mp[temp] ++;
    }

    int res = 0;
    string s;
    for(auto p: mp) {
        if(p.second > res){
            res = p.second;
            s = p.first;
        }
    }

    cout << s << endl;
    return 0;
}