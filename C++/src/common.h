#pragma once
//剑指 Offer 32 - I. 从上到下打印二叉树
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}

};


// Definition for a Node.
class NrayNode {
public:
    int val;
    vector<NrayNode*> children;

    NrayNode() {}

    NrayNode(int _val) {
        val = _val;
    }

    NrayNode(int _val, vector<NrayNode*> _children) {
        val = _val;
        children = _children;
    }
};
