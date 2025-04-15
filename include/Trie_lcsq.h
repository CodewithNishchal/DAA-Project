#ifndef Trie_LCSQ_H
#define Trie_LCSQ_H
#include <bits/stdc++.h>
#include <string>
using namespace std;

struct TrieNode
{
    unordered_map<char, TrieNode *> children;
    int count;
    TrieNode() : count(0) {}
};

void insert(TrieNode *root, const string &s);
string longestCommon(TrieNode *root, int total);
void analyzeCommonPrefixSuffix(const vector<string> &sequences);

#endif