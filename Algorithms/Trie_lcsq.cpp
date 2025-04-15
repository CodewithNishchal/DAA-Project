#include <bits/stdc++.h>
#include "../include/Trie_lcsq.h"
using namespace std;

void insert(TrieNode *root, const string &s)
{
    TrieNode *node = root;
    for (char c : s)
    {
        if (!node->children[c])
            node->children[c] = new TrieNode();
        node = node->children[c];
        node->count++;
    }
}

string longestCommon(TrieNode *root, int total)
{
    string result;
    TrieNode *node = root;
    while (node && node->children.size() == 1)
    {
        auto it = node->children.begin();
        if (it->second->count < total)
            break;
        result += it->first;
        node = it->second;
    }
    return result;
}

void analyzeCommonPrefixSuffix(const vector<string> &sequences)
{
    if (sequences.empty())
    {
        cout << "No sequences to analyze.\n";
        return;
    }

    int total = sequences.size();

    // Prefix
    TrieNode *prefixRoot = new TrieNode();
    for (const string &s : sequences)
        insert(prefixRoot, s);
    string prefix = longestCommon(prefixRoot, total);

    // Suffix
    TrieNode *suffixRoot = new TrieNode();
    for (string s : sequences)
    {
        reverse(s.begin(), s.end());
        insert(suffixRoot, s);
    }
    string suffix = longestCommon(suffixRoot, total);
    reverse(suffix.begin(), suffix.end());

    cout << "\n[RESULT] Longest Common Prefix: " << (prefix.empty() ? "None" : prefix) << endl;
    cout << "[RESULT] Longest Common Suffix: " << (suffix.empty() ? "None" : suffix)<<endl;
}
