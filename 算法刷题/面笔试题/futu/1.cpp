#include <bits/stdc++.h>

using namespace std;

int main() {
    int n = 0, k = 0;
    cin >> n >> k;
    vector<vector<int>> vec;
    for (int i = 0; i < n; ++i){
        vector<int> temp;
        for (int j = 0; j < k; ++j){  
            int x; scanf("%d", &x);
            temp.push_back(x);
        }
        vec.push_back(temp);
    }

    int res = 0;
    for (int i = 0; i+1 < vec.size(); ++i){
        vector<int> vec1 = vec[i];
        for (int j = i+1; j < vec.size(); ++j){
            vector<int> vec2 = vec[j];
            int sum = vec1[0] + vec2[0];
            bool tag = true;
            for (int k = 1; k < vec1.size(); ++k){
                if (vec1[k] + vec2[k] != sum) {
                    tag = false;
                    break;
                }
            }
            if(tag) res++;
        }
    }
    cout << res << endl;
    return 0;
}