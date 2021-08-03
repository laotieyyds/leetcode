#pragma once

namespace aug {
    //90. Subsets II
    class Solution_90 {
    public:
        set<vector<int>> ans;
        void helper(vector<int>& nums, int idx, vector<int>& ans_set) {
            if (idx == nums.size()) {
                ans.insert(ans_set);
                return;
            }

            ans_set.push_back(nums[idx]);
            ans.insert(ans_set);
            helper(nums, idx + 1, ans_set);
            ans_set.pop_back();
            helper(nums, idx + 1, ans_set);
            return;
        }
        vector<vector<int>> subsetsWithDup(vector<int>& nums) {
            sort(nums.begin(), nums.end());
            vector<int> temp_ans;
            helper(nums, 0, temp_ans);
            vector<vector<int>> result;
            result.insert(result.end(), ans.begin(), ans.end());
            return result;
        }
    };

    //581. 最短无序连续子数组
    class Solution_581 {
    public:
        int findUnsortedSubarray(vector<int>& nums) {
            vector<int> temp = nums;
            sort(nums.begin(), nums.end());
            int left = 0, right = nums.size() - 1;
            while (left < right && (nums[left] == temp[left] || nums[right] == temp[right]))
            {
                if (nums[left] == temp[left]) left++;
                if (nums[right] == temp[right]) right--;
            }
            if (left == right) return 0;
            return right - left + 1;
        }
    };

}