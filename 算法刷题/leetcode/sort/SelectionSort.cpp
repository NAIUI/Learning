#include <vector>

void SelectionSort(std::vector<int> nums){
    for (int i = 0; i < nums.size() - 1; ++i){
        int min = i;
        for (int j = i + 1; j < nums.size(); ++j){
            if (nums[min] > nums[j]) min = j;
        }
        std::swap(nums[min], nums[i]);
    }
}