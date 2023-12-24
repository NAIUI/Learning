// 数字循坏右移求最大，大整数
#include <iostream>
using namespace std;

int main() {
    string s;
    cin >> s;

    string res = s;
    for (int i = 1; i < s.size(); ++i){
        string s1 = s.substr(0,i);
        string s2 = s.substr(i,s.size()-i);
        string s3 = s2 + s1;
        if (s3 > res) res = s3;
    }

    cout << res << endl;

    return 0;
}