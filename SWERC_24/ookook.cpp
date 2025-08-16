#include <iostream>
#include <string>
using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string w;                    
    cin >> w;

    for (char c : w) {
        if (c == 'O')
            cout << ".-.-";      
        else                     
            cout << ".-";        
    }
    cout << '\n';
    return 0;
}