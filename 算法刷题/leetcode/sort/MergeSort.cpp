#include <vector>

void MergeSort(std::vector<int> &nums, std::vector<int> &copy, int low, int high)
{
    if (low >= high) return;
    int mid = (low + high) / 2;
    MergeSort(nums, copy, low, mid);
    MergeSort(nums, copy, mid+1, high);
    int low1 = low, low2 = mid+1, high1 = mid, high2 = high;
    int index = low;
    while (low1 <= high1 && low2 <= high2)
    {
        copy[index++] = nums[low1] > nums[low2] ? nums[low2++] : nums[low1++];
    }
    while (low1 <= high1)
    {
        copy[index++] = nums[low1++];
    }
    while (low2 <= high2)
    {
        copy[index++] = nums[low2++];
    }
    for(int i = low; i <= high; ++i)
    {
        nums[i] = copy[i];
    }
}