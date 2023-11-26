#include <vector>

void Heapify(std::vector<int> &nums, int n, int i)
{
    int l = i*2+1, r = i*2+2;
    int max = i;
    if (l < n && nums[max] < nums[l]) max = l;
    if (r < n && nums[max] < nums[r]) max = r;
    if (max != i)
    {
        std::swap(nums[max], nums[i]);
        Heapify(nums, n, max);
    }
}

void Heapify_build(std::vector<int> &nums, int n)
{
    int temp = n/2 - 1;
    for (int i = temp; i >= 0; --i)
    {
        Heapify(nums, n, i);
    }
}

void HeapifySort(std::vector<int> &nums, int n)
{
    Heapify_build(nums, n);
    for (int i = 0; i < n; ++i)
    {
        std::swap(nums[0], nums[n-i-1]);
        Heapify(nums, n-i-1, 0);
    }
}