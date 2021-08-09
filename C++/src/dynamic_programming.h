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

    //516：最长回文子序列
    class Solution_516 {
    public:
        int longestPalindromeSubseq(string s) {
            if (s.empty()) return 0;
            vector<vector<int>> dp(s.size(), vector<int>(s.size(), 0));
            for (int i = 0; i < s.size(); i++) {
                dp[i][i] = 1;
            }
            for (int i = s.size() - 1; i >= 0; i--)
            {
                for (int j = i + 1; j < s.size(); j++) {
                    if (s[i] == s[j]) dp[i][j] = dp[i + 1][j - 1] + 2;
                    else
                    {
                        dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
                    }
                }
            }
            return dp[0][s.size() - 1];
        }
    };

    //1143 最长公共子序列
    class Solution_1143 {
    public:
        int longestCommonSubsequence(string text1, string text2) {
            if (text1.empty() || text2.empty()) return 0;
            vector<vector<int>> dp(text1.size(), vector<int>(text2.size(), 0));
            int rows = text1.size(), cols = text2.size();
            if (text1[0] == text2[0]) dp[0][0] = 1;
            for (int i = 1; i < cols; i++) {
                if (text1[0] == text2[i]) dp[0][i] = 1;
                else dp[0][i] = dp[0][i - 1];
            }
            for (int i = 1; i < rows; i++) {
                if (text1[i] == text2[0]) dp[i][0] = 1;
                else dp[i][0] = dp[i - 1][0];
            }
            for (int i = 1; i < rows; i++) {
                for (int j = 1; j < cols; j++) {
                    if (text1[i] == text2[j]) dp[i][j] = dp[i - 1][j - 1] + 1;
                    else {
                        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                    }
                }
            }
            return dp[rows - 1][cols - 1];
        }
    };

    //300. 最长递增子序列
    class Solution_300 {
    public:
        int lengthOfLIS(vector<int>& nums) {
            if (nums.empty()) return 0;
            int n_len = nums.size();
            vector<int> dp(n_len, 1);
            int ans = 1;
            for (int i = 1; i < n_len; i++) {
                for (int j = 0; j < i; j++) {
                    if (nums[i] > nums[j]) dp[i] = max(dp[j] + 1, dp[i]);
                }
                ans = max(ans, dp[i]);
            }
            return ans;
        }
    };

    //354:俄罗斯套娃信封问题
    class Solution_354 {
    public:
        static bool cmp(vector<int>& a, vector<int>& b) {
            return a[0] < b[0];
        }

        int maxEnvelopes(vector<vector<int>>& envelopes) {
            if (envelopes.empty()) return 0;
            sort(envelopes.begin(), envelopes.end(), cmp);
            int ans = 1;
            int n_envelope = envelopes.size();
            vector<int> dp(n_envelope, 1);
            for (int i = 1; i < n_envelope; i++) {
                for (int j = 0; j < i; j++) {
                    if (envelopes[i][0] > envelopes[j][0] && envelopes[i][1] > envelopes[j][1])
                    {
                        dp[i] = max(dp[i], dp[j] + 1);
                    }
                }
                ans = max(ans, dp[i]);
            }
            return ans;
        }
    };

    //72 编辑距离
    class Solution_72 {
    public:
        int minDistance(string word1, string word2) {
            vector<vector<int>> dp(word1.size() + 1, vector<int>(word2.size() + 1, 0));
            for (int i = 0; i <= word1.size(); i++) {
                dp[i][0] = i;
            }
            for (int j = 0; j <= word2.size(); j++) {
                dp[0][j] = j;
            }
            for (int i = 1; i <= word1.size(); i++) {
                for (int j = 1; j <= word2.size(); j++) {
                    if (word1[i - 1] == word2[j - 1]) dp[i][j] = dp[i - 1][j - 1];
                    else
                    {
                        dp[i][j] = min(min(dp[i - 1][j - 1] + 1, dp[i][j - 1] + 1), dp[i - 1][j] + 1);
                    }
                }
            }
            return dp[word1.size()][word2.size()];
        }
    };

    //416. 分割等和子集
    class Solution {
    public:
        bool canPartition(vector<int>& nums) {
            int sum = 0;
            int n_len = nums.size();
            for (int i = 0; i < n_len; i++) sum += nums[i];
            if (sum % 2 == 1) return false;
            sum /= 2;
            vector<vector<bool>> dp(n_len + 1, vector<bool>(sum + 1, false));
            for (int i = 0; i <= n_len; i++) {
                dp[i][0] = true;
            }

            for (int i = 1; i <= n_len; i++) {
                for (int j = 0; j <= sum; j++) {
                    if (j < nums[i - 1]) {
                        dp[i][j] = dp[i - 1][j];
                    }
                    else {
                        dp[i][j] = dp[i - 1][j] || dp[i - 1][j - nums[i - 1]];
                    }
                }
            }
            return dp[n_len][sum];
        }
    };
}