class Solution:
    """
    @param s: input string
    @return: a string as the longest palindromic substring
    """
    def longestPalindrome(self, s):
        # write your code here
        if s == None:
            return

        mat = [[False] * len(s) for _ in range(len(s))]
        for i in range(len(s)):
            mat[i][i] = True
            if i+1 < len(s) and s[i] == s[i+1]:
                mat[i][i+1] = True
        
        res = ""
        for end in range(len(s)):
            for start in range(end , -1, -1):
                if start == end:
                    if end - start + 1 > len(res):
                        res = s[start : end + 1]
                elif start == end - 1 and mat[start][end] == True:
                    if end - start + 1 > len(res):
                        res = s[start : end + 1]
                elif start + 1 < len(s) and end - 1 >= 0 and mat[start + 1][end - 1] == True and s[start] == s[end]:
                    mat[start][end] = True
                    if end - start + 1 > len(res):
                        res = s[start : end + 1]

        return res