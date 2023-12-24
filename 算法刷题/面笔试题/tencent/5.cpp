#include <bits/stdc++.h>

int main(){
    int n = 2, k = 1;
    std::vector<int> nums;
    std::cin >> n >> k;
    // std::cin >> n;
    // std::cin >> k;
    for(int i = 0; i < n; i++){
        int x; scanf("%d",&x);
        nums.push_back(x);
    }

    sort(nums.begin(), nums.end());

    while (k-- > 0){
        int i = nums[nums.size()-1];
        int temp = 1;
        while (temp < i) temp *=2;
        if (temp == i) {
            nums[nums.size()-1] = 0;
        }else{
            nums[nums.size()-1] = i - temp/2;
        }
        sort(nums.begin(), nums.end());
    }

    int res = 0;
    for (auto i : nums) res += i;

    std::cout << res << std::endl;

    return -1;
}