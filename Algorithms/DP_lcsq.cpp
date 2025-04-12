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

void Intra_Class_Comparison(const vector<vector<string>> &Sequence_byClass)
{
    set<int> selectedClasses;
    int n;

    cout << "Enter the number of classes (0-6) to compare internally: ";
    cin >> n;

    cout << "Enter " << n << " class numbers (0 to 6): ";
    for (int i = 0; i < n; ++i)
    {
        int classNum;
        cin >> classNum;
        if (classNum >= 0 && classNum <= 6)
            selectedClasses.insert(classNum);
        else
            cout << "Invalid class number: " << classNum << " (Skipping)\n";
    }

    for (int c : selectedClasses)
    {
        const vector<string> &group = Sequence_byClass[c];

        if (group.size() < 2)
        {
            cout << "Class " << c << " has insufficient data for comparison.\n";
            continue;
        }

        int totalLCS = 0, count = 0;

        for (size_t i = 0; i < min((size_t)20, group.size()); ++i)
        {
            for (size_t j = i + 1; j < min((size_t)20, group.size()); ++j)
            {
                pair<int, string> value = lcsq_dp(group[i], group[j]);
                totalLCS += value.first;
                count++;
            }
        }

        cout << "Class " << c << " | Avg LCS Length: "
             << ((count > 0) ? (double)totalLCS / count : 0) << endl;
    }
}

// Performing Intra-Class comparisons

void Inter_Class_Comparison(const vector<vector<string>> &Sequence_byClass)
{
    set<int> selectedClasses;
    int n;

    cout << "Enter the number of classes you want to compare: ";
    cin >> n;

    cout << "Enter " << n << " class numbers (0 to 6): ";
    for (int i = 0; i < n; ++i)
    {
        int classNum;
        cin >> classNum;
        if (classNum >= 0 && classNum <= 6)
            selectedClasses.insert(classNum);
        else
            cout << "Invalid class number: " << classNum << " (Skipping)\n";
    }

    vector<int> classes(selectedClasses.begin(), selectedClasses.end());

    for (int i = 0; i < classes.size(); ++i)
    {
        for (int j = i + 1; j < classes.size(); ++j)
        {
            int c1 = classes[i], c2 = classes[j];
            const vector<string> &g1 = Sequence_byClass[c1];
            const vector<string> &g2 = Sequence_byClass[c2];

            int totalLCS = 0, count = 0;

            for (int x = 0; x < min(10, (int)g1.size()); ++x)
            {
                for (int y = 0; y < min(10, (int)g2.size()); ++y)
                {
                    pair<int, string> value = lcsq_dp(g1[x], g2[y]);
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

// Base function that takes 2 classes and calls printMutation
void chooseBaseClasses(const vector<vector<string>> &Sequence_byClass)
{
    cout << "Enter the two classes to be compared (0-6) ";
    int string1, string2;
    cin >> string1 >> string2;
    printLimitedMutations(Sequence_byClass[string1][20], Sequence_byClass[string2][20]);
}

// Returns the edit distance and step-by-step mutation operations
void printLimitedMutations(const string &A, const string &B, int maxStepsToPrint)
{
    maxStepsToPrint = 20;
    int m = A.size(), n = B.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));

    // Fill DP matrix
    for (int i = 0; i <= m; ++i)
        dp[i][0] = i;
    for (int j = 0; j <= n; ++j)
        dp[0][j] = j;

    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n; ++j)
            dp[i][j] = (A[i - 1] == B[j - 1]) ? dp[i - 1][j - 1] : 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});

    // Traceback for mutation steps
    vector<string> mutations;
    int i = m, j = n;

    while (i > 0 || j > 0)
    {
        if (i > 0 && j > 0 && A[i - 1] == B[j - 1])
        {
            --i;
            --j;
        }
        else if (i > 0 && j > 0 && dp[i][j] == dp[i - 1][j - 1] + 1)
        {
            mutations.push_back("Substitute '" + string(1, A[i - 1]) + "' with '" + B[j - 1] + "'");
            --i;
            --j;
        }
        else if (i > 0 && dp[i][j] == dp[i - 1][j] + 1)
        {
            mutations.push_back("Delete '" + string(1, A[i - 1]) + "'");
            --i;
        }
        else if (j > 0 && dp[i][j] == dp[i][j - 1] + 1)
        {
            mutations.push_back("Insert '" + string(1, B[j - 1]) + "'");
            --j;
        }
    }

    reverse(mutations.begin(), mutations.end());

    // Print edit distance
    cout << "Edit Distance: " << dp[m][n] << endl;

    // Limit output
    int totalSteps = mutations.size();
    int stepsToPrint = min(maxStepsToPrint, totalSteps);

    cout << "Mutation Steps (showing first " << stepsToPrint << " of " << totalSteps << "):\n";
    for (int k = 0; k < stepsToPrint; ++k)
    {
        cout << k + 1 << ". " << mutations[k] << endl;
    }

    if (stepsToPrint < totalSteps)
        cout << "... (" << totalSteps - stepsToPrint << " more steps omitted)\n";
}

// Update the function to count types of mutations :
    pair<int, MutationSummary> mutation_summary(const string &A, const string &B)
{
    int m = A.size(), n = B.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));

    for (int i = 0; i <= m; ++i)
        dp[i][0] = i;
    for (int j = 0; j <= n; ++j)
        dp[0][j] = j;

    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n; ++j)
            dp[i][j] = (A[i - 1] == B[j - 1]) ? dp[i - 1][j - 1] : 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});

    MutationSummary summary;
    int i = m, j = n;

    while (i > 0 || j > 0)
    {
        if (i > 0 && j > 0 && A[i - 1] == B[j - 1])
        {
            --i;
            --j;
        }
        else if (i > 0 && j > 0 && dp[i][j] == dp[i - 1][j - 1] + 1)
        {
            ++summary.substitutions;
            --i;
            --j;
        }
        else if (i > 0 && dp[i][j] == dp[i - 1][j] + 1)
        {
            ++summary.deletions;
            --i;
        }
        else if (j > 0 && dp[i][j] == dp[i][j - 1] + 1)
        {
            ++summary.insertions;
            --j;
        }
    }

    return {dp[m][n], summary};
}

