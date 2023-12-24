class Solution {
public:
    int hIndex(vector<int>& citations) {
        int len = citations.size();
        int left = 0, right = len-1;
        int res = 0;
        while (left <= right)
        {
            int mid = (left + right) / 2;
            if  (citations[mid] == (len-mid))
            {
                res = len-mid;
                break;
            }else if (citations[mid] < (len-mid))
            { 
                left = mid + 1;
            }
            else 
            {
                res = len - mid;
                right--;
            }
        }
        return res;
    }
};