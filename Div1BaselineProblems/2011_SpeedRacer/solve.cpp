#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

bool check(double a, double b, double c, double d, double v, double m, double t){
    double first = (a*v*v*v*v);
    double second = (b*v*v*v);
    double third = (c*v*v);
    double fourth = (d*v);

    return ((first + second + third + fourth)*(m/v)  <=  t+1e-12L);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    double a, b, c, d, m, t; 

    while (cin >> a >> b >> c >> d >> m >> t){
    
        double l = 0.0L, r = 1.0L;

        while(check(a,b,c,d,r,m,t)) r *= 2.0L;

        // Binary search until precision is enough for 2 decimals
        for(int i = 0; i < 5000; ++i) {  
            double mid = (l + r) / 2.0L;

            if (check(a, b, c, d, mid, m, t)) {
                l = mid;     
            } else {
                r = mid;    
            }
        }
        
        double res = floor((l+1e-12L) * 100.0L)/100.0L;
        while(!check(a,b,c,d,res,m,t)) res -= 0.01L;

        cout << std::fixed << setprecision(2) << res << '\n';
    }
    return 0;




}
