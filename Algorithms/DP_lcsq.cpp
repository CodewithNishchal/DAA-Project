#include<bits/stdc++.h>
#include "../include/DP_lcsq.h"
#include <vector>
#include<algorithm>
using namespace std;

vector<string> class_Description = {"G protein coupled receptors", "Tyrosine kinase", "Tyrosine phosphatase", "Synthetase", "Synthase", "Lon channel", "Transcription factor"};

pair<int, string> lcsq_dp(const string &a, const string &b)
{
    int n = a.length(), m = b.length();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    // DP table construction
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            if (a[i - 1] == b[j - 1])
                dp[i][j] = 1 + dp[i - 1][j - 1];
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    // Reconstructing the LCS string
    int i = n, j = m;
    string lcs = "";
    while (i > 0 && j > 0)
    {
        if (a[i - 1] == b[j - 1])
        {
            lcs = a[i - 1] + lcs;
            --i;
            --j;
        }
        else if (dp[i - 1][j] > dp[i][j - 1])
        {
            --i;
        }
        else
        {
            --j;
        }
    }

    return {dp[n][m], lcs};
}

// Performing Intra-Class comparisons

void Intra_Class_Comparison(vector<vector<string>> Sequence_byClass)
{
    for (int c = 0; c < 7; ++c)
    {
        vector<string> &group = Sequence_byClass[c];
        int totalLCS = 0, count = 0;

        for (size_t i = 0; i < 20; ++i)
        {
            for (size_t j = i + 1; j < 20; ++j)
            {
                pair<int, string> value = lcsq_dp(group[i], group[j]);
                totalLCS += value.first;
                count++;
            }
        }

        if (count > 0)
        {
            cout << "Class " << c << " | Avg LCS Length: " << (double)totalLCS / count << endl;
        }
        else
        {
            cout << "Class " << c << " has insufficient data for comparison.\n";
        }
    }
} 

// Performing Intra-Class comparisons

void Inter_Class_Comparison(vector<vector<string>> Sequence_byClass)
{
    for (int c1 = 0; c1 < 7; ++c1)
    {
        for (int c2 = c1 + 1; c2 < 7; ++c2)
        {
            vector<string> &g1 = Sequence_byClass[c1];
            vector<string> &g2 = Sequence_byClass[c2];

            int totalLCS = 0, count = 0;

            for (int i = 0; i < min(10, (int)g1.size()); ++i)
            {
                for (int j = 0; j < min(10, (int)g2.size()); ++j)
                {
                    pair<int, string> value = lcsq_dp(g1[i], g2[j]);
                    totalLCS += value.first;
                    count++;
                }
            }

            if (count > 0)
            {
                cout << "Avg LCS between Class " << c1 << " and Class " << c2 << ": "
                     << (double)totalLCS / count << endl;
            }
        }
    }
}

