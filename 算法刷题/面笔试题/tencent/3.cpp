#include <bits/stdc++.h>

int main(){
    int n = 0;
    std::vector<int> nums;
    nums.push_back(0);
    std::cin >> n;
    for(int i = 0; i < n; i++){
        int x; scanf("%d",&x);
        nums.push_back(x);
    }

    sort(nums.begin(), nums.end());

    int left = 0, right = nums.size()-1;

    int res = 0;

    while (left < right){
        res += nums[right--] - nums[left++];
    }

    std::cout << res << std::endl;

    return 0;
}