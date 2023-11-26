#include <vector>

void InsertionSort(std::vector<int> nums){
    for (int i = 1; i < nums.size(); ++i){
        int flag = i;
        while (flag >= 0 && nums[flag] < nums[flag-1]){
            std::swap(nums[flag], nums[flag-1]);
            flag--;
        }
    }
}