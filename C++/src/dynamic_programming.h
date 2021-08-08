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

    //322. 零钱兑换
    class Solution_322 {
    public:
        int coinChange(vector<int>& coins, int amount) {
            vector<int> dp(amount + 1, amount + 1);
            dp[0] = 0;
            for (int i = 1; i <= amount; i++) {
                for (auto coin : coins) {
                    if (coin > i) continue;
                    dp[i] = min(dp[i], dp[i - coin] + 1);
                }
            }
            int ans = dp[amount] == amount + 1 ? -1 : dp[amount];
            return ans;
        }
    };

    //931. 下降路径最小和
    class Solution_931 {
    public:
        int minFallingPathSum(vector<vector<int>>& matrix) {
            if (matrix.empty()) return 0;
            vector<vector<int>> dp(matrix.size(), vector<int>(matrix[0].size(), 0));
            int rows = matrix.size();
            int cols = matrix[0].size();
            int min_path_sum = INT_MAX;
            for (int i = 0; i < cols; i++) {
                dp[0][i] = matrix[0][i];
                if (rows == 1) min_path_sum = min(min_path_sum, dp[0][i]);
            }

            for (int i = 1; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    if (j == 0) {
                        dp[i][j] = min(dp[i - 1][j], dp[i - 1][j + 1]) + matrix[i][j];
                    }
                    else if (j == cols - 1)
                    {
                        dp[i][j] = min(dp[i - 1][j - 1], dp[i - 1][j]) + matrix[i][j];
                    }
                    else {
                        dp[i][j] = min(min(dp[i - 1][j - 1], dp[i - 1][j]), dp[i - 1][j + 1]) + matrix[i][j];
                    }
                    if (i == rows - 1) min_path_sum = min(min_path_sum, dp[i][j]);
                }
            }
            return min_path_sum;
        }
    };
}