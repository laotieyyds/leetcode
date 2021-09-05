#pragma once

namespace sep {
	//剑指 Offer 10- I. 斐波那契数列
	class Solution_jianzhi10 {
	public:
		int MAX = 1e9 + 7;
		int fib(int n) {
			if (n <= 1) return n;
			int f0 = 0, f1 = 1;
			int fn;
			for (int i = 2; i <= n; i++) {
				fn = (f1 + f0) % MAX;
				f0 = f1;
				f1 = fn;
			}
			return fn;
		}
	};

	//141. 环形链表
	class Solution_141 {
	public:
		bool hasCycle(ListNode* head) {
			if (head == NULL || head->next == NULL) return false;
			ListNode* p1 = head->next->next;
			ListNode* p2 = head->next;
			while (p1!=NULL && p2!=NULL)
			{
				if (p1 == p2) return true;
				else {
					p2 = p2->next;
					if (p1->next == NULL) return false;
					p1 = p1->next->next;
				}
			}
			return false;
		}
	};

	//142. 环形链表 II
	class Solution142 {
	public:
		ListNode* detectCycle(ListNode* head) {
			if (head == NULL || head->next == NULL) return NULL;
			ListNode* p1 = head->next->next;
			ListNode* p2 = head->next;
			ListNode* curr = head;
			while (p1 != NULL && p2 != NULL)
			{
				if (p1 == p2) break;
				else {
					p2 = p2->next;
					if (p1->next == NULL) return NULL;
					p1 = p1->next->next;
				}
			}
			if (p1 == NULL || p2 == NULL) return NULL;
			while (p2!=NULL && curr!=NULL)
			{
				if (p2 == curr) return curr;
				else {
					p2 = p2->next;
					curr = curr->next;
				}
			}
			return NULL;
		}
	};

	//470. 用 Rand7() 实现 Rand10()
	class Solution470 {
	public:
		int rand7() {
			return 1 + rand() % 7;
		}
		int rand10() {
			int a;
			while (true) {
				a = (rand7() - 1) * 7 + rand7();
				if (a <= 40) break;
			}
			return a % 10 + 1;
		}
	};

}