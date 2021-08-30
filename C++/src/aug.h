#pragma once
#include<map>
#include<unordered_map>
#include<algorithm>
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
    /*
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
    */
    //1137. 第 N 个泰波那契数
    class Solution_1137 {
public:
    int tribonacci(int n) {
        if (n == 0) return 0;
        if (n == 1 || n == 2) return 1;
        int t_1 = 1, t_2 = 1, t_0 = 0;
        int ans;
        for (int i = 3; i <= n; i++) {
            ans = t_0 + t_1 + t_2;
            t_0 = t_1;
            t_1 = t_2;
            t_2 = ans;
        }
        return ans;
    }
};

    //415 字符串相加
    class Solution_415 {
    public:
        string addStrings(string num1, string num2) {
            int n1_len = num1.size(), n2_len = num2.size();
            string ans;
            int p1 = n1_len - 1, p2 = n2_len - 1;
            int flag = 0;
            while (p1 >= 0 && p2 >= 0)
            {
                int add_item = (num1[p1--] - '0') + (num2[p2--] - '0') + flag;
                flag = add_item / 10;
                ans.push_back((add_item % 10 + '0'));
            }
            while (p1 >= 0)
            {
                int add_item = (num1[p1--] - '0') + flag;
                flag = add_item / 10;
                ans.push_back((add_item % 10 + '0'));
            }
            while (p2 >= 0)
            {
                int add_item = (num2[p2--] - '0') + flag;
                flag = add_item / 10;
                ans.push_back((add_item % 10 + '0'));
            }
            if (flag > 0) ans.push_back((flag + '0'));
            reverse(ans.begin(), ans.end());
            return ans;
        }
    };

    //超级丑数
    class Solution_313 {
    public:
        int nthSuperUglyNumber(int n, vector<int>& primes) {
            priority_queue<int, vector<int>, greater<int>> p_queue;
            set<int> seen;
            p_queue.push(1);
            seen.insert(1);
            int ugly_num = 1;
            for (int i = 1; i <= n; i++)
            {
                ugly_num = p_queue.top();
                int curr = ugly_num;
                p_queue.pop();
                for (auto item : primes) {
                    if (item > INT_MAX / curr) continue;
                    if (!seen.count(item * curr)) {
                        p_queue.push(item * curr);
                        seen.insert(item * curr);
                    }
                }
            }
            return ugly_num;
        }
    };

    //954. 二倍数对数组
    class Solution954 {
    public:
        static bool cmp(int a, int b) {
            return abs(a) < abs(b);
        }
        bool canReorderDoubled(vector<int>& arr) {
            unordered_map<int, int>mp;
            //按照绝对值从小到大排序
            sort(arr.begin(), arr.end(), cmp);
            for (auto x : arr) {
                mp[x]++;
            }
            for (auto x : arr) {
                if (mp[x] == 0) continue;
                else if (mp[2 * x] <= 0) return false;
                else {
                    mp[x]--;
                    mp[2 * x]--;
                }
            }
            return true;
        }
    };

    //76 Minimum Window Substring
    class Solution_76 {
    public:
        string minWindow(string s, string t) {
            string ans = "";
            if (s.empty() || t.empty()) return ans;
            map<char, int> t_char_mp;
            map<char, int> win_char_map;
            for (auto item : t) {
                t_char_mp[item]++;
            }

            int left = 0;
            int right = 0;
            int valid = 0;
            int min_win_len = INT_MAX;
            int start = -1;
            while (right < s.size())
            {
                char temp = s[right];
                right++;
                if (t_char_mp.count(temp)) {
                    win_char_map[temp]++;
                    if (win_char_map[temp] == t_char_mp[temp]) {
                        valid++;
                    }
                }
                while (valid == t_char_mp.size()) {
                    if (right - left <= min_win_len) {
                        min_win_len = right - left;
                        start = left;
                    }
                    char left_char = s[left];
                    left++;
                    if (t_char_mp.count(left_char)) {
                        win_char_map[left_char]--;
                        if (win_char_map[left_char] < t_char_mp[left_char]) {
                            valid--;
                        }
                    }
                }
            }
            return min_win_len == INT_MAX ? "" : s.substr(start, min_win_len);
        }
    };

    //303 Range Sum Query - Immutable
    class NumArray {
    public:
        NumArray(vector<int>& nums) {
            arr.clear();
            arr.insert(arr.end(), nums.begin(), nums.end());
        }

        int sumRange(int left, int right) {
            int ans = 0;
            for (int i = left; i <= right && i < arr.size(); i++) {
                ans += arr[i];
            }
            return ans;
        }
        vector<int> arr;
    };

    /**
     * Your NumArray object will be instantiated and called as such:
     * NumArray* obj = new NumArray(nums);
     * int param_1 = obj->sumRange(left,right);
     */
    //91 Decode Ways
    class Solution91 {
    public:
        int numDecodings(string s) {
            vector<int> dp(s.size() + 1, 0);
            dp[0] = 1;
            dp[1] = s[0] == '0' ? 0 : 1;
            for (int i = 2; i <= s.size(); i++) {
                if (s[i] != '0') dp[i] += dp[i - 1];
                if (s[i - 1] == '1') dp[i] += dp[i - 2];
                if (s[i - 1] == '2' && s[i] <= '6') {
                    cout << "add" << endl;
                    dp[i] += dp[i - 2];
                }
            }
            return dp[s.size()];
        }
    };

    //633 Sum of Square Numbers
    class Solution633 {
    public:
        bool judgeSquareSum(int c) {
            int sqrt_c = sqrt(c);
            if (sqrt_c * sqrt_c == c) return true;
            for (int i = 1; i <= sqrt_c; i++) {
                int sqrt_b = sqrt(c - i * i);
                if ((i * i + sqrt_b * sqrt_b) == c) return true;
            }
            return false;
        }
    };

    //
    class Solution {
    public:
    int maxCount(int m, int n, vector<vector<int>>& ops) {
        int rows = INT_MAX;
        int cols = INT_MAX;
        for (int i = 0; i < ops.size(); i++) {
            rows = min(rows, ops[i][0]);
            cols = min(cols, ops[i][1]);
        }
        rows = min(rows, m);
        cols = min(cols, n);
        return rows * cols;
    }
};
}