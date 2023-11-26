#include <vector>

void QuickSort(std::vector<int> &nums, int begin, int end)
{
    int temp = nums[begin];
    int i = begin, j = end;
    while ( i != j)
    {
        while (j > i && nums[j] >= temp) j--;
        while (j > i && nums[i] <= temp) i++;
        if (j > i)
        {
            std::swap(nums[i], nums[j]);
        }
    }
    nums[begin] = nums[i];
    nums[i] = temp;
    QuickSort(nums,begin,i-1);
    QuickSort(nums,i+1,end);
}