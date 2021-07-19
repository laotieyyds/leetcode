#pragma once
#include<vector>
#include<set>
#include<algorithm>
#include<string>
#include<map>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}

};

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


//Custom Sort String
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