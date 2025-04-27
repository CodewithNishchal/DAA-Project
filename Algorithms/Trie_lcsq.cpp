#include <bits/stdc++.h>
#include "../include/Trie_lcsq.h"
using namespace std;

void insert(TrieNode* root, const string& s) {
    TrieNode* node = root;
    for (char c : s) {
        if (!node->children[c])
            node->children[c] = new TrieNode();
        node = node->children[c];
        node->count++;
    }
}

string longestCommon(TrieNode* root, int total, double threshold) {
    string result;
    TrieNode* node = root;
    while (node && node->children.size() == 1) {
        auto it = node->children.begin();
        if ((double)it->second->count / total < threshold)
            break;
        result += it->first;
        node = it->second;
    }
    return result;
}

void analyzeCommonPrefixSuffix(const vector<string>& sequences) {
    if (sequences.empty()) {
        cout << "No sequences to analyze.\n";
        return;
    }

    int total = sequences.size();

    TrieNode* prefixRoot = new TrieNode();
    for (string s : sequences) {
        s.erase(remove_if(s.begin(), s.end(), ::isspace), s.end());  // Remove whitespace
        insert(prefixRoot, s);
    }
    string prefix = longestCommon(prefixRoot, total, 0.8);

    TrieNode* suffixRoot = new TrieNode();
    for (string s : sequences) {
        s.erase(remove_if(s.begin(), s.end(), ::isspace), s.end());  // Remove whitespace
        reverse(s.begin(), s.end());
        insert(suffixRoot, s);
    }
    string suffix = longestCommon(suffixRoot, total, 0.8);
    reverse(suffix.begin(), suffix.end());

    cout << "\n[RESULT] Longest Common Prefix: " << (prefix.empty() ? "None" : prefix) << endl;
    cout << "[RESULT] Longest Common Suffix: " << (suffix.empty() ? "None" : suffix) << endl;
}
