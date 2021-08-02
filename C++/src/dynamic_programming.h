#pragma once
#include<vector>
using namespace std;
namespace dynamic_programming {
    //53. 最大子序和
    class Solution_53 {
    public:
        /*
        //算法计算复杂度O(n),空间复杂度O(n); 
        int maxSubArray(vector<int>& nums) {
            if (nums.empty()) return 0;
            vector<int> dp;
            dp.resize(nums.size());
            dp[0] = nums[0];
            int max_result = nums[0];
            for (int i = 1; i < nums.size(); i++) {
                dp[i] = max(nums[i], dp[i - 1] + nums[i]);
                max_result = max(max_result, dp[i]);
            }
            return max_result;
        }
        */
        struct LRSum
        {
            int lsum, rsum, lrsum, isum;
            LRSum() {}
            LRSum(int left_sum, int right_sum, int left_right_sum, int mid_sum) {
                this->lsum = left_sum;
                this->rsum = right_sum;
                this->lrsum = left_right_sum;
                this->isum = mid_sum;
            }
        };
        LRSum UpSum(LRSum& left, LRSum& right) {
            int left_sum = max(left.lsum, left.lrsum + right.lsum);
            int right_sum = max(left.rsum + right.lrsum, right.rsum);
            int left_right_sum = left.lrsum + right.lrsum;
            int mid_sum = max(max(left.isum, right.isum), left.rsum + right.lsum);
        }

        LRSum helper(vector<int>& nums, int left, int right) {
            if (left == right) {
                return LRSum(nums[left], nums[left], nums[left], nums[left]);
            }
            int mid = (left + right) >> 1;
            LRSum left_sum_data = helper(nums, left, mid);
            LRSum right_sum_data = helper(nums, mid + 1, right);
            return UpSum(left_sum_data, right_sum_data);
        }


        int maxSubArray(vector<int>& nums) {
            LRSum sum_data = helper(nums, 0, nums.size() - 1);
            return sum_data.isum;
        }

    };













}