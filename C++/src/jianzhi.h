#pragma once
#include<vector>
#include<string>
#include<sstream>

//��ָ Offer 20. ��ʾ��ֵ���ַ���
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

//��ָ Offer 21. ��������˳��ʹ����λ��ż��ǰ��
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

//��ָ Offer 15. ��������1�ĸ���
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