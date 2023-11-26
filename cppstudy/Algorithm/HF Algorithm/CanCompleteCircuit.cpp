//https://leetcode.cn/problems/gas-station/description/
// 加油站问题
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int curNum = 0, totalNum = 0;
        int idx = 0;
        for (int i = 0; i < gas.size(); ++i){
            curNum += gas[i] - cost[i];
            totalNum += gas[i] - cost[i];
            if (curNum < 0){
                idx = i + 1;
                curNum = 0;
            }
        }

        return totalNum < 0 ? -1 : idx;
    }
};