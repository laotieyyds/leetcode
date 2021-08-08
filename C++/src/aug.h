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

    //581. �����������������
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

    // 113 Path Sum II
    class Solution_113 {
    public:
        vector<vector<int>> ans;
        void helper(TreeNode* root, vector<int>& temp, int targetSum) {
            if (root == NULL) return;
            if (root->val == targetSum && root->left == NULL && root->right == NULL) {
                temp.push_back(root->val);
                ans.push_back(temp);
                temp.pop_back();
                return;
            }
            temp.push_back(root->val);
            helper(root->left, temp, targetSum - root->val);
            helper(root->right, temp, targetSum - root->val);
            temp.pop_back();
            return;
        }


        vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
            vector<int> temp;
            helper(root, temp, targetSum);
            return ans;
        }
    };

//429. N-ary Tree Level Order Traversal
    class Solution_429 {
    public:
        vector<vector<int>> levelOrder(NrayNode* root) {
            if (root == NULL) return {};
            queue<NrayNode*> n_ray_node_que;
            n_ray_node_que.push(root);

            vector<vector<int>> ans;
            while (!n_ray_node_que.empty()) {
                vector<int> level_ans;
                queue<NrayNode*> n_ray_node_level_que;
                while (!n_ray_node_que.empty()) {
                    NrayNode* curr = n_ray_node_que.front();
                    n_ray_node_que.pop();
                    //cout << curr->val<< " ";                    
                    level_ans.push_back(curr->val);
                    for (auto item : curr->children) {
                        n_ray_node_level_que.push(item);
                    }
                }
                //cout<<endl;
                ans.push_back(level_ans);
                swap(n_ray_node_que, n_ray_node_level_que);
            }
            return ans;
        }
    };
}