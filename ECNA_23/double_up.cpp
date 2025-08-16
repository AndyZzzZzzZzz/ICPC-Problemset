#include <stack>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main(){

    int n;
    cin >> n;

    vector<int> integers(n, 0);
    for(int i = 0;  i < n; i ++){
        cin >> integers[i];
    }

    

    stack<int> stk;
    for(int i = 0; i < n; i ++){
        int curr = integers[i];

        if(!stk.empty() && stk.top() == curr){
            while(!stk.empty() && stk.top() == curr){
                stk.pop();
                curr = 2 * curr;
            }
        }
    }
    
    cout << stk.top() << endl;
    cout << stk.size();
    return 0;
}