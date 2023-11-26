// 汉诺塔问题
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    void hanota(vector<int>& A, vector<int>& B, vector<int>& C) {
        move(A, B, C, A.size());
    }

    void move(vector<int>& A, vector<int>& B, vector<int>& C, int n) {
        if (n > 1) move(A, C, B, n-1);
        C.push_back(A.back());
        A.pop_back();
        if (n > 1) move(B, A, C, n-1);
    }
};