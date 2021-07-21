#pragma once
#include<vector>
#include<string>
#include<sstream>
#include<stack>
#include<queue>

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

//剑指 Offer 32 - I. 从上到下打印二叉树
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
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
