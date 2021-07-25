#pragma once
#include<vector>
#include<set>
#include<algorithm>
#include<string>
#include<map>
#include<queue>
#include "common.h"
using namespace std;

//89 Gray Code
class Solution89 {
public:
    
    vector<int> grayCode(int n) {
        if (n == 1) return { 0, 1 };
        vector<int> dp{ 0, 1 };
        for (int i = 2; i <= n; i++) {
            for (int j = dp.size() - 1; j >= 0; j--) {
                dp.push_back(dp[j] + int(pow(2, i-1)));
            }
        }
        return dp;
    }
};

//1220. Count Vowels Permutation
class Solution1220 {
public:
    int man_ans = 10e9 + 7;
    int countVowelPermutation(int n) {
        vector<int> dp(5, 1);
        vector<int> temp(5, 1);
        for (int i = 1; i < n; i++) {
            temp[0] = (dp[1] + dp[2] + dp[4])%man_ans;
            temp[1] = (dp[0] + dp[2])% man_ans;
            temp[2] = (dp[1] + dp[3])% man_ans;
            temp[3] = dp[2]% man_ans;
            temp[4] = (dp[2] + dp[3])% man_ans;
            swap(temp, dp);
        }
        int sum = 0;
        for (auto& item : dp) {
            sum += item;
        }
        return sum % man_ans;
    }
};

//566 Reshape the Matrix
class Solution566 {
public:
    vector<vector<int>> matrixReshape(vector<vector<int>>& mat, int r, int c) {
        vector<vector<int>> ans;
        if (mat.empty()) return ans;
        int m = mat.size();
        int n = mat[0].size();
        if (m * n != r * c) {
            return mat;
        }
        ans.resize(r);
        for (int i = 0; i < r; i++) {
            ans[i].resize(c);
        }
        
        for (size_t i = 0; i < r*c; i++)
        {
            int row = i / c;
            int col = i % c;
            int m_row = i / n;
            int n_col = i % n;
            ans[i / c][i % c] = mat[i / n][i % n];
        }
        return ans;
    }
};

//378. Kth Smallest Element in a Sorted Matrix
class Solution378 {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int n = matrix.size();
        int left = matrix[0][0];
        int right = matrix[n - 1][n - 1] + 1;
        while (left < right)
        {
            int mid = left + (right - left) / 2;
            int count = 0, temp = n - 1;
            for (int i = 0; i < n; i++) {
                while (temp >= 0 && matrix[i][temp] > mid)
                {
                    temp--;
                }
                count += temp + 1;
            }

            if (count < k) left = mid + 1;
            else right = mid;
        }
        return right;
    }
};

//295. Find Median from Data Stream
class MedianFinder {
public:
    /** initialize your data structure here. */
    vector<int> nums;
    MedianFinder() {

    }

    void addNum(int num) {
        if (nums.empty()) {
            nums.push_back(num);
            return;
        };
        if (num >= nums[nums.size() - 1]) {
            nums.push_back(num);
            return;
        }
        for (auto iter = nums.begin(); iter != nums.end(); ++iter) {
            if (num < *iter) {
                iter;
                nums.insert(iter, num);
                return;
            }
        }
        return;
    }

    double findMedian() {
        double ans;
        sort(nums.begin(), nums.end());
        if (nums.size() % 2 == 1) {
            ans = nums[nums.size() / 2];
        }
        else {
            ans = (double(nums[nums.size() / 2]) + double(nums[(nums.size() - 1) / 2])) / 2;
        }
        return ans;
    }
};

//205 Isomorphic Strings
class Solution205 {
public:
    string strPattern(string& str) {
        map<char, char> mp;
        char idx = 'a';
        for (auto& item : str) {
            if (mp.find(item) == mp.end()) {
                mp[item] = idx++;
            }
        }
        string word(str.size(), 'a');
        for (int i = 0; i < word.size(); i++) {
            word[i] = mp[str[i]];
        }
        return word;
    }
    bool isIsomorphic(string s, string t) {
        if (s.size() != t.size()) return false;
        return strPattern(s) == strPattern(t);
    }
};

//162 Find Peak Element
class Solution162 {
public:
    int findPeakElement(vector<int>& nums) {
        if (nums.size() == 1) return 0;
        int left = 0, right = nums.size() - 1;
        if (nums[left] > nums[left + 1]) return left;
        if (nums[right] > nums[right - 1]) return right;
        while (left < right - 1)
        {
            int middle = (left + right) / 2;
            if (nums[middle] > nums[middle + 1]) {
                right = middle;
            }
            else {
                left = middle;
            }
        }
        return right;
    }
};


//791 Custom Sort String
class Solution791 {
public:
    struct order_info
    {
        char charater;
        int idx;
        int num;
    };
    static bool order_cmp(const order_info& a, const order_info& b) {
        return a.idx < b.idx;
    }
    string customSortString(string order, string str) {
        if (order.empty() || str.empty()) return str;
        vector<order_info> order_str_info;
        order_str_info.resize(26);
        for (int i = 0; i < 26; i++) {
            order_str_info[i].charater = 'a' + i;
            order_str_info[i].idx = 26;
            order_str_info[i].num = 0;
        }

        for (int i = 0; i < order.size(); i++) {
            order_str_info[order[i] - 'a'].idx = i;
        }

        for (int i = 0; i < str.size(); i++) {
            order_str_info[str[i] - 'a'].num++;
        }
        sort(order_str_info.begin(), order_str_info.end(), order_cmp);

        string ans;
        for (int i = 0; i < 26; i++) {
            string temp(order_str_info[i].num, order_str_info[i].charater);
            ans += temp;
        }
        return ans;
    }
};

//611 Valid Triangle Number
class Solution611 {
public:
    bool isValidTriangle(int& a, int& b, int& c) {
        return a + b > c;
    }

    int triangleNumber(vector<int>& nums) {
        if (nums.size() < 3) return 0;
        int L, R;
        sort(nums.begin(), nums.end());
        int ans = 0;
        for (int i = 0; i < nums.size(); i++) 
        {
            if (nums[i] == 0) continue;
            L = i + 1;
            R = nums.size() - 1;
            while ( L < nums.size() - 1 && R > i+1)
            {
                if (isValidTriangle(nums[i], nums[L], nums[R])) {
                    ans += R - L;
                    R--;
                    L = i + 1;
                }
                else if (L >= R) {
                    R--;
                    L = i + 1;
                }
                else {
                    L++;
                }
            }
        }
        return ans;
    }
};

//24. 两两交换链表中的节点
class Solution24 {
public:
    ListNode* swapPairs(ListNode* head) {
        if (head == NULL || head->next == NULL) return head;
        ListNode* curr = head;
        ListNode* temp = curr->next;
        curr->next = temp->next;
        temp->next = curr;
        curr = curr->next;
        ListNode* new_head = temp;
        ListNode*prev = temp->next;
        while (curr!=NULL && curr->next!=NULL)
        {
            ListNode* temp = curr->next;
            curr->next = temp->next;
            temp->next = curr;
            curr = curr->next;
            prev->next = temp;
            prev = temp->next;
        }
        return new_head;
    }
};

//25. K 个一组翻转链表
class Solution25 {
public:
    bool isValidK(ListNode* head, int k) {
        while (head && k>0)
        {
            head = head->next;
            k--;
        }
        return k == 0;
    }


    ListNode* reverseKGroup(ListNode* head, int k) {
        if (k <= 1) return head;
        if (head == NULL) return head;
        if (!isValidK(head, k)) return head;
        ListNode* prev = head;
        ListNode* curr = head->next;
        ListNode* pos = head;
        for (int i = 1; i < k; i++) {
            prev->next = curr->next;
            curr->next = pos;
            pos = curr;
            curr = prev->next;
        }

        ListNode* list_prev = prev;
        while (curr&&curr->next)
        {
            if (!isValidK(head, k)) return pos;
            prev = curr;
            ListNode* list_pos = curr;
            curr = curr->next;
            for (int i = 1; i < k; i++) {
                prev->next = curr->next;
                curr->next = list_pos;
                list_pos = curr;
                curr = prev->next;
                list_prev->next = list_pos;
            }
        }
        return pos;
    }
};

//384 Shuffle an Array
class Solution384 {
public:
    Solution384(vector<int>& nums) {
        original_nums = nums;
    }

    /** Resets the array to its original configuration and return it. */
    vector<int> reset() {
        return original_nums;
    }

    /** Returns a random shuffling of the array. */
    vector<int> shuffle() {
        vector<int> shuffle_nums(original_nums.begin(), original_nums.end());
        for (int i = shuffle_nums.size() - 1; i >= 0; i--) {
            int r = std::rand() % (i + 1);
            swap(shuffle_nums[i], shuffle_nums[r]);
        }
        return shuffle_nums;
    }
private:
    vector<int> original_nums;
};

//838. Push Dominoes
class Solution838 {
public:
    string pushDominoesLR(char& left, char& right, int len) {
        string ans="";
        if (len == 0) {
            return ans;
        }
        if (left == 'L' && right == 'L') {
            ans = string(len, 'L');
        }
        else if (left == 'R' && right == 'R') {
            ans = string(len, 'R');
        }
        else if (left == 'L' && right == 'R') {
            ans = "L" + string(len - 1, '.');
        }
        else {
            if (len % 2 == 1) {
                ans = string((len + 1) / 2, 'R') + string(len / 2, 'L');
            }
            else {
                ans = string(len / 2, 'R') + "." + string((len-1) / 2, 'L');
            }
        }
        return ans;
    }
    string pushDominoes(string dominoes) {
        if (dominoes.empty()) return dominoes;
        string ans = "";
        dominoes.push_back('R');
        char prev = 'L';
        int prev_idx = -1;
        for (int i = 0; i <= dominoes.size()-1; i++) {
            if (dominoes[i] == '.') continue;
            else {
                ans +=pushDominoesLR(prev, dominoes[i], i - prev_idx);
                prev = dominoes[i];
                prev_idx = i;
            }
        }
        return ans.substr(1, ans.size() - 1);
    }
};

//915. Partition Array into Disjoint Intervals
class Solution915 {
public:
    int partitionDisjoint(vector<int>& nums) {
        int nums_len = nums.size();
        int ans = -1;
        vector<int> dp_max_min(nums.size(), nums[0]);
        vector<int> dp_min_max(nums.size(), nums[nums_len-1]);
        for (int i = 1; i < nums_len; i++) {
            dp_max_min[i] = max(nums[i], dp_max_min[i - 1]);
        }
        for (int i = nums_len - 2; i >= 0; i--) {
            dp_min_max[i] = min(nums[i], dp_min_max[i + 1]);
        }

        for (int i = 1; i < nums_len; i++) {
            if (dp_max_min[i - 1] < dp_min_max[i]) {
                ans = i;
                break;
            }
        }
        return ans;
    }
};

//814. Binary Tree Pruning
class Solution_814 {
public:
    bool helper(TreeNode* root) {
        if (root == NULL) return true;
        if (root->val == 1) return false;
        bool left = helper(root->left);
        bool right = helper(root->right);
        return left && right;
    }

    TreeNode* pruneTree(TreeNode* root) {
        if (helper(root)) return NULL;
        root->left = pruneTree(root->left);
        root->right = pruneTree(root->right);
        return root;
    }
};

//127. Word Ladder
class Solution127 {
public:

    bool oneCharDiff(const string& a_str, const string& b_str) {
        int ret = 0;
        if (a_str.size() != b_str.size()) return false;
        for (int i = 0; i < a_str.size() && ret < 2; i++) {
            if (a_str[i] != b_str[i]) ret++;
        }
        return ret == 1;
    }

    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        if (beginWord == endWord) return 1;
        bool flag = false;
        for (auto& item : wordList) {
            if (item == endWord) flag = true;
        }
        if (!flag) return 0;
        map<string, vector<string>> cannect_mp;
        wordList.push_back(beginWord);
        for (int i = 0; i < wordList.size(); i++) {
            vector<string> temp;
            for (int j = 0; j < wordList.size(); j++) {
                if (wordList[i] != wordList[j] && oneCharDiff(wordList[i], wordList[j])) {
                    temp.push_back(wordList[j]);
                }
            }
            cannect_mp[wordList[i]] = temp;
        }

        queue<string> q;
        q.push(beginWord);
        int q_len = q.size();
        int ans = 1;
        while (!q.empty())
        {
            ans++;
            queue<string> level_q;
            while (!q.empty()) {
                string pre_str = q.front();
                q.pop();
                if (cannect_mp.find(pre_str) != cannect_mp.end()) {
                    vector<string> temp_strs = cannect_mp[pre_str];
                    for (auto& item : temp_strs) {
                        if (item == endWord) return ans;
                        else {
                            level_q.push(item);
                        }
                    }
                    cannect_mp.erase(pre_str);
                }
            }
            swap(q, level_q);
        }
        return 0;
    }
};

//126 Word Ladder II
class Solution_126 {
public:
    vector<vector<string>> result;
    void helper(map<string, vector<string>> connect_mp, vector<string>& ans,
        string beginWord, string endWord) {
        if (beginWord == endWord) {
            ans.push_back(beginWord);
            result.push_back(ans);
            ans.pop_back();
            return;
        }
        if (connect_mp.find(beginWord) != connect_mp.end()) {
            vector<string> begin_corr_strs = connect_mp[beginWord];
            connect_mp.erase(beginWord);
            ans.push_back(beginWord);
            for (auto& item : begin_corr_strs) {
                helper(connect_mp, ans, item, endWord);
            }
            ans.pop_back();
        }
        return;
    }

    bool oneCharDiff(const string& a_str, const string& b_str) {
        int ret = 0;
        if (a_str.size() != b_str.size()) return false;
        for (int i = 0; i < a_str.size() && ret < 2; i++) {
            if (a_str[i] != b_str[i]) ret++;
        }
        return ret == 1;
    }

    vector<vector<string>> findLadders(string beginWord,
        string endWord, vector<string>& wordList) {

        if (beginWord == endWord) return { {beginWord} };
        bool flag = false;
        for (auto& item : wordList) {
            if (item == beginWord) flag = true;
        }
        if (!flag)wordList.push_back(beginWord);
        flag = false;
        for (auto& item : wordList) {
            if (item == endWord) flag = true;
        }
        if (!flag) return result;
        map<string, vector<string>> cannect_mp;

        for (int i = 0; i < wordList.size(); i++) {
            vector<string> temp;
            for (int j = 0; j < wordList.size(); j++) {
                if (wordList[i] != wordList[j] && oneCharDiff(wordList[i], wordList[j])) {
                    temp.push_back(wordList[j]);
                }
            }
            cannect_mp[wordList[i]] = temp;
        }

        /*
        // DFS
        vector<string> ans;
        helper(cannect_mp, ans, beginWord, endWord);
        int shortest = INT_MAX;
        for (int i = 0; i < result.size(); i++) {
            if (shortest > result[i].size()) {
                shortest = result[i].size();
            }
        }
        vector<vector<string>> shortest_result;
        for (int i = 0; i < result.size(); i++) {
            if (shortest == result[i].size()) {
                shortest_result.push_back(result[i]);
            }
        }
        return shortest_result;
        */
        vector<vector<string>> str_pathes{ { {beginWord} } };
        vector<vector<string>> str_level_pathes;
        vector<vector<string>> result;
        bool isThisLevel = false;
        while (true)
        {
            vector<string> erase_node;
            for (auto item : str_pathes) {
                string node = item[item.size() - 1];
                if (cannect_mp.find(node) != cannect_mp.end()) {
                    erase_node.push_back(node);
                    vector<string> node_strs = cannect_mp[node];
                    for (auto& node_str : node_strs) {
                        if (node_str == endWord) {
                            isThisLevel = true;
                            vector<string> temp = item;
                            temp.push_back(node_str);
                            str_level_pathes.push_back(temp);
                        }
                        else {
                            vector<string> temp = item;
                            temp.push_back(node_str);
                            str_level_pathes.push_back(temp);
                        }
                    }
                }
            }
            for (auto node : erase_node) {
                cannect_mp.erase(node);
            }
            if (isThisLevel) {
                int len = str_level_pathes[0].size();
                for (int i = 0; i < str_level_pathes.size(); i++) {
                    if (str_level_pathes[i][len - 1] == endWord) {
                        result.push_back(str_level_pathes[i]);
                    }
                }
                return result;
            }
            if (str_level_pathes == str_pathes) break;
            else {
                swap(str_level_pathes, str_pathes);
                str_level_pathes.clear();
            }
        }
        return { };
    }
};

//Non-negative Integers without Consecutive Ones
class Solution_600 {
public:
    bool isConsecutiveOnes(int n) {
        while (n)
        {
            if (((n >> 1) & 1) && (n  & 1)) {
                return true;
            }
            n = n >> 1;
        }
        return false;
    }
    
    int findNums(int n, int i, int sum, bool prev) {
        if (sum > n) return 0;
        if (1 << i > n) return 1;
        if (prev) {
            return  findNums(n, i + 1, sum, false);
        }
        else {
            return findNums(n, i + 1, sum, false) + findNums(n, i + 1, sum + (1 << i), true);
        }
    }

    int findIntegers(int n) {
        return findNums(n, 0, 0, false);
        /*
        //暴力方法
        int ans = 0;
        for (int i = 0; i <= n; i++) {
            if (!isConsecutiveOnes(i)) ans++;           
        }
        return ans;
        */
    }


};