#include <bits/stdc++.h>
#include "../include/Backtrack_lcsq.h"
#include <vector>
#include <algorithm>
using namespace std;

#include <set>

void backtrackAllLCS(const vector<vector<int>> &dp, const string &X, const string &Y, int i, int j, string lcs, set<string> &all_lcs, int max_motifs)
{
    if (all_lcs.size() >= max_motifs)
        return;

    if (i == 0 || j == 0)
    {
        reverse(lcs.begin(), lcs.end());
        all_lcs.insert(lcs);
        return;
    }

    if (X[i - 1] == Y[j - 1])
    {
        backtrackAllLCS(dp, X, Y, i - 1, j - 1, lcs + X[i - 1], all_lcs, max_motifs);
    }
    else
    {
        if (dp[i - 1][j] >= dp[i][j - 1])
            backtrackAllLCS(dp, X, Y, i - 1, j, lcs, all_lcs, max_motifs);
        if (dp[i][j - 1] >= dp[i - 1][j])
            backtrackAllLCS(dp, X, Y, i, j - 1, lcs, all_lcs, max_motifs);
    }
}

set<string> getAllLCS(const string &X, const string &Y, int max_motifs = 5)
{
    int m = X.length(), n = Y.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n; ++j)
            if (X[i - 1] == Y[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);

    set<string> all_lcs;
    backtrackAllLCS(dp, X, Y, m, n, "", all_lcs, max_motifs);
    return all_lcs;
}