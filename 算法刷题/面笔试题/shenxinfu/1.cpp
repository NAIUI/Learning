#include <iostream>

using namespace std;

int main() {
    int a = 2, b = 10;
//    cin >> a >> b;

    if (b == 0) return 1;
    int res = a;
    while (b > 1){
        res = res * a;
        res = res % 10;
        b--;
    }
    cout << res << endl;
    return 0;
}