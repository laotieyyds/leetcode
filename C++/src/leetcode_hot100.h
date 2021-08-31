#pragma once
#include"common.h"
namespace leetcode_hot100 {
	//448
    class Solution448 {
    public:
        vector<int> findDisappearedNumbers(vector<int>& nums) {
            for (auto& num : nums) {
                nums[abs(num) - 1] = -abs(nums[abs(num) - 1]);
            }
            vector<int> ans;
            for (int i = 0; i < nums.size(); i++) {
                if (nums[i] > 0) ans.push_back(i + 1);
            }
            return ans;
        }
    };

    //461. 汉明距离
    class Solution461 {
    public:
        int hammingDistance(int x, int y) {
            int z = x ^ y;
            int ans = 0;
            while (z > 0)
            {
                if ((z & 1) == 1) ans++;
                z = z >> 1;
            }
            return ans;
        }
    };

    //494. 目标和
    class Solution494 {
    public:
        void FindTarget(vector<int>& nums, int target, int idx, int& ans) {
            if (idx >= nums.size()) return;
            if (idx == nums.size() - 1) {
                if (nums[idx] == target) {
                    ans++;
                }
                if (nums[idx] == -target) {
                    ans++;
                }
                return;
            }
            FindTarget(nums, target - nums[idx], idx + 1, ans);
            FindTarget(nums, target + nums[idx], idx + 1, ans);
            return;
        }


        int findTargetSumWays(vector<int>& nums, int target) {
            int ans = 0;
            FindTarget(nums, target, 0, ans);
            return ans;
        }
    };

    //538. 把二叉搜索树转换为累加树
    class Solution538 {
    public:
        int sum = 0;
        void helper(TreeNode* root) {
            if (root == NULL) return;
            int val = root->val;
            helper(root->right);
            sum += root->val;
            root->val = sum;
            helper(root->left);
        }

        TreeNode* convertBST(TreeNode* root) {
            helper(root);
            return root;
        }
    };

}