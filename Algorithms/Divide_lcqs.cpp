#include <bits/stdc++.h>
#include "../include/Divide_lcsq.h"
using namespace std;

// Helper to compute LCS length using 2 rows (space optimized)
vector<int> compute_lcs_row(const string &a, const string &b) {
    int m = a.length(), n = b.length();
    vector<int> prev(n + 1, 0), curr(n + 1, 0);

    for (int i = 1; i <= m; ++i) {
        swap(prev, curr);
        for (int j = 1; j <= n; ++j) {
            if (a[i - 1] == b[j - 1])
                curr[j] = prev[j - 1] + 1;
            else
                curr[j] = max(prev[j], curr[j - 1]);
        }
    }

    return curr;
}

// Core recursive function for Divide and Conquer LCS
string lcs_divide_conquer(const string &a, const string &b) {
    int m = a.length(), n = b.length();

    if (m == 0 || n == 0) return "";
    if (m == 1) {
        for (char ch : b) {
            if (a[0] == ch)
                return string(1, a[0]);
        }
        return "";
    }

    int mid = m / 2;
    string a_left = a.substr(0, mid);
    string a_right = a.substr(mid);

    vector<int> l1 = compute_lcs_row(a_left, b);
    string a_right_rev = a_right;
    reverse(a_right_rev.begin(), a_right_rev.end());
    string b_rev = b;
    reverse(b_rev.begin(), b_rev.end());
    vector<int> l2 = compute_lcs_row(a_right_rev, b_rev);

    int maxLen = -1, split = 0;
    for (int i = 0; i <= n; ++i) {
        if (l1[i] + l2[n - i] > maxLen) {
            maxLen = l1[i] + l2[n - i];
            split = i;
        }
    }

    string leftLCS = lcs_divide_conquer(a_left, b.substr(0, split));
    string rightLCS = lcs_divide_conquer(a_right, b.substr(split));

    return leftLCS + rightLCS;
}

// Public function to return both length and LCS
pair<int, string> lcsq_divide_conquer(const string &a, const string &b) {
    string lcs = lcs_divide_conquer(a, b);
    return { (int)lcs.length(), lcs };
}
