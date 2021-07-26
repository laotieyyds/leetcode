#pragma once
#include<vector>
#include<string>
#include<sstream>
#include<stack>
#include<queue>
#include "common.h"
using namespace std;

//剑指 Offer 20. 表示数值的字符串
class Solution_jianzhi20 {
public:
    string eraseSpace(string s) {
        int left = 0, right = s.size() - 1;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] != ' ') {
                left = i;
                break;
            }
        }
        for (int i = s.size() - 1; i >= 0; i--) {
            if (s[i] != ' ') {
                right = i;
                break;
            }
        }
        return s.substr(left, right - left + 1);
    }

    bool isInt(string s) {
        if (s.empty()) return false;
        if (s.size() == 1)
        {
            return (s[0] >= '0' && s[0] <= '9');
        }
        else {
            for (int i = 0; i < s.size(); i++) {
                if (i == 0) {
                    if (s[i] == '-' || s[i] == '+') continue;
                }
                if (s[i] < '0' || s[i]>'9') {
                    return false;
                }
            }
        }
        return true;
    }

    bool isDecimal(string s) {
        if (s.empty()) return false;
        if (s[0] == '.') {
            if (s.size() == 1) return false;
            else if (s[1] < '0' || s[1] > '9') return false;
            else return isInt(s.substr(1, s.size() - 1));
        }
        if (s[s.size() - 1] == '.') {
            return isInt(s.substr(0, s.size() - 1));
        }
        istringstream iss(s);
        string temp;
        vector<string> s_v;
        while (getline(iss, temp, '.'))
        {
            s_v.push_back(temp);
        }
        if (s_v.size() != 2) return false;
        if (s_v[1][0] < '0' || s_v[1][0] > '9') return false;
        return isInt(s_v[0]) && isInt(s_v[1]);
    }
    bool isHasE(string s) {
        istringstream iss(s);
        string temp;
        vector<string> s_v;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == 'e' || s[i] == 'E') {
                s_v.push_back(s.substr(0, i));
                s_v.push_back(s.substr(i + 1, s.size() - 1 - i));
            }
        }
        if (s_v.size() != 2) return false;
        bool left = isInt(s_v[0]) || isDecimal(s_v[0]);
        bool right = isInt(s_v[1]);
        return left && right;
    }


    bool isNumber(string s) {
        s = eraseSpace(s);
        if (s.empty()) return false;
        bool is_int = isInt(s);
        bool is_decimal = isDecimal(s);
        bool is_has_e = isHasE(s);
        return is_int || is_decimal || is_has_e;
    }
};

//剑指 Offer 21. 调整数组顺序使奇数位于偶数前面
class Solution_jianzhi21 {
public:
    /*
        vector<int> exchange(vector<int>& nums) {
            vector<int> ans(nums.size());
            int left = 0, right = nums.size() - 1;
            int count = 0;
            while (left <= right && count < nums.size())
            {
                if (nums[count] % 2 == 0) {
                    ans[right--] = nums[count++];
                }
                else {
                    ans[left++] = nums[count++];
                }
            }
            return ans;
        }
        */
    vector<int> exchange(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;
        while (left <= right)
        {
            while (left < nums.size() && (nums[left]) % 2 == 1)
            {
                left++;
            }
            while (right >= 0 && (nums[right]) % 2 == 0)
            {
                right--;
            }
            if (left > right) break;
            if (left <= right) swap(nums[left], nums[right]);
        }
        return nums;
    }
};

//剑指 Offer 15. 二进制中1的个数
class Solution_jianzhi15 {
public:
    int hammingWeight(uint32_t n) {
        int count = 0;
        for (int i = 0; i < 32; i++) {
            count += n & 1;
            n = n >> 1;
        }
        return count;
    }
};

//剑指 Offer 17. 打印从1到最大的n位数
class Solution_jianzhi17 {
public:
    vector<int> printNumbers(int n) {
        int max_value = pow(10, n);
        vector<int> ans;
        for (int i = 1; i < n; i++) 
        {
            ans.push_back(i);
        }
        return ans;
    }
};


//剑指 Offer 24. 反转链表
class Solution_jianzhi24 {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = NULL;
        ListNode* curr = head;
        ListNode* temp = NULL;
        while (curr)
        {
            temp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = temp;
        }
        return prev;
    }
};

//剑指 Offer 18. 删除链表的节点
class Solution_jianzhi18 {
public:
    ListNode* deleteNode(ListNode* head, int val) {
        if (head->val == val) return head->next;
        ListNode* prev = head;
        ListNode* curr = head->next;
        while (curr)
        {
            if (curr->val == val) {
                prev->next = curr->next;
                return head;
            }
            else {
                prev = curr;
                curr = curr->next;
            }

        }
        return head;
    }
};

//剑指 Offer 35. 复杂链表的复制
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

class Solution_jianzhi35 {
public:
    Node* copyRandomList(Node* head) {
        if (head == NULL) return head;
        map<Node*, Node*> mp_node;
        Node* curr = head;
        while (curr)
        {
            mp_node[curr] = new Node(curr->val);
            curr = curr->next;
        }
        curr = head;
        while (curr)
        {
            mp_node[curr]->next = mp_node[curr->next];
            mp_node[curr]->random = mp_node[curr->random];
            curr = curr->next;
        }
        return mp_node[head];
    }
};

//剑指 Offer 30. 包含min函数的栈
class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {
 
    }

    void push(int x) {
        nodes.push(x);
        if (min_nodes.empty() || x <= min_nodes.top()) {
            min_nodes.push(x);
        }
    }

    void pop() {
        int top_node = nodes.top();
        nodes.pop();
        if (top_node == min_nodes.top()) {
            min_nodes.pop();
        }
        return;
    }

    int top() {
        return nodes.top();
    }

    int min() {
        return min_nodes.top();
    }
private:
    stack<int> nodes;
    stack<int> min_nodes;

};

class Node36 {
public:
    int val;
    Node36* left;
    Node36* right;

    Node36() {}

    Node36(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node36(int _val, Node36* _left, Node36* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};

class Solution_jianzhi36 {
public:
    vector<Node36*> v_nodes;
    void helper(Node36* root) {
        if (root == NULL) return;
        helper(root->left);
        v_nodes.push_back(root);
        helper(root->right);
        return;
    }

    Node36* treeToDoublyList(Node36* root) {
        if (root == NULL) return root;
        helper(root);
        for (int i = 0; i < v_nodes.size() - 1; i++) {
            v_nodes[i]->right = v_nodes[i + 1];
            v_nodes[i + 1]->left = v_nodes[i];
        }
        v_nodes[0]->left = v_nodes[v_nodes.size() - 1];
        v_nodes[v_nodes.size() - 1]->right = v_nodes[0];
        return  v_nodes[0];
    }
};


//剑指 Offer 31. 栈的压入、弹出序列
class Solution_jianzhi31 {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        if (pushed.size() != popped.size()) return false;
        if (pushed.empty()) return true;
        stack<int> stk_nodes;
        int j = 0;
        for (int i = 0; i <= pushed.size(); i++) {
            while (!stk_nodes.empty() && stk_nodes.top() == popped[j] && j < pushed.size())
            {
                j++;
                stk_nodes.pop();
            }
            if(i < pushed.size())
                stk_nodes.push(pushed[i]);
        }
        return stk_nodes.empty();
    }
};

//剑指 Offer 38. 字符串的排列
class Solution_jianzhi38 {
public:
    vector<string> ans;
    void helper(string s, string& temp_ans, vector<bool>& flag, int idx) {
        if (idx == s.size()) {
            ans.push_back(temp_ans);
            return;
        }
        for (int i = 0; i < s.size(); i++) {
            if (flag[i]) continue;
            else {
                flag[i] = true;
                temp_ans.push_back(s[i]);
                helper(s, temp_ans, flag, idx + 1);
                temp_ans.pop_back();
                flag[i] = false;
            }
        }

    }
    vector<string> permutation(string s) {
        if (s.empty()) return ans;
        string temp = "";
        vector<bool> flag(s.size(), false);
        helper(s, temp, flag, 0);
        set<string> ans_set(ans.begin(), ans.end());
        vector<string > result(ans_set.begin(), ans_set.end());
        return result;
    }
};


//剑指 Offer 39. 数组中出现次数超过一半的数字
class Solution_jianzhi39 {
public:
    int majorityElement(vector<int>& nums) {
        vector<int> maj_nums;
        maj_nums.push_back(nums[0]);
        for (int i = 1; i < nums.size(); i++) {
            if (maj_nums.empty()) maj_nums.push_back(nums[i]);
            else {
                if (nums[i] == maj_nums[0]) {
                    maj_nums.push_back(nums[i]);
                }
                else {
                    maj_nums.pop_back();
                }
            }
        }
        return maj_nums[0];
    }
};


class Solution_jianzhi32_1 {
public:
    vector<int> levelOrder(TreeNode* root) {
        vector<int> ans;
        if (root == NULL) return ans;
        queue<TreeNode*> node;
        queue<TreeNode*> level_node;
        node.push(root);
        while (!node.empty())
        {
            vector<int> level_ans;
            while (!node.empty())
            {
                TreeNode* curr = node.front();
                node.pop();
                level_ans.push_back(curr->val);
                if (curr->left) level_node.push(curr->left);
                if (curr->right) level_node.push(curr->right);
            }
            swap(level_node, node);
            ans.insert(ans.end(), level_ans.begin(), level_ans.end());
        }
        return ans;
    }
};

//剑指 Offer 32 - II. 从上到下打印二叉树 II
class Solution_jianzhi32_2 {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if (root == NULL) return ans;
        queue<TreeNode*> node;
        queue<TreeNode*> level_node;
        node.push(root);
        while (!node.empty())
        {
            vector<int> level_ans;
            while (!node.empty())
            {
                TreeNode* curr = node.front();
                node.pop();
                level_ans.push_back(curr->val);
                if (curr->left) level_node.push(curr->left);
                if (curr->right) level_node.push(curr->right);
            }
            swap(level_node, node);
            ans.push_back(level_ans);
        }
        return ans;
    }
};


//剑指 Offer 44. 数字序列中某一位的数字
class Solution_jianzhi44 {
public:
    int findNthDigit(int n) {
        if (n < 10) return n;
        int count = 9, digit = 1, start = 1;
        while (n > count)
        {
            n -= count;
            digit++;
            start *= 10;
            if (9 * digit > INT_MAX / start) break;
            count = 9 * digit * start;
        }
        int num = start + (n-1) / digit;
        string num_str = to_string(num);
        return num_str[(n - 1) % digit] - '0';
    }
};

//剑指 Offer 32 - III. 从上到下打印二叉树 III
class Solution_jianzhi32_3 {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if (root == NULL) return ans;
        queue<TreeNode*> queue_node;
        queue<TreeNode*> level_node;
        queue_node.push(root);
        vector<int> level_ans;
        TreeNode* curr;
        bool flag = true;
        while (!queue_node.empty())
        {
            while (!queue_node.empty())
            {
                curr = queue_node.front();
                queue_node.pop();
                level_ans.push_back(curr->val);
                if (curr->left) level_node.push(curr->left);
                if (curr->right) level_node.push(curr->right);
            }
            if (!flag) {
                flag = true;
                reverse(level_ans.begin(), level_ans.end());
            }
            else {
                flag = false;
            }
            swap(queue_node, level_node);
            ans.push_back(level_ans);
            level_ans.clear();
        }
        return ans;
    }
};

//剑指 Offer 33. 二叉搜索树的后序遍历序列
class Solution_jianzhi33 {
public:
    bool helper(vector<int>& postorder, int left, int right) {
        if (left >= right) return true;
        int root = postorder[right];
        int idx = left;
        for (; idx < right; idx++) {
            if (postorder[idx] > root) {
                break;
            }
        }
        for (; idx < right; idx++) {
            if (postorder[idx] < root) return false;
        }
        bool left_flag = helper(postorder, left, idx - 1);
        bool right_flag = helper(postorder, idx, right - 1);
        return left_flag && right_flag;
    }

    bool verifyPostorder(vector<int>& postorder) {
        if (postorder.size() <= 1) return true;
        return helper(postorder, 0, postorder.size() - 1);
    }
};

//剑指 Offer 50. 第一个只出现一次的字符
class Solution_jianzhi50 {
public:
    char firstUniqChar(string s) {
        map<char, int> mp_s;
        for (int i = 0; i < s.size(); i++) {
            if (mp_s.find(s[i]) != mp_s.end()) {
                mp_s[s[i]] = -1;

            }
            else {
                mp_s[s[i]] = i;
            }
        }
        int idx = 50001;
        char ans = ' ';
        for (auto iter : mp_s) {
            if (iter.second < 0) continue;
            if (iter.second < idx) {
                idx = iter.second;
                ans = iter.first;
            }
        }
        return ans;
    }
};

//剑指 Offer 34. 二叉树中和为某一值的路径
class Solution_jianzhi34 {
public:
    vector<vector<int>> ans;

    void helper(TreeNode* root, vector<int>& temp, int target) {
        if (root == NULL) return;
        if (root->val == target && root->left == NULL && root->right == NULL) {
            temp.push_back(root->val);
            ans.push_back(temp);
            temp.pop_back();
            return;
        }
        else {
            temp.push_back(root->val);
            helper(root->left, temp, target - root->val);
            helper(root->right, temp, target - root->val);
            temp.pop_back();
            return;
        }
    }

    vector<vector<int>> pathSum(TreeNode* root, int target) {
        vector<int> ans_temp;
        helper(root, ans_temp, target);
        return ans;
    }
};

//剑指 Offer 56 - I. 数组中数字出现的次数
class Solution_jianzhi56_1 {
public:
    vector<int> singleNumbers(vector<int>& nums) {
        int ret = 0;
        for (int i = 0; i < nums.size(); i++) {
            ret ^= nums[i];
        }
        int target = 1;
        while ((target & ret) == 0)
        {
            target = target << 1;
        }
        int a = 0, b = 0;
        for (int i = 0; i < nums.size(); i++) {
            if ((target & nums[i]) > 0) {
                a ^= nums[i];
            }
            else {
                b ^= nums[i];
            }
        }
        return { a, b };
    }
};

//剑指 Offer 56 - II. 数组中数字出现的次数 II

class Solution_jianzhi56_2 {
public:
    int singleNumber(vector<int>& nums) {
        int ans = 0;
        for (int i = 0; i < 32; i++) {
            int sum = 0;
            for (auto& item : nums) {
                sum += (item >> i) & 1;
            }
            ans |= (sum % 3) << i;
        }
        return ans;
    }
};

//剑指 Offer 57. 和为s的两个数字
class Solution_jianzhi57 {
public:
    /*
    vector<int> twoSum(vector<int>& nums, int target) {
        map<int, int> mp;
        for (int i = 0; i < nums.size(); i++) {
            if (mp.find(nums[i]) != mp.end()) {
                return { nums[i], mp[nums[i]] };
            }
            else {
                mp[target - nums[i]] = nums[i];
            }
        }
        return {};
    }
    */
    vector<int> twoSum(vector<int>& nums, int target) {
        int left = 0, right = nums.size()-1;
        while (left < right)
        {
            int sum = nums[left] + nums[right];
            if (sum == target) return { nums[left], nums[right] };
            else if (sum > target) {
                right--;
            }
            else {
                left++;
            }
        }
        return {};
            
    }

};

//剑指 Offer 68 - I. 二叉搜索树的最近公共祖先
class Solution68_1 {
public:
    TreeNode* helper(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root->val == p->val || root->val == q->val) return root;
        if (root->val > p->val) {
            if (root->val < q->val) return root;
            else {
                return helper(root->left, p, q);
            }
        }
        else {
            if (root->val > q->val) return root;
            else {
                return helper(root->right, p, q);
            }
        }
    }

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (p == NULL) return q;
        if (q == NULL) return p;
        return helper(root, p, q);
    }
};

//剑指 Offer 68 - II. 二叉树的最近公共祖先
class Solution68_2 {
public:
    TreeNode* helper(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == NULL) return NULL;
        if (root->val == p->val || root->val == q->val) return root;
        TreeNode* left = helper(root->left, p, q);
        TreeNode* right = helper(root->right, p, q);
        if (left != NULL && right != NULL) {
            return root;
        }
        else {
            return left == NULL ? right : left;
        }
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        return helper(root, p, q);
    }
};

//剑指 Offer 57 - II. 和为s的连续正数序列
class Solution_57_2 {
public:
    vector<int> geneAns(int target, int num_len, int begin) {
        vector<int> result;
        while (num_len--)
        {
            result.push_back(begin++);
        }
        return result;
    }

    vector<vector<int>> findContinuousSequence(int target) {
        int max = sqrt(2 * target);
        vector<vector<int>> ans;
        for (int i = max; i >= 2; i--) {
            if (i % 2 == 1) {
                if (target % i != 0) continue;
                else {
                    ans.push_back(geneAns(target, i, target / i - i / 2));
                }
            }
            else {
                if (target % i != i / 2) continue;
                else {
                    ans.push_back(geneAns(target, i, target / i - i / 2 + 1));
                }
            }
        }
        return ans;
    }
};

//剑指 Offer 52. 两个链表的第一个公共节点
class Solution_jianzhi52 {
public:
    int ListLen(ListNode* head) {
        int len = 0;
        while (head)
        {
            len++;
            head = head->next;
        }
        return len;
    }

    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
        if (NULL == headA || NULL == headB) return NULL;
        int a_len = ListLen(headA);
        int b_len = ListLen(headB);
        if (a_len < b_len) {
            swap(headA, headB);
            swap(a_len, b_len);
        }
        while ((a_len - b_len) > 0)
        {
            a_len--;
            headA = headA->next;
        }
        while (headA && headB)
        {
            if (headA == headB) return headA;
            else {
                headA = headA->next;
                headB = headB->next;
            }
        }
        return NULL;
    }
};

//剑指 Offer 58 - I. 翻转单词顺序
class Solution_jianzhi58_1 {
public:
    string reverseWords(string s) {
        istringstream iss(s);
        vector<string> strs;
        string word;
        while (getline(iss, word, ' '))
        {
            if (word.empty()) continue;
            strs.push_back(word);
        }
        reverse(strs.begin(), strs.end());
        string ans = "";
        for (auto word_i : strs) {
            ans += word_i + " ";
        }
        return ans.substr(0, ans.size() - 1);
    }
};


//剑指 Offer 47. 礼物的最大价值
class Solution_jianzhi47 {
public:
    int maxValue(vector<vector<int>>& grid) {
        if (grid.empty()) return 0;
        int row = grid.size(), col = grid[0].size();
        vector<vector<int>> dp(row, vector<int>(col, 0));
        dp[0][0] = grid[0][0];
        for (int i = 1; i < row; i++) {
            dp[i][0] = dp[i - 1][0] + grid[i][0];
        }
        for (int i = 1; i < col; i++) {
            dp[0][i] = dp[0][i - 1] + grid[0][i];
        }
        for (int i = 1; i < row; i++) {
            for (int j = 1; j < col; j++) {
                dp[i][j] = grid[i][j] + max(dp[i - 1][j], dp[i][j - 1]);
            }   
        }
        return dp[row - 1][col - 1];
    }
};

//剑指 Offer 53 - I. 在排序数组中查找数字 I
class Solution_jianzhi53 {
public:
    int search_right(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        while (left < right)
        {
            int mid = (left + right + 1) / 2;
            if (nums[mid] > target) {
                right = mid - 1;
            }
            else {
                left = mid;
            }
        }
        return nums[right] == target ? right : -1;
    }


    int search_left(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        while (left < right)
        {
            int mid = (left + right) / 2;
            if (nums[mid] >= target) {
                right = mid;
            }
            else {
                left = mid + 1;
            }
        }
        return nums[left] == target ? left : -1;
    }

    int search(vector<int>& nums, int target) {
        int left = search_left(nums, target);
        int right = search_right(nums, target);
        if (left >= 0 && right >= 0 && right>=left) {
            return right - left + 1;
        }
        else {
            return 0;
        }
    }
};

//剑指 Offer 53 - II. 0～n-1中缺失的数字
class Solution_jianzhi53_2 {
public:
    int missingNumber(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;
        int mid;
        while (left <= right) {
            mid = (left + right) / 2;
            if (nums[mid] <= mid) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        return left;
    }
};

//剑指 Offer 58 - II. 左旋转字符串
class Solution_jianzhi58_2 {
public:
    string reverseLeftWords(string s, int n) {
        if (n == 0 || n == s.size()) return s;
        n = n % s.size();
        return s.substr(n - 1, s.size() - n) + s.substr(0, n);
    }
};

//剑指 Offer 40. 最小的k个数
class Solution_jianzhi40 {
public:

    void quicksort(vector<int>& nums, int left, int right) {
        if (left >= right) return;
        int lo = left, hi = right;
        int pivot = nums[left];
        while (left < right)
        {
            while (left < right && nums[right] >= pivot)
            {
                right--;
            }
            nums[left] = nums[right];
            while (left < right && nums[left] <= pivot)
            {
                left++;
            }
            nums[right] = nums[left];
        }
        nums[left] = pivot;
        int index = left;
        quicksort(nums, lo, index - 1);
        quicksort(nums, index + 1, hi);
    }

    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        vector<int> ans;
        if (arr.empty()) return ans;
        quicksort(arr, 0, arr.size() - 1);
        ans.insert(ans.end(), arr.begin(), arr.begin() + k);
        return ans;
    }
};


//剑指 Offer 41. 数据流中的中位数
class MedianFinder {
public:
    /** initialize your data structure here. */
    priority_queue<int, vector<int>, less<int>> queue_a;
    priority_queue<int, vector<int>, greater<int>> queue_b;

    MedianFinder() {
    }

    void addNum(int num) {
        if (queue_a.size() == queue_b.size()) {
            queue_b.push(num);
            int top = queue_b.top();
            queue_b.pop();
            queue_a.push(top);
        }
        else {
            queue_a.push(num);
            int top = queue_a.top();
            queue_a.pop();
            queue_b.push(top);
        }
    }

    double findMedian() {
        if (queue_a.size() == queue_b.size()) {
            return (queue_a.top() + queue_b.top()) / 2.0;
        }
        return queue_a.size() > queue_b.size() ? queue_a.top() : queue_b.top();
    }
};

