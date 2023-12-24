#include <vector>

void ShellSort(std::vector<int> &nums)
{
    int len = nums.size();
    for (int gap = len/2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < len; ++i)
        {
            int temp = nums[i];
            int j;
            for (j = i - gap; j >= 0 && nums[j] > temp; j -= gap)
            {
                nums[j+gap] = nums[j];
            }
            nums[j+gap] = temp;
        }
    }
}