#include <bits/stdc++.h>

using namespace std;

void func(vector<vector<int>> &nums, vector<vector<int>> &res){
    int first = nums[0][0];
    for (int i = 1; i <= first; ++i){ // 1 2 3 4 5 6
        vector<int> temp;
        int aLen = nums[(i-1)*3+1][0];
        int bLen = aLen - 1;
        vector<int> a = nums[(i-1)*3+2];
        vector<int> b = nums[(i-1)*3+3];
        sort(a.begin(),a.end());
        int mid = aLen%2 ? a[aLen/2] : (a[aLen/2]+a[aLen/2+1])/2;
        temp.push_back(mid);
        for (int j = 0; j < bLen; j++){
            for (int ii = b[j]; ii < aLen - 1; ++ii){
                a[ii] = a[ii+1];
            }
            aLen--;
            mid = aLen%2 ? a[aLen/2] : (a[aLen/2]+a[aLen/2+1])/2;
            temp.push_back(mid);
        }
        res.push_back(temp);
    }
}

int main(){
    //freopen("1.in","r",stdin);
    int n;
    vector<vector<int>> nums;
    vector<vector<int>> res;
    cin >> n;
    nums.push_back({n});
    for(int i = 0; i < n; i++){
        int m;
        cin >> m;
        nums.push_back({m});
        vector<int> temp;
        for(int j = 0; j < m; j++){
            int x; scanf("%d",&x);
            temp.push_back(x);
        }
        nums.push_back(temp);
        temp.clear();
        for(int j = 0; j < m-1; j++){
            int x; scanf("%d",&x);
            temp.push_back(x);
        }
        nums.push_back(temp);
    }

    func(nums, res);

    for (auto i : res){
        for (auto j : i){
            cout << j << " ";
        }
        cout << endl;
    }

    return 0;
}