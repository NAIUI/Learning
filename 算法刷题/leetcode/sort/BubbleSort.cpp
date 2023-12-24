#include <vector>

void BubbleSort(std::vector<int> &nums){
    bool flag = true;
    for (int i = 0; i < nums.size() - 1; ++i){
        flag = true;
        for (int j = 0; j < nums.size() - i - 1; ++j){
            if (nums[j] > nums[j+1]){
                flag = false;
                std::swap(nums[j], nums[j+1]);
            }
        }
        if (flag) break;
    }
}